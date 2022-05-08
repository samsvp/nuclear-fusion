#pragma once

#include <SFML/Graphics.hpp>


namespace nf
{

class Window;
class Vec2;


class Brush : public sf::Drawable, public sf::Transformable
{
public:

    Brush(const char* texture_path, const sf::Vector2f brush_size);
    Brush(const char* texture_path, float brush_size_x, float brush_size_y);
    ~Brush();


    void setColor(sf::Color color);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void draw_line(nf::Window* window, float x1, float y1, float x2, float y2, float step=0.01);
    void draw_rect(nf::Window* window, float x, float y, float w, float h, float step=0.01);
    void draw_circle(nf::Window* window, float x, float y, float r, float step=0.01);
    void draw_ellipse(nf::Window* window, float x, float y, float r1, float r2, float step=0.01);
    void draw_path(nf::Window* window, std::vector<nf::Vec2> points, float step=0.01, int n_cps=1);

    template<typename... Args>
    void draw_bezier(nf::Window* window, float step, Args... args);

private:
    sf::Texture texture;
    sf::RectangleShape rect;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}