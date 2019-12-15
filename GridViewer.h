#ifndef _GRID_VIEWER_H
#define _GRID_VIEWER_H


#include "LLCellularAutomaton.h"
#include "Window.h"


class GridViewer {
public:
    GridViewer();

    void loop();

private:
    void draw();

    Window _win;
    LLCellularAutomaton _llca;

    const int cell_width = 32;
    const int cell_height = 32;
};

#endif
