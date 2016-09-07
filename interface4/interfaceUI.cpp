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
#include <iomanip>
#include <string>
#include "dbgutils.h"
#include "interfaceUI.h"

//template <typename T>
std::string dbl_to_string(double const& value) {
    std::stringstream sstr;
    sstr << std::fixed << std::setprecision(3) << value;
    return sstr.str();
}

volatile std::atomic<bool> bControlC; // = false;

/**
 *  Handle when user enters Control-C to break application.
 *  Set the global Control-C variable.
 */

void _control_c_handler(int n) {
    D(debug("%s\n", __PRETTY_FUNCTION__));
    bControlC = true;
}

std::string format_fifo_string(FIFO* pFifo)
{
    std::ostringstream  os;

    os << "AT " << hexify(pFifo->uiFifoPtr) << " SIZE " <<
          hexify(pFifo->uiFifoSize) << " RDPTR " << hexify(pFifo->uiFifoRdPtr) <<
          " WRPTR " << hexify(pFifo->uiFifoWrPtr);

    return os.str();
}

std::string format_picbuf_string(PICBUF_COMP* comp, int line)
{
    std::ostringstream  os;

    if (line == 0) {
        os << "buffer @ " << hexify(comp->uiBufAddress) << " ttl_width " << hexify(comp->uiTotalWidth);
    } else if (line == 1) {
        os << "tiled dimensions ( " << comp->uiBufWidth << " x " << comp->uiBufHeight << " )";
    } else if (line == 2) {
        os << "position x " << comp->uiPosX << " y " << comp->uiPosY << " w " <<
              comp->uiPosWidth << " h " << comp->uiPosHeight << " size_tile " << comp->uiSizeTile;
    }

    return os.str();
}

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

    int y = 1;

    auto DRAW_INPUT_FIELD_FIFO = [this,&y](std::string text, FIFO* pFifo) {
        text.resize(20);
        mvwaddstr(input_window, y, 4, text.c_str());
        mvwaddch(input_window, y, 25, ':');
        mvwaddstr(input_window, y, 27, format_fifo_string(pFifo).c_str());
        y++;
    };
    auto DRAW_INPUT_FIELD_HEX = [this,&y](std::string text, uint32_t value) {
        text.resize(20);
        mvwaddstr(input_window, y, 4, text.c_str());
        mvwaddch(input_window, y, 25, ':');
        mvwaddstr(input_window, y, 27, hexify(value).c_str());
        y++;
    };

    auto DRAW_INPUT_FIELD_STR = [this,&y](std::string text, std::string value) {
        text.resize(20);
        mvwaddstr(input_window, y, 4, text.c_str());
        mvwaddch(input_window, y, 25, ':');
        mvwaddstr(input_window, y, 27, value.c_str());
        y++;
    };

