#ifndef __INTERFACEUI_H__
#define __INTERFACEUI_H__

#if (__cplusplus < 201103L)
#pragma GCC error "Must be compiled with C++11 support!"
#endif

#include <ncurses.h>
#include <panel.h>
#include <chrono>
#include <iomanip>

#include "targetEngine.h"
#include "targetStandardInterface.h"
#include "utils.h"
#include "optionparser.h"

typedef struct _rectangle {
	int x, y;
	int w, h;
} RECT;

#define SET_RECT( rect, X, Y, W, H )                                            \
    rect.x = X;                                                                 \
    rect.y = Y;                                                                 \
    rect.w = W;                                                                 \
    rect.h = H;


#define UIRESULT_OK         0
#define UIRESULT_FAIL       -1

/**
 *
 */

class interfaceUI
{
    public:

        typedef enum _appState {
            APP_STATE_UNKNOWN,
            APP_INITIALIZING,
            APP_LOADING_MICROCODE,
            APP_SENDING_UNINIT,
            APP_SENDING_INIT,
            APP_SENDING_PLAY,
            APP_SENDING_STOP,
            APP_PLAYING,
        } APP_STATE;

        interfaceUI();
        virtual ~interfaceUI();

        bool                open(int argc, char* argv[]);
        bool                close();
        bool                run();

    protected:


        using TIME_POINT =  std::chrono::time_point<std::chrono::system_clock>;
//        typedef std::chrono::time_point<std::chrono::system_clock> TIME_POINT;

        typedef enum _flags {
            FLAG_SAVING_YUV          = (1L << 0),
            FLAG_QUIT_IN_PROGRESS    = (1L << 1),
        } FLAGS;

        APP_STATE           state;
        int                 flags;

        int                 screenx;
        int                 screeny;
        int                 maxlines;

        RECT                status_rect;
        WINDOW*             status_window;
        PANEL*              status_panel;

        RECT                input_rect;
        WINDOW*             input_window;
        PANEL*              input_panel;

        RECT                output_rect;
        WINDOW*             output_window;
        PANEL*              output_panel;

        void                host_interrupt();

        /* User interface functions. */
        int                 init_user_interface();
        int                 uninit_user_interface();
        int                 update_user_interface();

        /* Curses utility functions. */
        void                center_string(WINDOW* win, int pair,
                                          int y, const char* str);
        void                init_colors();
        void                super_box(WINDOW* pWin, const char* sTitle,
                                      int colors);
        void                clear_line(WINDOW* pWin, int line);
        void                draw_status_panel();
        void                draw_input_panel();
        void                draw_output_panel();
        void                main_loop();

        std::string         get_debug_string() const;
        std::string         get_debug_string(const debugStatus& status) const;

        optionPack          opts;

        TARGET_ENGINE_PTR   pTarget;
        TARGET_STD_IF       pStdIF;

        inputStats          inStats;
        outputStats         outStats;
        debugStatus         dbgStatus;

        TIME_POINT          start;

    private:
};


#define     SET_FLAG(x)     flags |= (x)
#define     CLEAR_FLAG(x)   flags &= ~(x)
#define     TEST_FLAG(x)    ((flags & (x)) != 0)


#define     DRAW_BUFFER_SIZE            512


template< typename T >
std::string hexify(T i)
{
    std::stringbuf buf;
    std::ostream os(&buf);

    os << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
       << std::uppercase << std::hex << i;

    return buf.str().c_str();
}

template <typename T>
std::string to_string(T const& value) {
    std::stringstream sstr;
    sstr << value;
    return sstr.str();
}
#endif // __INTERFACEUI_H__
