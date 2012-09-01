#ifndef _HELLO_H
#define _HELLO_H

#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

bool done;
int windowHeight;
int windowWidth;

int count;
ALLEGRO_FONT *font18;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;

int startup(ALLEGRO_DISPLAY *display);
int shutdown(ALLEGRO_DISPLAY *display);
void render(ALLEGRO_DISPLAY *display);

/*#define SHOWFPS
#define FULLSCREEN

#define WINDOW_WIDTH  2560
#define WINDOW_HEIGHT 1440*/

#endif
