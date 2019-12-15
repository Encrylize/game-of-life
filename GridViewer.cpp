#include "GridViewer.h"


GridViewer::GridViewer() :
    _win("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0),
    _llca(128, 128) {
    // Spinner
#if 0
    _llca.set_cell_state(1, 3, LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(2, 3, LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(3, 3, LLCellularAutomaton::CellState::ALIVE);
#endif

    // Glider
    _llca.set_cell_state(0, 2, LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(1, 3, LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(2, 1, LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(2, 2, LLCellularAutomaton::CellState::ALIVE);
    _llca.set_cell_state(2, 3, LLCellularAutomaton::CellState::ALIVE);
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

    for (LLCellularAutomaton::GridSize x = 0; x < _llca.get_width(); x++) {
        if ((int) x * cell_width > _win.get_width()) {
            break;
        }

        for (LLCellularAutomaton::GridSize y = 0; y < _llca.get_height(); y++) {
            if ((int) y * cell_height > _win.get_height()) {
                break;
            }

            if (_llca.get_cell_state(x, y) == LLCellularAutomaton::CellState::ALIVE) {
                _win.set_draw_color(0, 0, 0, 0);
            } else {
                _win.set_draw_color(255, 255, 255, 255);
            }

            _win.draw_rect((int) x * cell_width, (int) y * cell_height,
                cell_width, cell_height);
        }
    }

    _win.update();
}
