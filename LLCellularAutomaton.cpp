#include <iostream>

#include "LLCellularAutomaton.h"


LLCellularAutomaton::LLCellularAutomaton(Vector2D<GridSize> size) :
    _grid(size.y, GridRow(size.x, CellState::DEAD)), _size(size) {}

void LLCellularAutomaton::advance() {
    Grid new_grid(_size.y, GridRow(_size.x));
    for (GridSize y = 0; y < _size.y; y++) {
        for (GridSize x = 0; x < _size.x; x++) {
            switch (get_neighborhood_sum(Vector2D<GridSize>(x, y))) {
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
        Vector2D<GridSize> pos) const {
    return _grid[pos.y][pos.x];
}

void LLCellularAutomaton::set_cell_state(Vector2D<GridSize> pos,
        CellState state) {
    _grid[pos.y][pos.x] = state;
}

void LLCellularAutomaton::print_grid() const {
    for (auto& row : _grid) {
        for (auto cell_state : row) {
            std::cout << (cell_state == CellState::ALIVE ? "X" : "O");
        }

        std::cout << std::endl;
    }
}

Vector2D<LLCellularAutomaton::GridSize> LLCellularAutomaton::get_size() const {
    return _size;
}

uint8_t LLCellularAutomaton::get_neighborhood_sum(Vector2D<GridSize> pos)
    const {
    uint8_t sum = 0;

    for (int8_t x_i = -1; x_i <= 1; x_i++) {
        auto x = pos.x + x_i;
        if (x < 0 || x >= _size.x) {
            continue;
        }

        for (int8_t y_i = -1; y_i <= 1; y_i++) {
            auto y = pos.y + y_i;
            if (y < 0 || y >= _size.y) {
                continue;
            }
            sum += _grid[y][x];
        }
    }

    return sum;
}
