#pragma once


#include <math.h>
#include <random>


namespace nf
{


/**
 * @brief struct for random number generation following a 
 * normal distribution. Wrapper for std::random
 */
struct Random
{
    std::mt19937 rng;
    std::normal_distribution<float> dist;

    /**
     * @brief Construct a new Random object
     * 
     * @param low lower random distribution bound
     * @param high higher random distribution bound
     */
    Random(float low, float high);

    /**
     * @brief Generates a random number following a normal distribution
     * 
     * @return float 
     */
    float gen();
};

/**
 * @brief Struct for using vectors
 * 
 */
struct Vec2
{
    float x, y;
    Vec2();
    Vec2(float x, float y);

    /**
     * @brief Rotates the given vector
     * 
     * @param angle angle to rotate the vector
     * @param is_degree defines if the angle is in degrees or radians
     * @return Vec2 
     */
    Vec2 rotate(float angle, bool is_degree=0) const;
    /**
     * @brief Rotates the vector around a point
     * 
     * @param angle angle to rotate the vector
     * @param center center of rotation
     * @param is_degree defines if the angle is in degrees or radians
     * @return Vec2 
     */
    Vec2 rotate(float angle, const Vec2& center, bool is_degree=0) const;
    static Vec2 rotate(const Vec2& v, float angle, bool is_degree=0);
    static Vec2 rotate(const Vec2& v, float angle, const Vec2& center, bool is_degree=0);

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;

    Vec2 operator*(const Vec2& other) const;
    Vec2 operator*(const float& other) const;
    
    Vec2 operator/(const Vec2& other) const;
    Vec2 operator/(const float& other) const;
};


/**
 * @brief Defines a linear bezier curve
 * 
 * @param p0 
 * @param p1 
 * @param t 
 * @return nf::Vec2 
 */
nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, float t);

/**
 * @brief Defines a quadratic bezier curve
 * 
 * @param p0 
 * @param p1 
 * @param p2 
 * @param t 
 * @return nf::Vec2 
 */
nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, nf::Vec2 p2, float t);
/**
 * @brief Defines a curbic bezier curve
 * 
 * @param p0 
 * @param p1 
 * @param p2 
 * @param p3 
 * @param t 
 * @return nf::Vec2 
 */
nf::Vec2 bezier(nf::Vec2 p0, nf::Vec2 p1, nf::Vec2 p2, nf::Vec2 p3, float t);
} // namespace nf