//    auto DRAW_INPUT_FIELD_DEC = [&](std::string text, uint32_t value) {
////        std::ostringstream   os;
////        os << std::setw(LABEL_WIDTH) << std::setfill(' ') << std::left << text << ": " << value;
//        y++;
////        return os.str();
//    };

    auto DRAW_INPUT_FIELD_TP = [this,&y](std::string text, TIME_POINT tp) {
        text.resize(20);
        mvwaddstr(input_window, y, 4, text.c_str());
        mvwaddch(input_window, y, 25, ':');
        mvwaddstr(input_window, y, 27, asString(tp).c_str());
        y++;
    };

    TIME_POINT now = std::chrono::system_clock::now();

    super_box( input_window, "Input", 4 );

    DRAW_INPUT_FIELD_TP  ( "Start Time",            start );
    DRAW_INPUT_FIELD_TP  ( "Current Time",          now );
    DRAW_INPUT_FIELD_STR ( "Input Bitstream",       inStats.sInputFile );
    DRAW_INPUT_FIELD_STR ( "Codec Profile",         targetStandardInterface::get_profile_string_from_id(inStats.profile) );
    DRAW_INPUT_FIELD_STR ( "Video Microcode",       pTarget->get_ucode_file() );
    DRAW_INPUT_FIELD_HEX ( "Video Task Database",   inStats.pvtdb );
    DRAW_INPUT_FIELD_HEX ( "Video Task Interface",  inStats.pvti );
    DRAW_INPUT_FIELD_HEX ( "Bts FIFO Container",    inStats.btsFifo.uiFifoCont );
    DRAW_INPUT_FIELD_FIFO( "Bitstream FIFO",        &inStats.btsFifo );

    if (opts.type == targetEngine::UCODE_DEBUG) {
        DRAW_INPUT_FIELD_STR( "Debug State",        get_debug_string());
//        DRAW_INPUT_FIELD_HEX( "Debug Status1",      dbgStatus.status1);
//        DRAW_INPUT_FIELD_HEX( "Debug Status2",      dbgStatus.status2);
    }
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
    int y = 1;

    auto DRAW_OUTPUT_FIELD_STR = [this,&y](std::string text, std::string value) {
        text.resize(20);
        mvwaddstr(output_window, y, 4, text.c_str());
        mvwaddch(output_window, y, 25, ':');
        mvwaddstr(output_window, y, 27, value.c_str());
        y++;
    };

    auto DRAW_OUTPUT_FIELD_DEC = [this,&y](std::string text, uint32_t value) {
        text.resize(20);
        mvwaddstr(output_window, y, 4, text.c_str());
        mvwaddch(output_window, y, 25, ':');
        mvwaddstr(output_window, y, 27, std::to_string(value).c_str());
        y++;
    };

    auto DRAW_OUTPUT_FIELD_FIFO = [this,&y](std::string text, FIFO* pFifo) {
        text.resize(20);
        mvwaddstr(output_window, y, 4, text.c_str());
        mvwaddch(output_window, y, 25, ':');
        mvwaddstr(output_window, y, 27, format_fifo_string(pFifo).c_str());
        y++;
    };

    auto DRAW_OUTPUT_FIELD_HEX = [this,&y](std::string text, uint32_t value) {
        text.resize(20);
        mvwaddstr(output_window, y, 4, text.c_str());
        mvwaddch(output_window, y, 25, ':');
        mvwaddstr(output_window, y, 27, hexify(value).c_str());
        y++;
    };
    auto DRAW_OUTPUT_FIELD_DBL = [this,&y](std::string text, double value) {
        text.resize(20);
        mvwaddstr(output_window, y, 4, text.c_str());
        mvwaddch(output_window, y, 25, ':');
        mvwaddstr(output_window, y, 27, dbl_to_string(value).c_str());
        y++;
    };
    auto DRAW_OUTPUT_FIELD_PB = [this,&y](std::string text, PICBUF_COMP* pb, int line) {
        text.resize(20);
        mvwaddstr(output_window, y, 4, text.c_str());
        mvwaddch(output_window, y, 25, ':');
        mvwaddstr(output_window, y, 27, format_picbuf_string(pb, line).c_str());
        y++;
    };

    super_box( output_window, "Output", 5 );

    DRAW_OUTPUT_FIELD_STR ( "Capture File",             outStats.bSavingYUV?outStats.sYUVFile:"N/A" );
    DRAW_OUTPUT_FIELD_DEC ( "Frame Count",              outStats.frame_count );
    DRAW_OUTPUT_FIELD_HEX ( "DispFIFO Container",       outStats.dispFifo.uiFifoCont );
    DRAW_OUTPUT_FIELD_FIFO( "Display FIFO",             &outStats.dispFifo);

    if (outStats.frame_count > 0) {
        DRAW_OUTPUT_FIELD_DBL ( "Frame DL Time",            outStats.save_time );
        DRAW_OUTPUT_FIELD_PB  ( "Luma",                     &outStats.picInfo.lumaComp, 0 );
        DRAW_OUTPUT_FIELD_PB  ( "Luma",                     &outStats.picInfo.lumaComp, 1 );
        DRAW_OUTPUT_FIELD_PB  ( "Luma",                     &outStats.picInfo.lumaComp, 2 );

        DRAW_OUTPUT_FIELD_PB  ( "Chroma",                   &outStats.picInfo.chromaComp, 0 );
        DRAW_OUTPUT_FIELD_PB  ( "Chroma",                   &outStats.picInfo.chromaComp, 1 );
        DRAW_OUTPUT_FIELD_PB  ( "Chroma",                   &outStats.picInfo.chromaComp, 2 );
    }

    return;
}

/**
 *  Draw status panel showing the overall status of the application.
 */

void interfaceUI::draw_status_panel()
{
    const char *msg = 0L;
    char buffer[DRAW_BUFFER_SIZE];
    inputStats      inpStats;

    super_box( status_window, "Application Status", 2);

    if (pTarget && pTarget->is_connected()) {
        snprintf(buffer, DRAW_BUFFER_SIZE, "Connected to %s @ %s",
                pTarget->get_chipid().c_str(),pTarget->get_targetid().c_str());
        center_string(status_window, 2, 2, buffer);
    } else {
        center_string(status_window, 2, 2, "Not Connected");
    }

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
            sMsg = ">>>>>>> Quitting application <<<<<<<";
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

                    /* Set the Control-C atomic bool variable */
                    pStdIF->set_controlc_var(&bControlC);

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

/**
 *
 */

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

        if (opts.type == targetEngine::UCODE_DEBUG) {
            pStdIF->get_debug_state(dbgStatus);
            D(debug("state1 = %d state2 = %d\n", dbgStatus.status1, dbgStatus.status2));
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

    D(debug("-- exiting main_loop()\n"));

    return;
}

std::string interfaceUI::get_debug_string() const
{
    return get_debug_string(dbgStatus);
}

/**
 *  Return string representing the current debug state.
 */

std::string interfaceUI::get_debug_string(const debugStatus& status) const
{
    std::ostringstream  os;

    if (status.status1 == status.status2) {
        RMuint32 offset = (status.status1 != 4)?1:0;

        os << "BREAKPOINT @ " << hexify(status.rpc - offset) <<
              " stat " << hexify((RMuint16)status.rstat) <<
              " a0 " << hexify((RMuint16)status.ra0) <<
              " a1 " << hexify((RMuint16)status.ra1);
    } else {
        os << "RUNNING";
    }

    return os.str();
}
