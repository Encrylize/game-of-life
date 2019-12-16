#include "GridViewer.h"


const int GridViewer::_cell_size = 32;


GridViewer::GridViewer() :
    _win("Title",
            Vector2D<int>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED),
            Vector2D<int>(640, 480), 0),
    _llca(Vector2D<LLCellularAutomaton::GridSize>(128, 128)) {
    // Spinner
#if 0
    _llca.set_cell_state(1, 3, LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(2, 3, LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(3, 3, LLCellularAutomaton::CellState::ALIVE);
#endif

    // Glider
    _llca.set_cell_state(Vector2D<LLCellularAutomaton::GridSize>(0, 2),
            LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCellularAutomaton::GridSize>(1, 3),
            LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCellularAutomaton::GridSize>(2, 1),
            LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCellularAutomaton::GridSize>(2, 2),
            LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCellularAutomaton::GridSize>(2, 3),
            LLCellularAutomaton::CellState::ALIVE);
}

// TODO: FPS
void GridViewer::loop() {
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }

        _llca.advance();
        draw();
        SDL_Delay(150);
    }
}

void GridViewer::draw() {
    _win.set_draw_color(255, 255, 255, 255);
    _win.clear();

    auto grid_size = _llca.get_size();
    auto win_size = _win.get_size();

    for (LLCellularAutomaton::GridSize x = 0; x < grid_size.x; x++) {
        if ((int) x * _cell_size > win_size.x) {
            break;
        }

        for (LLCellularAutomaton::GridSize y = 0; y < grid_size.y; y++) {
            if ((int) y * _cell_size > win_size.y) {
                break;
            }

            auto cell_pos = Vector2D<LLCellularAutomaton::GridSize>(x, y);
            if (_llca.get_cell_state(cell_pos) ==
                    LLCellularAutomaton::CellState::ALIVE) {
                _win.set_draw_color(0, 0, 0, 0);
            } else {
                _win.set_draw_color(255, 255, 255, 255);
            }

            _win.draw_rect(
                    Vector2D<int>((int) x * _cell_size, (int) y * _cell_size),
                    Vector2D<int>(_cell_size, _cell_size));
        }
    }

    _win.update();
}
