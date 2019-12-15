#include "LLCellularAutomaton.h"


LLCellularAutomaton::LLCellularAutomaton(GridSize w, GridSize h) :
    _grid(h, GridRow(w, CellState::DEAD)), _w(w), _h(h) {}

void LLCellularAutomaton::advance() {
    Grid new_grid(_h, GridRow(_w));
    for (GridSize y = 0; y < _h; y++) {
        for (GridSize x = 0; x < _w; x++) {
            switch (get_neighborhood_sum(x, y)) {
                case 3:
                    new_grid[y][x] = CellState::ALIVE;
                    break;
                case 4:
                    new_grid[y][x] = _grid[y][x];
                    break;
                default:
                    new_grid[y][x] = CellState::DEAD;
            }
        }
    }

    _grid = new_grid;
}

LLCellularAutomaton::CellState LLCellularAutomaton::get_cell_state(
        GridSize x, GridSize y) const {
    return _grid[y][x];
}

void LLCellularAutomaton::set_cell_state(GridSize x, GridSize y,
        CellState state) {
    _grid[y][x] = state;
}

uint8_t LLCellularAutomaton::get_neighborhood_sum(GridSize x, GridSize y) const {
    uint8_t sum = 0;

    for (int8_t x_i = -1; x_i <= 1; x_i++) {
        auto x_pos = x + x_i;
        if (x_pos < 0 || x_pos >= _w) {
            continue;
        }

        for (int8_t y_i = -1; y_i <= 1; y_i++) {
            auto y_pos = y + y_i;
            if (y_pos < 0 || y_pos >= _h) {
                continue;
            }
            sum += _grid[y_pos][x_pos];
        }
    }

    return sum;
}
