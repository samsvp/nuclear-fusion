#include "../include/nf.hpp"


nf::NormalRandom::NormalRandom(float low, float high)
{
    std::random_device dev;
    rng = std::mt19937(dev());
    dist = std::normal_distribution<float>(low, high);
}

float nf::NormalRandom::gen() { return dist(rng); }


nf::Random::Random(int low, int high)
{
    std::random_device dev;
    rng = std::mt19937(dev());
    dist = std::uniform_int_distribution<int>(low, high);
}

int nf::Random::gen() { return dist(rng); }



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

const std::vector<float> nf::Vec2::iter() { return {x, y}; }

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



nf::Vec3::Vec3() : x(0), y(0), z(0) { }
nf::Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) { }

const std::vector<float> nf::Vec3::iter() { return {x, y, z}; }

nf::Vec3 nf::Vec3::operator+(const nf::Vec3& other) const
{ return nf::Vec3(this->x + other.x, this->y + other.y, this->z + other.z); }
nf::Vec3 nf::Vec3::operator-(const nf::Vec3& other) const
{ return nf::Vec3(this->x - other.x, this->y - other.y, this->z - other.z); }

nf::Vec3 nf::Vec3::operator*(const nf::Vec3& other) const
{ return nf::Vec3(this->x * other.x, this->y * other.y, this->z * other.z); }
nf::Vec3 nf::Vec3::operator*(const float& other) const
{ return nf::Vec3(this->x * other, this->y * other, this->z * other); }

nf::Vec3 nf::Vec3::operator/(const nf::Vec3& other) const
{ return nf::Vec3(this->x / other.x, this->y / other.y, this->z / other.z); }
nf::Vec3 nf::Vec3::operator/(const float& other) const
{ return nf::Vec3(this->x / other, this->y / other, this->z / other); }

nf::Vec3 operator*(float lhs, nf::Vec3 rhs) { return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z}; }


float nf::dist(const nf::Vec2& v1, const nf::Vec2& v2)
{ return std::sqrt(nf::sqr_dist(v1, v2)); }
float nf::dist(const nf::Vec3& v1, const nf::Vec3& v2)
{ return std::sqrt(nf::sqr_dist(v1, v2)); }
float nf::sqr_dist(const nf::Vec2& v1, const nf::Vec2& v2)
{ return std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2); }
float nf::sqr_dist(const nf::Vec3& v1, const nf::Vec3& v2)
{ return std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2) + std::pow(v1.z - v2.z, 2); }


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
