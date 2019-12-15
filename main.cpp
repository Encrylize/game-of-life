#include <iostream>
#include <memory>

#include "LLCellularAutomaton.h"
#include "Window.h"

int main() {
#if 0
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    auto win = std::make_unique<Window>(
            "Title",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            640, 480,
            0);

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                // Window needs to be deleted before quitting SDL to prevent
                // memory leaks.
                win = nullptr;
                SDL_Quit();
                return 0;
            }
        }

        win->clear();

        win->set_draw_color(255, 255, 255, 255);
        win->draw_rect(200, 100, 64, 128);
        win->set_draw_color(0, 0, 0, 255);

        win->update();
    }
#endif

    LLCellularAutomaton llca(5, 5);

    // Create spinner
    llca.set_cell_state(1, 2, LLCellularAutomaton::CellState::ALIVE);
    llca.set_cell_state(2, 2, LLCellularAutomaton::CellState::ALIVE);
    llca.set_cell_state(3, 2, LLCellularAutomaton::CellState::ALIVE);

    for (int i = 0; i < 5; i++) {
        std::cout << "Generation " << i << std::endl;
        llca.print_grid();
        llca.advance();
    }
}
