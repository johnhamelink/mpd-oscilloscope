#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

bool done;
int windowHeight;
int windowWidth;

int fifo;
int freqPercent[1024];
unsigned *frequencyMagnitude;

int count;
ALLEGRO_FONT *font18;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;

int startup(ALLEGRO_DISPLAY *display, ALLEGRO_DISPLAY_MODE disp_data);
int shutdown(ALLEGRO_DISPLAY *display);
void render(ALLEGRO_DISPLAY *display);
void setFifo();
int* getFifo();

/*#define SHOWFPS */
/*#define FULLSCREEN*/
