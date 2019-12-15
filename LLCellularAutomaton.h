#ifndef _LL_CELLULAR_AUTOMATON_H
#define _LL_CELLULAR_AUTOMATON_H

#include <string>
#include <vector>

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
    using GridSize = Grid::size_type;

public:
    LLCellularAutomaton(GridSize w, GridSize h);

    void advance();

    CellState get_cell_state(GridSize x, GridSize y) const;
    void set_cell_state(GridSize x, GridSize y, CellState state);

    void print_grid() const;

private:
    uint8_t get_neighborhood_sum(GridSize x, GridSize y) const;

    Grid _grid;
    GridSize _w, _h;
};

#endif
