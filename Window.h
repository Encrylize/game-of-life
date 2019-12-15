#ifndef _WINDOW_H
#define _WINDOW_H

#include <memory>
#include <SDL2/SDL.h>


// TODO: Abstract away underlying implementation more
class Window {
public:
    Window(const char* title, int x, int y, int w, int h, Uint32 flags);

    void clear();
    void update();
    void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void draw_rect(int x, int y, int w, int h);

    int get_width() const { return _width; }
    int get_height() const { return _height; }

private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _win;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _rend;

    int _width;
    int _height;
};

#endif
