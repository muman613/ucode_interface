/**
 *  @file       curses-mgr.c
 *  @author     Michael Uman
 *  @date       June 30, 2016
 */

#ifdef ENABLE_CURSES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <libgen.h>
#include <ncurses.h>
#include <panel.h>
#include <signal.h>


#define ALLOW_OS_CODE 1
#include "llad/include/llad.h"
//#include "rmdef/rmbtypes.h"
#include "test_interface.h"
#include "curses-mgr.h"

//#define ENABLE_COUNTER      1

/**
 *
 */

static void center_string(UI_CONTEXT* pContext,
                   WINDOW* win,
                   int pair,
                   int y, const char* str)
{
    int indent; // = (pContext->screenx - strlen(str)) / 2;
    int w, h;

    getmaxyx(win, h, w);
    (void)h;

    indent = (w - strlen(str)) / 2;

    wattron(win, COLOR_PAIR(pair)|A_BOLD);
    mvwaddstr(win, y, indent, str);
    wattroff(win, COLOR_PAIR(pair)|A_BOLD);
//	mvwaddstr(win, y, (screenx - strlen(str)) / 2, str);
    return;
}

static void init_colors() {
	if (has_colors()) {
		start_color();

		init_pair(1, COLOR_WHITE, COLOR_BLUE);
		init_pair(2, COLOR_BLACK, COLOR_WHITE);
		init_pair(3, COLOR_WHITE, COLOR_RED);
		init_pair(4, COLOR_YELLOW, COLOR_RED);
		init_pair(5, COLOR_BLUE, COLOR_WHITE);
	}

    return;
}

/**
 *  Initialize user interface context.
 */

int init_user_interface(UI_CONTEXT* pCtx)
{
    int nResult = UIRESULT_OK;

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, 1);
    keypad(stdscr, 1);
    curs_set(0);

    init_colors();

    if (has_colors())
        wbkgd(stdscr, COLOR_PAIR(1));

	getmaxyx(stdscr, (pCtx->screeny), (pCtx->screenx));
	pCtx->maxlines = pCtx->screeny - 2;

	SET_RECT( pCtx->status_rect, 0, 0,  pCtx->screenx, 5  );
	SET_RECT( pCtx->input_rect,  0, 6,  pCtx->screenx, 14 );
	SET_RECT( pCtx->output_rect, 0, 21, pCtx->screenx, 14 );

    /* Initialize status panel */
	pCtx->status_window = newwin( pCtx->status_rect.h, pCtx->status_rect.w, pCtx->status_rect.y, pCtx->status_rect.x );
    pCtx->status_panel  = new_panel( pCtx->status_window );
    /* Initialize input panel */
    pCtx->input_window = newwin( pCtx->input_rect.h, pCtx->input_rect.w, pCtx->input_rect.y, pCtx->input_rect.x );
    pCtx->input_panel  = new_panel( pCtx->input_window );
    /* Initialize output panel */
    pCtx->output_window =  newwin( pCtx->output_rect.h, pCtx->output_rect.w, pCtx->output_rect.y, pCtx->output_rect.x );
    pCtx->output_panel  = new_panel( pCtx->output_window );

    hide_panel( pCtx->input_panel );
    hide_panel( pCtx->output_panel );

    /* Initialize context mutex */
    pthread_mutex_init(&pCtx->context_mutex, NULL);

    return nResult;
}

/**
 *  Uninitialize user interface...
 */

int uninit_user_interface(UI_CONTEXT* pCtx)
{
    int nResult = UIRESULT_OK;

    del_panel( pCtx->output_panel );
    del_panel( pCtx->input_panel );
    del_panel( pCtx->status_panel );

    delwin( pCtx->output_window );
    delwin( pCtx->input_window );
    delwin( pCtx->status_window );

    endwin();

    pthread_mutex_destroy( &pCtx->context_mutex );

    return nResult;
}

/**
 *  Draw a box with hilighted (BOD) title.
 */

