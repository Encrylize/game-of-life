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
    void zoom(float factor);

    Vector2D<LLCA::CellPos> get_view_size() const;
    float get_max_zoom() const;
    unsigned get_cell_size() const;
    unsigned get_grid_width() const;
    Vector2D<LLCA::CellPos> screen_to_cell_pos(Sint32 x, Sint32 y) const;

    Window _win;
    LLCellularAutomaton _llca;
    Vector2D<LLCA::CellPos> _top_left;
    bool _running;
    unsigned _iter_per_sec;
    float _zoom_factor;
    bool _drawing;
    LLCA::CellState _draw_state;

    const float _max_zoom;

    static const unsigned _cell_size;
    static const unsigned _grid_width;
    static const unsigned _iter_step;
    static const float _zoom_step;
    static const float _min_zoom;
};

#endif
