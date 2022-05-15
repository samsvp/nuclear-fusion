#pragma once


#include <math.h>
#include <random>


namespace nf
{


struct Random
{
    std::mt19937 rng;
    std::normal_distribution<float> dist;

    Random(float low, float high);

    float gen();
};

struct Vec2
{
    float x, y;
    Vec2();
    Vec2(float x, float y);

    Vec2 rotate(float angle, bool is_degree=0);


    Vec2 rotate(float angle, const Vec2& center, bool is_degree=0);


    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;

    Vec2 operator*(const Vec2& other) const;
    Vec2 operator*(const float& other) const;
    
    Vec2 operator/(const Vec2& other) const;
    Vec2 operator/(const float& other) const;
};


nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, float t);
nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, nf::Vec2 p2, float t);
nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, nf::Vec2 p2, nf::Vec2 p3, float t);
} // namespace nf