void super_box(WINDOW* pWin, const char* sTitle, int colors)
{
    int w,h;

    getmaxyx(pWin, h, w);
    (void)h; /* to squash unused variable warning */

    werase(pWin);
    box(pWin, 0, 0);

    if (has_colors())
        wbkgd(pWin, COLOR_PAIR(colors));
    wattron(pWin, A_BOLD);
    mvwaddstr(pWin, 0, (w - strlen(sTitle))/2, sTitle);
    wattroff(pWin, A_BOLD);
}

inline void format_fifo_string(char* szString, size_t size, const char* szLabel, int width, FIFO* pFifo)
{
    snprintf(szString, size, "%*.*s : AT 0x%08X SIZE 0x%08X RDPTR 0x%08X WRPTR 0x%08X",
             -width, width, szLabel, pFifo->uiFifoPtr, pFifo->uiFifoSize, pFifo->uiFifoRdPtr, pFifo->uiFifoWrPtr);
}

static void format_picbuf_string(char* szString, size_t size, PICBUF_COMP* comp, int line)
{
    if (line == 0) {
        snprintf(szString, size, "buffer @ 0x%08X ttl_width 0x%08X",
                 comp->uiBufAddress, comp->uiTotalWidth);
    } else if (line == 1) {
        snprintf(szString, size, "tiled dimensions ( %d x %d )",
                 comp->uiBufWidth, comp->uiBufHeight);
    } else if (line == 2) {
        snprintf(szString, size, "position x %d y %d w %d h %d size_tile %d",
                 comp->uiPosX, comp->uiPosY, comp->uiPosWidth, comp->uiPosHeight,
                 comp->uiSizeTile);
    }
}

/**
 *  Draw the input panel.
 */

void draw_input_panel(UI_CONTEXT* pCtx)
{
    char buffer[DRAW_BUFFER_SIZE];
    int y = 1;
    time_t now = time(NULL);

    super_box( pCtx->input_window, "Input", 4 );

    DRAW_INPUT_FIELD_TS  ( "Start Time",           pCtx->startTime, "%r", pCtx, y );
    DRAW_INPUT_FIELD_TS  ( "Current Time",         now, "%r", pCtx, y );
    DRAW_INPUT_FIELD_FLAG( "Status",               FLAG_FILLTHREAD_RUNNING, "Filling FIFO", "Done", pCtx, y);
    DRAW_INPUT_FIELD_STR ( "Input Bitstream",      pCtx->szPlayFile, pCtx, y );
    DRAW_INPUT_FIELD_STR ( "Codec Profile",        pCtx->codec, pCtx, y );
    DRAW_INPUT_FIELD_STR ( "Video Microcode #0",   pCtx->szBinFile[0], pCtx, y );
    DRAW_INPUT_FIELD_STR ( "Video Microcode #1",   pCtx->szBinFile[1], pCtx, y );
    DRAW_INPUT_FIELD_HEX ( "Video Task Database",  pCtx->uivtdb, pCtx, y );
    DRAW_INPUT_FIELD_HEX ( "Video Task Interface", pCtx->uivtif, pCtx, y );
    DRAW_INPUT_FIELD_HEX ( "Bts FIFO Container",   pCtx->BtsFifo.uiFifoCont, pCtx, y );
    DRAW_INPUT_FIELD_FIFO( "Bitstream FIFO",       pCtx->BtsFifo, pCtx, y );

#ifdef ENABLE_COUNTER
    DRAW_INPUT_FIELD_DEC ( "Counter", pCtx->counter, pCtx, y );
    pCtx->counter++;
#endif // ENABLE_COUNTER

    return;
}

/**
 *  Draw the output panel.
 */

