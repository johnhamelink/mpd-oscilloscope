#include "main.h"
#include "output.h"
#include "fifo.h"

using namespace std;

int main (int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_DISPLAY_MODE disp_data;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;


    setFifo();

    startup(display);

#ifdef SHOWFPS
    /**
     * We don't need any of this if we're not
     * counting FPS
     */
    count = 0;
    al_init_font_addon();
    al_init_ttf_addon();
    font18 = al_load_ttf_font("arial.ttf", 18, 0);
#endif

    timer = al_create_timer(1.0 / 42); // Set the FPS to 60
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    done = false;
    while (!done) {
        /**
         * Wait for something to happen
         * (keypress or timer, whatever comes first)
         */
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
#ifdef SHOWFPS
        count++;
#endif

        /**
         * Check for keyboard presses.
         */
        if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true; // Leave the loop
            }
        }

        getFifo(windowHeight); // Get the latest spectrum data from the FIFO
        render(display);
    }

    shutdown(display);

    return 0;
}


void render(ALLEGRO_DISPLAY *display)
{
    al_clear_to_color(al_map_rgb(0,0,0));

#ifdef SHOWFPS
    al_draw_textf(font18, al_map_rgb(255,255,255), 20, 20, ALLEGRO_ALIGN_LEFT, "Frames: %i", count);
#endif

    int halfScreen = windowHeight / 2;
    int x1 = 0;
    int x2 = 0;
    int y1, y2;
    ALLEGRO_COLOR blue = al_map_rgb(44, 117, 255);

    // Number of points is equal to the overall bytesize of freqPercent
    // divided by the size of each element.
    int numPoints = (sizeof(freqPercent) / sizeof(freqPercent[0]));

    for (int i = 0; i  <= numPoints; i++) {
        // We set the width of the bars so that they
        // will always fit inside the window (as
        // long as it's bigger than the width of the data,
        // we don't scale down).
        int x1 = i*(windowWidth / numPoints);
        int x2 = x1+(windowWidth / numPoints);
        // We set the height to the screen center + the frequency
        // size. It expans from the screen center.
        int y1 = halfScreen;
        int y2 = (y1 + freqPercent[i]);

        al_draw_line(x1, y1, x2, y2, blue, 1);
    }

    // Render
    al_flip_display();
}


int startup(ALLEGRO_DISPLAY *display)
{
    showMsg("Starting up");

    if (!al_init()) {
        return showError("Failed to initialise allegro");
    }

    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();


#ifdef FULLSCREEN
    /**
     * If we've compiled with fullscreen, then lets
     * find the resolution and match it in our width
     * and height.
     */
    showMsg("Going Fullscreen");

    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    windowWidth  = info.x2 - info.x1;
    windowHeight = info.y2 - info.y1;

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
#else
    windowWidth  = 1024;
    windowHeight = 480;
#endif

#ifdef WINDOW_WIDTH
    showMsg("Overriding width");
    windowWidth = WINDOW_WIDTH;
#endif
#ifdef WINDOW_HEIGHT
    showMsg("Overriding height");
    windowHeight = WINDOW_HEIGHT;
#endif

    char str[100];
    sprintf(str, "Set resolution to %i x %i", windowWidth, windowHeight);
    showMsg(str);
    display = al_create_display(windowWidth, windowHeight);

    if (!display) {
        return showError("Failed to create display");
    }

    return 0;
}

int shutdown(ALLEGRO_DISPLAY *display)
{
    showMsg("Shutting down.");
    al_destroy_display(display);
    return 0;
}
