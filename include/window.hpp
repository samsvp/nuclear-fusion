#pragma once

#include <SFML/Graphics.hpp>

#include "brush.hpp"


namespace nf
{
struct Window
{
    Window();
    ~Window();

    bool should_draw;
    Brush* brush;
    sf::Thread window_thread;
    sf::RenderWindow window;
    sf::RenderTexture canvas;

    void set_brush(Brush* brush);

    void resize();
    void main();
};
}
