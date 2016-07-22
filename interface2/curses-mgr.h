/**
 *  @file       curses-mgr.h
 *  @author     Michael Uman
 *  @date       June 30, 2016
 */

#ifndef __CURSES_MGR_H__
#define __CURSES_MGR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <panel.h>
#include <pthread.h>
#include <time.h>

#define UIRESULT_OK         0
#define UIRESULT_FAIL       -1

typedef struct _rectangle {
	int x, y;
	int w, h;
} RECT;

#define SET_RECT( rect, X, Y, W, H )                                            \
    rect.x = X;                                                                 \
    rect.y = Y;                                                                 \
    rect.w = W;                                                                 \
    rect.h = H;

typedef struct _fifo {
    uint32_t        uiFifoCont;             ///< FIFO container address
    uint32_t        uiFifoPtr;              ///< FIFO base address
    uint32_t        uiFifoSize;             ///< FIFO size
    uint32_t        uiFifoRdPtr;            ///< FIFO read pointer
    uint32_t        uiFifoWrPtr;            ///< FIFO write pointer
} FIFO;

typedef struct picBufComponent {
    uint32_t        uiBufAddress;
    uint32_t        uiTotalWidth;
    uint32_t        uiBufWidth;
    uint32_t        uiBufHeight;
    uint32_t        uiPosX;
    uint32_t        uiPosY;
    uint32_t        uiPosWidth;
    uint32_t        uiPosHeight;
    uint32_t        uiSizeTile;
} PICBUF_COMP;

typedef struct picBufSpec {
    uint32_t        uiPicAddress;
    PICBUF_COMP     lumaComp;
    PICBUF_COMP     chromaComp;
} PICBUF_SPEC;

/*  Macro used to initialize FIFO structure. */
#define INIT_FIFO(fifo, start, size, rptr, wptr)                               \
    fifo.uiFifoPtr = start;                                                    \
    fifo.uiFifoSize = size;                                                    \
    fifo.uiFifoRdPtr = rptr;                                                   \
    fifo.uiFifoWrPtr = wptr;


typedef enum _flags {
    FLAG_FILLTHREAD_RUNNING  = (1L << 0),
    FLAG_EMPTYTHREAD_RUNNING = (1L << 1),
    FLAG_SAVING_YUV          = (1L << 2),
    FLAG_QUIT_IN_PROGRESS    = (1L << 3),
} FLAGS;

/**
 *	User Interface context.
 */

class UI_CONTEXT {
public:
    int             screenx;
    int             screeny;
    int             maxlines;
    uint32_t        counter;
    APP_STATE       state;
    volatile int    flags;
    const char*     codec;

    const char*     szPlayFile;
    const char*     szBinFile[2];
    const char*     szCapFile;
    const char*     szConn;
    const char*     szChip;

    uint32_t        uivtdb;             ///< Task Database ptr
    uint32_t        uivtif;             ///< Task Interface ptr

    FIFO            DispFifo;
    FIFO            BtsFifo;

    uint32_t        frameCnt;

#ifdef  ENABLE_PROFILING
    double          secsPerFrame;
#endif // ENABLE_PROFILING

    PICBUF_SPEC     picbuf;

    time_t          startTime;

    RECT            status_rect;
    WINDOW*         status_window;
    PANEL*          status_panel;

    RECT            input_rect;
    WINDOW*         input_window;
    PANEL*          input_panel;

    RECT            output_rect;
    WINDOW*         output_window;
    PANEL*          output_panel;

    pthread_mutex_t context_mutex;
};

int init_user_interface(UI_CONTEXT* pCtx);
int uninit_user_interface(UI_CONTEXT* pCtx);
int update_user_interface(UI_CONTEXT* pCtx);

/* Multithreaded locking functions */
void lock_context(UI_CONTEXT* pCtx);
void unlock_context(UI_CONTEXT* pCtx);

/**
 *  Flag macros
 */

#define SET_FLAG(ctx, value)                                                     \
    ((UI_CONTEXT*)(ctx)->pUIContext)->flags |= (value)

