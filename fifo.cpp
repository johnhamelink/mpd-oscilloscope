#include "fifo.h"

using namespace std;

void setFifo()
{
    fifo = open("/home/john/.mpd/mpd.fifo", O_RDONLY | O_NONBLOCK);
}

int* getFifo(int windowHeight)
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
