#include <chrono>
#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../include/nf.hpp"
#include "../include/window.hpp"
#include "../include/brush.hpp"


using std::this_thread::sleep_for;
using std::chrono::microseconds;


nf::Brush::Brush(const char* texture_path, float brush_size_x, float brush_size_y) :
        Brush(texture_path, sf::Vector2f{brush_size_x, brush_size_y})
{}

nf::Brush::Brush(const char* texture_path, const sf::Vector2f brush_size) : 
        random(1.0, 1.0f)
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


void nf::Brush::setSize(const nf::Vec2& v) { this->rect.setSize({v.x, v.y}); }
void nf::Brush::setSize(int x, int y) { this->rect.setSize({x, y}); }

void nf::Brush::setColor(sf::Color color) 
{
    if (this->palette.size() == 0) 
    {
        this->rect.setFillColor(color);
        return;
    }
    auto calc_dist = [](sf::Color c1, sf::Color c2){
        return std::abs((int)c1.r - (int)c2.r) + 
            std::abs((int)c1.g - (int)c2.g) +
            std::abs((int)c1.b - (int)c2.b);
    };
    
    sf::Color r_color = nf::min_with_index(color, palette, calc_dist).second;
    this->rect.setFillColor({r_color.r, r_color.g, r_color.b, color.a});
}

void nf::Brush::setColor(uint8_t r, uint8_t g, uint8_t b) 
{ return this->setColor({r, g, b}); }
void nf::Brush::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) 
{ return this->setColor({r, g, b, a}); }

void nf::Brush::set_palette(const std::vector<sf::Color> palette) { this->palette = palette; }
void nf::Brush::set_palette(const std::vector<std::vector<uint8_t>> palette) 
{
    this->palette.clear();
    for (auto& p: palette)
    {
        p.size() == 3 ? 
            this->palette.push_back({p[0], p[1], p[2]}):
            this->palette.push_back({p[0], p[1], p[2], p[3]});
    }
}


template<typename... Args>
void nf::Brush::draw_bezier(nf::Window* window, float step, Args... points)
{
    float t = 0;
    while (t < 1)
    {
        nf::Vec2 v = nf::bezier(points..., t);
        
        this->setPosition({v.x, v.y});

        t += step * random.gen();

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