void draw_output_panel(UI_CONTEXT* pCtx)
{
    char buffer[DRAW_BUFFER_SIZE];
    int y = 1;

    super_box( pCtx->output_window, "Output", 5 );

    DRAW_OUTPUT_FIELD_STR ( "Capture File",          pCtx->szCapFile, pCtx, y );
    DRAW_OUTPUT_FIELD_HEX ( "DispFIFO Container",    pCtx->DispFifo.uiFifoCont, pCtx, y );
    DRAW_OUTPUT_FIELD_FIFO( "Display FIFO",          pCtx->DispFifo, pCtx, y );
    DRAW_OUTPUT_FIELD_DEC ( "Frame Count",           pCtx->frameCnt, pCtx, y );

    if (pCtx->frameCnt > 0) {
#ifdef  ENABLE_PROFILING
        DRAW_OUTPUT_FIELD_DBL( "Frame DL time",      pCtx->secsPerFrame, pCtx, y);
#endif // ENABLE_PROFILING
        DRAW_OUTPUT_FIELD_PB( "Luma",   &pCtx->picbuf.lumaComp, 0, pCtx, y);
        DRAW_OUTPUT_FIELD_PB( "Luma",   &pCtx->picbuf.lumaComp, 1, pCtx, y);
        DRAW_OUTPUT_FIELD_PB( "Luma",   &pCtx->picbuf.lumaComp, 2, pCtx, y);

        DRAW_OUTPUT_FIELD_PB( "Chroma", &pCtx->picbuf.chromaComp, 0, pCtx, y);
        DRAW_OUTPUT_FIELD_PB( "Chroma", &pCtx->picbuf.chromaComp, 1, pCtx, y);
        DRAW_OUTPUT_FIELD_PB( "Chroma", &pCtx->picbuf.chromaComp, 2, pCtx, y);
    }

    return;
}

/**
 *  Update the user interface...
 */

int update_user_interface(UI_CONTEXT* pCtx)
{
    const char *msg = 0L;
    char buffer[DRAW_BUFFER_SIZE];
 //   char szTmp[12];

    assert(pCtx != 0L);

    pthread_mutex_lock( &pCtx->context_mutex );

    switch (pCtx->state) {
    case APP_INITIALIZING:
        msg = "Application Initializing...";
        break;
    case APP_LOADING_MICROCODE_0:
//        snprintf(buffer, 256, "> Loading microcode #1 [%s] <", (pCtx->szBinFile[0] != 0)?basename((char *)pCtx->szBinFile[0]):"N/A");
        msg = buffer;
        break;
    case APP_LOADING_MICROCODE_1:
//        snprintf(buffer, 256, "> Loading microcode #2 [%s] <", (pCtx->szBinFile[1] != 0)?basename((char *)pCtx->szBinFile[1]):"N/A");
        msg = buffer;
        break;
    case APP_SENDING_UNINIT:
        msg = "Sending Uninit command!";
        break;
    case APP_SENDING_INIT:
        msg = "Sending Init command!";
        break;
    case APP_SENDING_PLAY:
        msg = "Sending Play command!";
        break;
    case APP_SENDING_STOP:
        msg = "Sending Stop command!";
        break;
    case APP_PLAYING:
//        snprintf(buffer, 256, "> Playing stream %s <", (pCtx->szPlayFile != 0)?basename((char *)pCtx->szPlayFile):"N/A");
        msg = buffer;
        break;
    default:
        msg = "!! Invalid state !!";
        break;
    }

    super_box( pCtx->status_window, "Application Status", 2);

    /* Update status panel... */
    center_string(pCtx, pCtx->status_window, 2, 2, msg);

    if (pCtx->state == APP_PLAYING) {
        if (panel_hidden(pCtx->input_panel))
            show_panel( pCtx->input_panel );
        if (panel_hidden(pCtx->output_panel))
            show_panel( pCtx->output_panel );

        draw_input_panel( pCtx );
        draw_output_panel( pCtx );
    } else {
        hide_panel( pCtx->input_panel );
        hide_panel( pCtx->output_panel );
    }

    if ((pCtx->flags & FLAG_QUIT_IN_PROGRESS) == 0) {
        center_string( pCtx, stdscr, 1, pCtx->screeny-1, "Hit 'q' to quit");
    } else {
        center_string( pCtx, stdscr, 1, pCtx->screeny-1, "Quitting application");
    }

    update_panels();
    doupdate();

    /* release context mutex */
    pthread_mutex_unlock( &pCtx->context_mutex );

    return UIRESULT_FAIL;
}

/**
 *  Lock context mutex.
 */

void lock_context(UI_CONTEXT* pCtx)
{
    pthread_mutex_lock( &pCtx->context_mutex );
}

/**
 *  Unlock context mutex.
 */

void unlock_context(UI_CONTEXT* pCtx)
{
    pthread_mutex_unlock( &pCtx->context_mutex );
}

#endif // ENABLE_CURSES
