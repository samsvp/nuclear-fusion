#pragma once


#include <math.h>

namespace nf
{

struct Vec2
{
    float x, y;
    Vec2() : x(0), y(0) { }
    Vec2(float x, float y) : x(x), y(y) { }

    Vec2 rotate(float angle, bool is_degree=0)
    {
        if (!is_degree) angle = angle * 180 / M_PI;

        return Vec2( std::cos(angle) * this->x - std::sin(angle) * this->y,
                     std::sin(angle) * this->x + std::cos(angle) * this->y
        );
    }


    Vec2 rotate(float angle, const Vec2& center, bool is_degree=0)
    {
        if (is_degree) angle = angle * M_PI / 180;

        Vec2 c = *this - center;

        return Vec2( center.x + std::cos(angle) * c.x - std::sin(angle) * c.y,
                     center.y + std::sin(angle) * c.x + std::cos(angle) * c.y
        );
    }


    Vec2 operator+(const Vec2& other) const
    { return Vec2(this->x + other.x, this->y + other.y); }
    Vec2 operator-(const Vec2& other) const
    { return Vec2(this->x - other.x, this->y - other.y); }

    Vec2 operator*(const Vec2& other) const
    { return Vec2(this->x * other.x, this->y * other.y); }
    Vec2 operator*(const float& other) const
    { return Vec2(this->x * other, this->y * other); }
    
    Vec2 operator/(const Vec2& other) const
    { return Vec2(this->x / other.x, this->y / other.y); }
    Vec2 operator/(const float& other) const
    { return Vec2(this->x / other, this->y / other); }
};

Vec2 operator*(float lhs, Vec2 rhs) { return {lhs * rhs.x, lhs * rhs.y}; }


nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, float t)
{
    return p0 + t * (p1 - p0);
}


nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, nf::Vec2 p2, float t)
{
    float u = 1 - t;
    return std::pow(u, 2) * p0 + 2 * t * u * p1 + std::pow(t, 2) * p2;
}


nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, nf::Vec2 p2, nf::Vec2 p3, float t)
{
    float u = 1 - t;
    return std::pow(u, 3) * p0 + 3 * std::pow(u, 2) * t * p1 + 
        3 * u * std::pow(t, 2) * p2 + std::pow(t, 3) * p3;
}

} // namespace nf