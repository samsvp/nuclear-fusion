#pragma once

#include <SFML/Graphics.hpp>

#include "brush.hpp"


namespace nf
{
struct Window
{
    Window();
    ~Window();

    // defines whether the window can be drawn
    bool should_draw;
    // the brush to be used to draw in the window
    Brush* brush;
    // window thread to process events
    sf::Thread window_thread;
    // current window
    sf::RenderWindow window;
    // the current canvas
    sf::RenderTexture canvas;

    /**
     * @brief Set the brush object
     * 
     * @param brush 
     */
    void set_brush(Brush* brush);

    /**
     * @brief Resizes the window
     */
    void resize();
    /**
     * @brief Main window loop. Is used in a separeted thread
     */
    void main();
};
}
