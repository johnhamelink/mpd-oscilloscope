#ifndef _FIFO_H
#define _FIFO_H

#include "config.h"
#include <fstream>
#include <allegro5/allegro.h>

int fifo;
int freqPercent[1024];
unsigned *frequencyMagnitude;

void setFifo();
int* getFifo(int windowHeight);

#endif
