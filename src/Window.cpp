#include <sstream>
#include <stdexcept>

#include "Window.h"

Window::Window(const std::string& title, Vector2D<int> pos, Vector2D<int> size,
               uint32_t flags)
    : _win(nullptr, SDL_DestroyWindow),
      _rend(nullptr, SDL_DestroyRenderer),
      _size(size) {
    std::stringstream error;

    _win.reset(
        SDL_CreateWindow(title.c_str(), pos.x, pos.y, size.x, size.y, flags));
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

void Window::draw_rect(Vector2D<int> pos, Vector2D<int> size) {
    SDL_Rect rect{pos.x, pos.y, size.x, size.y};
    SDL_RenderFillRect(_rend.get(), &rect);
}

Vector2D<int> Window::get_size() const {
    return _size;
}
