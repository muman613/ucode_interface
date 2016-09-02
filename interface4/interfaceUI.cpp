#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <libgen.h>
#include <ncurses.h>
#include <panel.h>
#include <signal.h>
#include <unistd.h>
#include "dbgutils.h"
#include "interfaceUI.h"


static volatile bool bControlC = false;

void _control_c_handler(int n) {
    D(debug("%s\n", __PRETTY_FUNCTION__));
    bControlC = true;
}

#define     SET_FLAG(x)     flags |= (x)
#define     CLEAR_FLAG(x)   flags &= ~(x)
#define     TEST_FLAG(x)    ((flags & (x)) != 0)

interfaceUI::interfaceUI()
:   state(APP_STATE_UNKNOWN),
    flags(0)
{
    //ctor
}

interfaceUI::~interfaceUI()
{
    //dtor
}
/**
 *
 */

void interfaceUI::center_string(WINDOW* win, int pair,
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

void interfaceUI::init_colors() {
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

int interfaceUI::init_user_interface()
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

	getmaxyx(stdscr, (screeny), (screenx));
	maxlines = screeny - 2;

	SET_RECT( status_rect, 0, 0,  screenx, 6  );
	SET_RECT( input_rect,  0, 7,  screenx, 14 );
	SET_RECT( output_rect, 0, 22, screenx, 14 );

    /* Initialize status panel */
	status_window = newwin( status_rect.h, status_rect.w, status_rect.y, status_rect.x );
    status_panel  = new_panel( status_window );
    /* Initialize input panel */
    input_window = newwin( input_rect.h, input_rect.w, input_rect.y, input_rect.x );
    input_panel  = new_panel( input_window );
    /* Initialize output panel */
    output_window =  newwin( output_rect.h, output_rect.w, output_rect.y, output_rect.x );
    output_panel  = new_panel( output_window );

    hide_panel( input_panel );
    hide_panel( output_panel );

    /* Initialize context mutex */
//    pthread_mutex_init(&pCtx->context_mutex, NULL);

    return nResult;
}

/**
 *  Uninitialize user interface...
 */

int interfaceUI::uninit_user_interface()
{
    int nResult = UIRESULT_OK;

    del_panel( output_panel );
    del_panel( input_panel );
    del_panel( status_panel );

    delwin( output_window );
    delwin( input_window );
    delwin( status_window );

    endwin();

//  pthread_mutex_destroy( &pCtx->context_mutex );

    return nResult;
}

/**
 *
 */

bool interfaceUI::open(int argc, char* argv[])
{
    bool bRes = false;

    /* Parse arguments here... */
    if (opts.parse(argc, argv)) {
        init_user_interface();
        signal(SIGINT, _control_c_handler);
        bRes = true;
    }

    return bRes;
}

/**
 *
 */

bool interfaceUI::close()
{
    uninit_user_interface();
    signal(SIGINT, SIG_DFL);

    return true;
}

/**
 *  Draw a box with hilighted (BOD) title.
 */

void interfaceUI::super_box(WINDOW* pWin, const char* sTitle, int colors)
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

/**
 *  Draw the input panel.
 */

void interfaceUI::draw_input_panel()
{
//    char buffer[DRAW_BUFFER_SIZE];
//    int y = 1;
//    time_t now = time(NULL);

    super_box( input_window, "Input", 4 );

//    DRAW_INPUT_FIELD_TS  ( "Start Time",           pCtx->startTime, "%r", pCtx, y );
//    DRAW_INPUT_FIELD_TS  ( "Current Time",         now, "%r", pCtx, y );
//    DRAW_INPUT_FIELD_FLAG( "Status",               FLAG_FILLTHREAD_RUNNING, "Filling FIFO", "Done", pCtx, y);
//    DRAW_INPUT_FIELD_STR ( "Input Bitstream",      pCtx->szPlayFile, pCtx, y );
//    DRAW_INPUT_FIELD_STR ( "Codec Profile",        pCtx->codec, pCtx, y );
//    DRAW_INPUT_FIELD_STR ( "Video Microcode #0",   pCtx->szBinFile[0], pCtx, y );
////    DRAW_INPUT_FIELD_STR ( "Video Microcode #1",   pCtx->szBinFile[1], pCtx, y );
//    DRAW_INPUT_FIELD_HEX ( "Video Task Database",  pCtx->uivtdb, pCtx, y );
//    DRAW_INPUT_FIELD_HEX ( "Video Task Interface", pCtx->uivtif, pCtx, y );
//    DRAW_INPUT_FIELD_HEX ( "Bts FIFO Container",   pCtx->BtsFifo.uiFifoCont, pCtx, y );
//    DRAW_INPUT_FIELD_FIFO( "Bitstream FIFO",       pCtx->BtsFifo, pCtx, y );
//
//#ifdef ENABLE_COUNTER
//    DRAW_INPUT_FIELD_DEC ( "Counter", pCtx->counter, pCtx, y );
//    pCtx->counter++;
//#endif // ENABLE_COUNTER

    return;
}


/**
 *  Draw the output panel.
 */

void interfaceUI::draw_output_panel()
{
//    char buffer[DRAW_BUFFER_SIZE];
//    int y = 1;

    super_box( output_window, "Output", 5 );

//    DRAW_OUTPUT_FIELD_STR ( "Capture File",          pCtx->szCapFile, pCtx, y );
//    DRAW_OUTPUT_FIELD_HEX ( "DispFIFO Container",    pCtx->DispFifo.uiFifoCont, pCtx, y );
//    DRAW_OUTPUT_FIELD_FIFO( "Display FIFO",          pCtx->DispFifo, pCtx, y );
//    DRAW_OUTPUT_FIELD_DEC ( "Frame Count",           pCtx->frameCnt, pCtx, y );
//
//    if (pCtx->frameCnt > 0) {
//#ifdef  ENABLE_PROFILING
//        DRAW_OUTPUT_FIELD_DBL( "Frame DL time",      pCtx->secsPerFrame, pCtx, y);
//#endif // ENABLE_PROFILING
//        DRAW_OUTPUT_FIELD_PB( "Luma",   &pCtx->picbuf.lumaComp, 0, pCtx, y);
//        DRAW_OUTPUT_FIELD_PB( "Luma",   &pCtx->picbuf.lumaComp, 1, pCtx, y);
//        DRAW_OUTPUT_FIELD_PB( "Luma",   &pCtx->picbuf.lumaComp, 2, pCtx, y);
//
//        DRAW_OUTPUT_FIELD_PB( "Chroma", &pCtx->picbuf.chromaComp, 0, pCtx, y);
//        DRAW_OUTPUT_FIELD_PB( "Chroma", &pCtx->picbuf.chromaComp, 1, pCtx, y);
//        DRAW_OUTPUT_FIELD_PB( "Chroma", &pCtx->picbuf.chromaComp, 2, pCtx, y);
//    }
//
    return;
}

void interfaceUI::draw_status_panel()
{
    const char *msg = 0L;
    char buffer[DRAW_BUFFER_SIZE];
    inputStats      inpStats;

    super_box( status_window, "Application Status", 2);

    snprintf(buffer, DRAW_BUFFER_SIZE, "Connected to %s @ %s",
             "8758", "10.10.10.12:0");
    center_string(status_window, 2, 2, buffer);

    switch (state) {
        case APP_INITIALIZING:
            msg = "Application Initializing...";
            break;
        case APP_LOADING_MICROCODE:
            snprintf(buffer, 256, "> Loading microcode #1 [%s] <", pTarget->get_ucode_file().c_str());
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
            snprintf(buffer, 256, "> Playing stream %s <", inStats.sInputFile.c_str());
            msg = buffer;
            break;
        default:
            msg = "!! Invalid state !!";
            break;
    }

    /* Update status panel... */
    center_string(status_window, 2, 3, msg);

    return;
}

/**
 *  Update the user interface...
 */

int interfaceUI::update_user_interface()
{
    draw_status_panel();

    if (state == APP_PLAYING) {
        std::string sMsg;

        if (panel_hidden(input_panel))
            show_panel( input_panel );
        if (panel_hidden(output_panel))
            show_panel( output_panel );

        draw_input_panel();
        draw_output_panel();

        if (!TEST_FLAG(FLAG_QUIT_IN_PROGRESS)) {
            if (outStats.bSavingYUV == true) {
                sMsg = "Hit 'v' to view YUV/ Hit 'q' to quit";
            } else {
                sMsg = "Hit 'q' to quit";
            }
        } else {
            sMsg = "Quitting application";
        }

        center_string( stdscr, 1, screeny-1, sMsg.c_str());
    } else {
        hide_panel( input_panel );
        hide_panel( output_panel );
    }

    update_panels();
    doupdate();

    /* release context mutex */
//    pthread_mutex_unlock( &pCtx->context_mutex );

    return UIRESULT_OK;
}

/**
 *
 */

bool interfaceUI::run()
{
    bool bRes = false;
    D(debug("%s\n", __PRETTY_FUNCTION__));

    start = std::chrono::system_clock::now();

    state = APP_INITIALIZING;
    update_user_interface();

    pTarget = CREATE_NEW_ENGINE(opts.chipID, "Video",
                                opts.engineNo, opts.type);

    if (pTarget && pTarget->is_valid()) {
#ifdef _DEBUG
        std::cerr << *pTarget;
        debug("-- attempting to connect!\n");
#endif // _DEBUG

        if (pTarget->connect(opts.serverStr)) {
            D(debug("-- connected --\n"));
            state = APP_LOADING_MICROCODE;
            update_user_interface();
            if (pTarget->load_ucode()) {
                D(debug("-- microcode loaded --\n"));

                pStdIF = CREATE_NEW_INTERFACE( pTarget );

                if (pStdIF) {
                    D(debug("-- interface created --\n"));

                    pStdIF->play_stream(opts.inputStream, opts.outputYUV, opts.profile);

                    main_loop();
                    bRes = true;
                }

                update_user_interface();

                pStdIF->stop();

                pStdIF.reset();
            }
        } else {
            D(debug("ERROR: Unable to connect to target!\n"));
        }
    }

    pTarget.reset();

    return bRes;
}

void interfaceUI::main_loop()
{
    bool                                bDone = false;
    targetStandardIFTask::taskState     taskState;
    targetStandardIFTask::taskSubstate  taskSubstate;
    targetStandardInterface::if_state   ifState;
    int                                 ch;

    while (!bDone) {

        ch = getch();

        if (bControlC == true) {
            D(debug("-- user hit control-c!\n"));
            break;
        }

        if (ch != ERR) {
            if (tolower(ch) == 'q') {
                bDone = true;
                SET_FLAG(FLAG_QUIT_IN_PROGRESS);
                break;
            }

//            if ((toupper(ch) == 'V') && (pCtx->yuvfp != 0)) {
//                launch_viewer(pCtx.get());
//            }
        }

        ifState = pStdIF->get_interface_state();

        if (ifState != targetStandardInterface::IF_PLAYING) {
            pStdIF->get_task_state(0, &taskState, &taskSubstate);

            if (taskState == targetStandardIFTask::TASK_COMMAND_PENDING) {
                switch (taskSubstate) {
                    case targetStandardIFTask::TASK_SUBSTATE_SENT_UNINIT:
                        state = APP_SENDING_UNINIT;
                        break;
                    case targetStandardIFTask::TASK_SUBSTATE_SENT_INIT:
                        state = APP_SENDING_INIT;
                        break;
                    case targetStandardIFTask::TASK_SUBSTATE_SENT_STOP:
                        state = APP_SENDING_STOP;
                        break;
                    case targetStandardIFTask::TASK_SUBSTATE_SENT_PLAY:
                        state = APP_SENDING_PLAY;
                        break;
                    default:
                        break;
                }
            }
        } else {
            state = APP_PLAYING;
            pStdIF->get_input_stats(0, inStats);
            pStdIF->get_output_stats(0, outStats);
        }

        update_user_interface();

        usleep(5000);
    }
}
