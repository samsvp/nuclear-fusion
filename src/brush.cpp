#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../include/nf.hpp"
#include "../include/window.hpp"


using std::this_thread::sleep_for;
using std::chrono::microseconds;


nf::Brush::Brush(const char* texture_path, float brush_size_x, float brush_size_y) :
        Brush(texture_path, sf::Vector2f{brush_size_x, brush_size_y})
{}

nf::Brush::Brush(const char* texture_path, const sf::Vector2f brush_size) 
{
    if (!this->texture.loadFromFile(texture_path))
    {
        std::cout << "Could not load the given texture" << std::endl;
    }
    texture.setSmooth(true);

    this->rect.setTexture(&this->texture);
    this->rect.setSize(brush_size);
    this->setColor(0, 0, 0, 8);
}

nf::Brush::~Brush() { }


void nf::Brush::setColor(sf::Color color) { this->rect.setFillColor(color); }
void nf::Brush::setColor(uint8_t r, uint8_t g, uint8_t b) { this->rect.setFillColor({r, g, b}); }
void nf::Brush::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { this->rect.setFillColor({r, g, b, a}); }


template<typename... Args>
void nf::Brush::draw_bezier(nf::Window* window, float step, Args... args)
{
    float t = 0;
    while (t < 1)
    {
        nf::Vec2 v = nf::bezier(args..., t);
        
        this->setPosition({v.x, v.y});

        t += step;

        window->should_draw = true;

        while (window->should_draw) 
        {
            sleep_for(microseconds(1500));
        }
    }
}


void nf::Brush::draw_line(nf::Window* window, float x1, float y1, float x2, float y2, float step)
{
    window->set_brush(this);
    this->setPosition({x1, y1});

    this->draw_bezier(window, step, nf::Vec2{x1, y1}, nf::Vec2{x2, y2});
}


void nf::Brush::draw_circle(nf::Window* window, float x, float y, float r, float step)
{
    window->set_brush(this);
    this->setPosition({x, y});

    float c = 0.552284749831;
    nf::Vec2 offset(x, y);

    // first segment
    nf::Vec2 p0 = nf::Vec2(0, r) + offset;
    nf::Vec2 p1 = nf::Vec2(r * c, r) + offset;
    nf::Vec2 p2 = nf::Vec2(r, r * c) + offset;
    nf::Vec2 p3 = nf::Vec2(r, 0) + offset;

    this->draw_bezier(window, step, p0, p1, p2, p3);
    this->draw_bezier(window, step, p0.rotate(270, offset, 1), 
        p1.rotate(270, offset, 1), p2.rotate(270, offset, 1), p3.rotate(270, offset, 1));
    this->draw_bezier(window, step, p0.rotate(180, offset, 1), 
        p1.rotate(180, offset, 1), p2.rotate(180, offset, 1), p3.rotate(180, offset, 1));
    this->draw_bezier(window, step, p0.rotate(90, offset, 1), 
        p1.rotate(90, offset, 1), p2.rotate(90, offset, 1), p3.rotate(90, offset, 1));
}


void nf::Brush::draw_ellipse(nf::Window* window, float x, float y, float rx, float ry, float step)
{
    window->set_brush(this);
    this->setPosition({x, y});

    float c = 0.552284749831;
    nf::Vec2 offset(x, y);

    // first segment
    nf::Vec2 p0 = nf::Vec2(0, ry) + offset;
    nf::Vec2 p1 = nf::Vec2(ry * c, ry) + offset;
    nf::Vec2 p2 = nf::Vec2(rx, rx * c) + offset;
    nf::Vec2 p3 = nf::Vec2(rx, 0) + offset;

    this->draw_bezier(window, step, p0, p1, p2, p3);
    this->draw_bezier(window, step, p0.rotate(180, offset, 1), 
        p1.rotate(180, offset, 1), p2.rotate(180, offset, 1), p3.rotate(180, offset, 1));

    // second segment
    p0 = nf::Vec2(rx, 0) + offset;
    p1 = nf::Vec2(rx, -rx*c) + offset;
    p2 = nf::Vec2(ry * c, -ry) + offset;
    p3 = nf::Vec2(0, -ry) + offset;

    this->draw_bezier(window, step, p0, p1, p2, p3);
    this->draw_bezier(window, step, p0.rotate(180, offset, 1), 
        p1.rotate(180, offset, 1), p2.rotate(180, offset, 1), p3.rotate(180, offset, 1));

}


void nf::Brush::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    states.texture = &texture;

    // draw the vertex array
    target.draw(this->rect, states);
}
