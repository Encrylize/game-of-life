#ifndef _LL_CELLULAR_AUTOMATON_H
#define _LL_CELLULAR_AUTOMATON_H

#include <string>
#include <vector>

#include "Vector2D.h"


// Follows standard Game of Life rules for now
// TODO: Implement rulestrings
class LLCellularAutomaton {
public:
    enum CellState {
        DEAD = 0,
        ALIVE = 1
    };

private:
    using GridRow = std::vector<CellState>;
    using Grid = std::vector<GridRow>;

public:
    using GridSize = Grid::size_type;

    LLCellularAutomaton(Vector2D<GridSize> size);

    void advance();

    CellState get_cell_state(Vector2D<GridSize> pos) const;
    void set_cell_state(Vector2D<GridSize> pos, CellState state);

    void print_grid() const;

    Vector2D<GridSize> get_size() const;

private:
    uint8_t get_neighborhood_sum(Vector2D<GridSize> pos) const;

    Grid _grid;
    Vector2D<GridSize> _size;
};

using LLCA = LLCellularAutomaton;

#endif
