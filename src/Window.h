#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL.h>
#include <memory>

#include "Vector2D.h"

struct Color {
    uint8_t r, g, b, a;
};

class Window {
public:
    Window(const std::string& title, Vector2D<int> pos, Vector2D<int> size,
           uint32_t flags);

    void clear();
    void update();
    void set_draw_color(Color color);
    void draw_rect(Vector2D<int> pos, Vector2D<int> size);

    Vector2D<int> get_size() const;
    Vector2D<int> get_mouse_pos() const;

private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _win;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _rend;

    Vector2D<int> _size;
};

#endif