#define CLEAR_FLAG(ctx, value)                                                   \
    ((UI_CONTEXT*)(ctx)->pUIContext)->flags &= ~(value)

#define TEST_FLAG(ctx, value)                                                    \
    ((UI_CONTEXT*)(ctx)->pUIContext)->flags & (value))

#define DRAW_BUFFER_SIZE            512

/* Input Field macros */

#define DRAW_INPUT_FIELD_HEX( text, value, ctx, y )                             \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->input_window, (y), 4, buffer);                            \
    snprintf(buffer, DRAW_BUFFER_SIZE, "0x%08X", value);                        \
    mvwaddstr( (ctx)->input_window, (y), 27, buffer);                           \
    y++

#define DRAW_INPUT_FIELD_STR( text, value, ctx, y )                             \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->input_window, (y), 4, buffer);                            \
    mvwaddstr( (ctx)->input_window, (y), 27, (value != 0L)?value:"N/A");        \
    y++

#define DRAW_INPUT_FIELD_FIFO( text, value, ctx, y )                            \
    format_fifo_string(buffer, DRAW_BUFFER_SIZE, (text), 20, &value);           \
    mvwaddstr((ctx)->input_window, y, 4, buffer);                               \
    y++;

#define DRAW_INPUT_FIELD_DEC( text, value, ctx, y )                             \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->input_window, (y), 4, buffer);                            \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%d", value);                            \
    mvwaddstr( (ctx)->input_window, (y), 27, buffer);                           \
    y++

#define DRAW_INPUT_FIELD_TS( text, value, fmt, ctx, y )                         \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->input_window, (y), 4, buffer);                            \
    strftime(buffer, DRAW_BUFFER_SIZE, (fmt), localtime((&value)));             \
    mvwaddstr( (ctx)->input_window, (y), 27, buffer);                           \
    y++

#define DRAW_INPUT_FIELD_FLAG( text, flag, truestr, falsestr, ctx, y )          \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->input_window, (y), 4, buffer);                            \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%s",                                    \
             ((ctx)->flags & (flag))?(truestr):(falsestr));                     \
    mvwaddstr( (ctx)->input_window, (y), 27, buffer);                           \
    y++

/* Output Field macros */

#define DRAW_OUTPUT_FIELD_HEX( text, value, ctx, y )                            \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->output_window, (y), 4, buffer);                           \
    snprintf(buffer, DRAW_BUFFER_SIZE, "0x%08X", value);                        \
    mvwaddstr( (ctx)->output_window, (y), 27, buffer);                          \
    y++

#define DRAW_OUTPUT_FIELD_STR( text, value, ctx, y )                            \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->output_window, (y), 4, buffer);                           \
    mvwaddstr( (ctx)->output_window, (y), 27, (value != 0L)?value:"N/A");       \
    y++

#define DRAW_OUTPUT_FIELD_DEC( text, value, ctx, y )                            \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->output_window, (y), 4, buffer);                           \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%d", value);                            \
    mvwaddstr( (ctx)->output_window, (y), 27, buffer);                          \
    y++

#define DRAW_OUTPUT_FIELD_DBL( text, value, ctx, y )                            \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->output_window, (y), 4, buffer);                           \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%3.2f", value);                         \
    mvwaddstr( (ctx)->output_window, (y), 27, buffer);                          \
    y++

#define DRAW_OUTPUT_FIELD_FIFO( text, value, ctx, y )                           \
    format_fifo_string(buffer, DRAW_BUFFER_SIZE, (text), 20, &value);           \
    mvwaddstr( (ctx)->output_window, y, 4, buffer);                             \
    y++;

#define DRAW_OUTPUT_FIELD_PB( text, spec, line, ctx, y )                        \
    snprintf(buffer, DRAW_BUFFER_SIZE, "%-20.20s :", (text) );                  \
    mvwaddstr( (ctx)->output_window, (y), 4, buffer);                           \
    format_picbuf_string(buffer, DRAW_BUFFER_SIZE, (spec), (line));             \
    mvwaddstr( (ctx)->output_window, (y), 27, buffer);                          \
    y++;


#endif // __CURSES_MGR_H__
