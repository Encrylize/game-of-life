#ifndef _GRID_VIEWER_H
#define _GRID_VIEWER_H

#include <type_traits>

#include "LLCellularAutomaton.h"
#include "Window.h"


class GridViewer {
public:
    GridViewer();

    void loop();

private:
    void draw();

    Vector2D<LLCA::CellPos> get_view_size() const;

    Window _win;
    LLCellularAutomaton _llca;
    Vector2D<LLCA::CellPos> _top_left;
    Vector2D<LLCA::CellPos> _view_size;
    bool _running;
    unsigned _iter_per_sec;

    static const unsigned _cell_size;
    static const unsigned _grid_width;
    static const unsigned _iter_step;
};

#endif
