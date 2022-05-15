#include "../include/nf.hpp"




nf::Random::Random(float low, float high)
{
    std::random_device dev;
    rng = std::mt19937(dev());
    dist = std::normal_distribution<float>(low, high);
}

float nf::Random::gen() { return dist(rng); }



nf::Vec2::Vec2() : x(0), y(0) { }
nf::Vec2::Vec2(float x, float y) : x(x), y(y) { }

nf::Vec2 nf::Vec2::rotate(float angle, bool is_degree) const
{
    if (!is_degree) angle = angle * 180 / M_PI;

    return Vec2( std::cos(angle) * this->x - std::sin(angle) * this->y,
                    std::sin(angle) * this->x + std::cos(angle) * this->y
    );
}

nf::Vec2 nf::Vec2::rotate(float angle, const nf::Vec2& center, bool is_degree) const
{
    if (is_degree) angle = angle * M_PI / 180;

    Vec2 c = *this - center;

    return Vec2( center.x + std::cos(angle) * c.x - std::sin(angle) * c.y,
                    center.y + std::sin(angle) * c.x + std::cos(angle) * c.y
    );
}
nf::Vec2 nf::Vec2::rotate(const Vec2& v, float angle, bool is_degree)
{ return v.rotate(angle, is_degree); }
nf::Vec2 nf::Vec2::rotate(const Vec2& v, float angle, const nf::Vec2& center, bool is_degree)
{ return v.rotate(angle, center, is_degree); }


nf::Vec2 nf::Vec2::operator+(const nf::Vec2& other) const
{ return nf::Vec2(this->x + other.x, this->y + other.y); }
nf::Vec2 nf::Vec2::operator-(const nf::Vec2& other) const
{ return nf::Vec2(this->x - other.x, this->y - other.y); }

nf::Vec2 nf::Vec2::operator*(const nf::Vec2& other) const
{ return nf::Vec2(this->x * other.x, this->y * other.y); }
nf::Vec2 nf::Vec2::operator*(const float& other) const
{ return nf::Vec2(this->x * other, this->y * other); }

nf::Vec2 nf::Vec2::operator/(const nf::Vec2& other) const
{ return nf::Vec2(this->x / other.x, this->y / other.y); }
nf::Vec2 nf::Vec2::operator/(const float& other) const
{ return nf::Vec2(this->x / other, this->y / other); }

nf::Vec2 operator*(float lhs, nf::Vec2 rhs) { return {lhs * rhs.x, lhs * rhs.y}; }


nf::Vec2 nf::bezier(nf::Vec2 p0, nf::Vec2 p1, float t)
{
    return p0 + t * (p1 - p0);
}


nf::Vec2 nf::bezier(nf::Vec2 p0, nf::Vec2 p1, nf::Vec2 p2, float t)
{
    float u = 1 - t;
    return std::pow(u, 2) * p0 + 2 * t * u * p1 + std::pow(t, 2) * p2;
}


nf::Vec2 nf::bezier(nf::Vec2 p0, nf::Vec2 p1, nf::Vec2 p2, nf::Vec2 p3, float t)
{
    float u = 1 - t;
    return std::pow(u, 3) * p0 + 3 * std::pow(u, 2) * t * p1 + 
        3 * u * std::pow(t, 2) * p2 + std::pow(t, 3) * p3;
}
