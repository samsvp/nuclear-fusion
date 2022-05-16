#pragma once

#include "nf.hpp"
#include <vector>
#include <SFML/Graphics.hpp>


namespace nf
{


class Window;


/**
 * @brief Painting brush class
 * 
 */
class Brush : public sf::Drawable, public sf::Transformable
{
public:

    Brush(const char* texture_path, const sf::Vector2f brush_size);
    Brush(const char* texture_path, float brush_size_x, float brush_size_y);
    ~Brush();

    /**
     * @brief Set the rect size
     * 
     * @param x 
     * @param y 
     */
    void setSize(const nf::Vec2& s);
    void setSize(int x, int y);
    /**
     * @brief Set the Color object
     * 
     * @param color 
     */
    void setColor(sf::Color color);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    /**
     * @brief Set the palette object
     * 
     * @param palette 
     */
    void set_palette(const std::vector<sf::Color> palette);
    void set_palette(const std::vector<std::vector<uint8_t>> palette);

    void draw_line(nf::Window* window, float x1, float y1, float x2, float y2, float step=0.01);
    void draw_rect(nf::Window* window, float x, float y, float w, float h, float step=0.01);
    void draw_circle(nf::Window* window, float x, float y, float r, float step=0.01);
    void draw_ellipse(nf::Window* window, float x, float y, float r1, float r2, float step=0.01);
    void draw_path(nf::Window* window, std::vector<nf::Vec2> points, float step=0.01, int n_cps=1);

    /**
     * @brief Draws a bezier curve with the given points
     * 
     * @tparam Args 
     * @param window the window to draw to
     * @param step steps to take from each draw
     * @param args points of the bezier curve
     */
    template<typename... Args>
    void draw_bezier(nf::Window* window, float step, Args... points);

private:
    std::vector<sf::Color> palette;
    nf::NormalRandom random;
    sf::Texture texture;
    sf::RectangleShape rect;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}