#ifndef __INTERFACEUI_H__
#define __INTERFACEUI_H__

#include <ncurses.h>
#include <panel.h>
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

        APP_STATE           state;
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

//      time_t          startTime;
        int                 init_user_interface();
        int                 uninit_user_interface();
        int                 update_user_interface();

        void                center_string(WINDOW* win, int pair,
                                          int y, const char* str);
        void                init_colors();
        void                super_box(WINDOW* pWin, const char* sTitle,
                                      int colors);

        void                draw_status_panel();
        void                draw_input_panel();
        void                draw_output_panel();
        void                main_loop();

        optionPack          opts;

        TARGET_ENGINE_PTR   pTarget;
        TARGET_STD_IF       pStdIF;

    private:
};

#define DRAW_BUFFER_SIZE            512

#endif // __INTERFACEUI_H__
