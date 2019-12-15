#include <iostream>
#include <memory>

#include "GridViewer.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    {
        GridViewer grid_viewer;
        grid_viewer.loop();
    }

    SDL_Quit();

    return 0;
}
