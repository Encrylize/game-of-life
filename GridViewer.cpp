#include "GridViewer.h"


const unsigned GridViewer::_cell_size = 32;


GridViewer::GridViewer() :
    _win("Title",
            Vector2D<int>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED),
            Vector2D<int>(640, 480), 0),
    _llca("B3/S23", Vector2D<LLCA::GridSize>(32, 32)), _top_left(0, 0),
    _view_size(_win.get_size() / _cell_size) {
    // Glider
    //_llca.set_cell_state(Vector2D<LLCA::GridSize>(0, 2), LLCA::CellState::ALIVE);
    //_llca.set_cell_state(Vector2D<LLCA::GridSize>(1, 3), LLCA::CellState::ALIVE);
    //_llca.set_cell_state(Vector2D<LLCA::GridSize>(2, 1), LLCA::CellState::ALIVE);
    //_llca.set_cell_state(Vector2D<LLCA::GridSize>(2, 2), LLCA::CellState::ALIVE);
    //_llca.set_cell_state(Vector2D<LLCA::GridSize>(2, 3), LLCA::CellState::ALIVE);

    // Blinker
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(1, 0), LLCA::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(1, 1), LLCA::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(1, 2), LLCA::CellState::ALIVE);

    // Blinker
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(30, 0), LLCA::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(30, 1), LLCA::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(30, 2), LLCA::CellState::ALIVE);

    // Blinker
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(1, 29), LLCA::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(1, 30), LLCA::CellState::ALIVE);
    _llca.set_cell_state(Vector2D<LLCA::GridSize>(1, 31), LLCA::CellState::ALIVE);
}

// TODO: FPS
void GridViewer::loop() {
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                return;
            } else if (event.type == SDL_KEYDOWN) {
                Vector2D<MoveByType> move_by(
                        (event.key.keysym.sym == SDLK_l)
                            - (event.key.keysym.sym == SDLK_h),
                        (event.key.keysym.sym == SDLK_j)
                            - (event.key.keysym.sym == SDLK_k));
                move_view_by(move_by);
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

    for (LLCA::GridSize x = 0; x < _view_size.x; x++) {
        for (LLCA::GridSize y = 0; y < _view_size.y; y++) {
            auto cell_pos = _top_left + Vector2D<LLCA::GridSize>(x, y);
            if (_llca.get_cell_state(cell_pos) == LLCA::CellState::ALIVE) {
                _win.set_draw_color(0, 0, 0, 0);
            } else {
                _win.set_draw_color(255, 255, 255, 255);
            }

            _win.draw_rect(
                    Vector2D<int>(x * _cell_size, y * _cell_size),
                    Vector2D<int>(_cell_size, _cell_size));
        }
    }

    _win.update();
}

void GridViewer::move_view_by(const Vector2D<MoveByType>& by) {
    // This is pretty ugly, but I can't think of a better
    // way that isn't susceptible to overflow or underflow.
    auto grid_size = _llca.get_size();
    auto max_top_left = grid_size - _view_size;

    auto constrain_coord = [](auto by, auto& top_left, auto max_top_left) {
        if (by < 0 && (LLCA::GridSize) std::abs(by) > top_left) {
            top_left = 0;
        } else if (by > 0 && (LLCA::GridSize) by > max_top_left - top_left) {
            top_left = max_top_left;
        } else {
            top_left += by;
        }
    };

    constrain_coord(by.x, _top_left.x, max_top_left.x);
    constrain_coord(by.y, _top_left.y, max_top_left.y);
}
