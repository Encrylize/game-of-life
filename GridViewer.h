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

    using MoveByType = std::make_signed<LLCA::GridSize>::type;
    void move_view_by(const Vector2D<MoveByType>& by);
    Vector2D<LLCA::GridSize> get_view_size() const;

    Window _win;
    LLCellularAutomaton _llca;
    Vector2D<LLCA::GridSize> _top_left;
    Vector2D<LLCA::GridSize> _view_size;
    bool _running;

    static const unsigned _cell_size;
    static const unsigned _grid_width;
};

#endif
