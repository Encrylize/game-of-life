#include <sstream>
#include <stdexcept>

#include "Window.h"


Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags)
    : _win(nullptr, SDL_DestroyWindow), _rend(nullptr, SDL_DestroyRenderer),
    _width(w), _height(h) {
    std::stringstream error;

    _win.reset(SDL_CreateWindow(title, x, y, w, h, flags));
    if (_win == nullptr) {
        error << "Error creating window: " << SDL_GetError();
        throw std::runtime_error(error.str());
    }

    _rend.reset(SDL_CreateRenderer(_win.get(), -1, 0));
    if (_rend == nullptr) {
        error << "Error creating renderer: " << SDL_GetError();
        throw std::runtime_error(error.str());
    }
}


void Window::clear() {
    SDL_RenderClear(_rend.get());
}

void Window::update() {
    SDL_RenderPresent(_rend.get());
}

void Window::set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(_rend.get(), r, g, b, a);
}

void Window::draw_rect(int x, int y, int w, int h) {
    SDL_Rect rect{x, y, w, h};
    SDL_RenderFillRect(_rend.get(), &rect);
}
