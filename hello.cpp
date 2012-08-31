#ifndef _HELLO_H
#define _HELLO_H
#include "hello.h"
#endif

#ifndef _OUTPUT_H
#define _OUTPUT_H
#include "output.h"
#endif

using namespace std;

int main (int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_DISPLAY_MODE disp_data;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

#ifdef SHOWFPS
    /**
     * We don't need any of this if we're not
     * counting FPS
     */
    count = 0;
    al_init_font_addon();
    al_init_ttf_addon();
    font18 = al_load_font("arial.ttf", 18, 0);
#endif

    setFifo();

    startup(display, disp_data);

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

        getFifo(); // Get the latest spectrum data from the FIFO
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
    int numPoints = (sizeof(freqPercent) / sizeof(freqPercent[0]));

    for (int i = 0; (i-1)  <= numPoints; i = (i+2)) {
        int x = i;
        int y = (halfScreen + freqPercent[i]);
        al_draw_line(x, halfScreen, x, y, blue, 1);
    }

    al_flip_display();
}


int startup(ALLEGRO_DISPLAY *display, ALLEGRO_DISPLAY_MODE disp_data)
{
    showMsg("Starting up");

    if (!al_init()) {
        return showError("Failed to initialise allegro");
    }

    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();

    windowWidth  = 1024;
    windowHeight = 480;

#ifdef FULLSCREEN
    /**
     * If we've compiled with fullscreen, then lets
     * find the resolution and match it in our width
     * and height.
     */
    al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
    windowHeight = disp_data.height;
    windowWidth = disp_data.width;
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
#endif

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

void setFifo()
{
    fifo = open("/home/john/.mpd/mpd.fifo", O_RDONLY | O_NONBLOCK);
}

int* getFifo()
{
    int16_t buf[1024];
    ssize_t data = read(fifo, &buf, sizeof(buf));
    if (data != -1) {
        for (int i = 0; i < 1024; i++) {
            freqPercent[i] = (buf[i] / 2e4) * (windowHeight / 5);
        }
    }

    return freqPercent;
}
