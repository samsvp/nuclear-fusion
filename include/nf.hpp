#pragma once

#include <math.h>
#include <random>
#include <numeric>
#include <execution>


namespace nf
{


/**
 * @brief struct for random number generation following a 
 * normal distribution. Wrapper for std::random
 */
struct NormalRandom
{
    std::mt19937 rng;
    std::normal_distribution<float> dist;

    /**
     * @brief Construct a new NormalRandom object
     * 
     * @param low lower random distribution bound (inclusive)
     * @param high higher random distribution bound (inclusive)
     */
    NormalRandom(float low, float high);

    /**
     * @brief Generates a random number following a normal distribution
     * 
     * @return float 
     */
    float gen();
};


/**
 * @brief struct for random number generation following a 
 * uniform distribution. Wrapper for std::random
 */
struct Random
{
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

    /**
     * @brief Construct a new NormalRandom object
     * 
     * @param low lower random distribution bound (inclusive)
     * @param high higher random distribution bound (inclusive)
     */
    Random(int low, int high);

    /**
     * @brief Generates a random number following an uniform distribution
     * 
     * @return int 
     */
    int gen();
};


/**
 * @brief Type for using vectors with 2 dimensions
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

    const std::vector<float> iter();
    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;

    Vec2 operator*(const Vec2& other) const;
    Vec2 operator*(const float& other) const;
    
    Vec2 operator/(const Vec2& other) const;
    Vec2 operator/(const float& other) const;
};

/**
 * @brief Type for using vectors with 3 dimensions
 * 
 */
struct Vec3
{
    float x, y, z;
    Vec3();
    Vec3(float x, float y, float z);

    const std::vector<float> iter();
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;

    Vec3 operator*(const Vec3& other) const;
    Vec3 operator*(const float& other) const;
    
    Vec3 operator/(const Vec3& other) const;
    Vec3 operator/(const float& other) const;
};


float dist(const Vec2& v1, const Vec2& v2);
float dist(const Vec3& v1, const Vec3& v2);
float sqr_dist(const Vec2& v1, const Vec2& v2);
float sqr_dist(const Vec3& v1, const Vec3& v2);


template <typename T, typename Function>
const std::pair<int, T> min_with_index(const T& _t, const std::vector<T>& ts, Function f)
{
    int min_id = -1;
    float min_dist = 10000000;
    T t;
    for (int i=0; i<ts.size(); i++)
    {
        T curr_t = ts[i];
        float dist = f(_t, curr_t);
        if (dist < min_dist)
        {
            min_id = i;
            min_dist = dist;
            t = curr_t;
        }
    }
    return std::make_pair(min_id, t);
}



template <typename Vec>
const int assign_centroid_id(const Vec& point, std::vector<Vec> centroids)
{
    return min_with_index(point, centroids, [](Vec v1, Vec v2){ return sqr_dist(v1, v2); }).first;
}

template <typename Vec>
const std::vector<Vec> KMeans(const std::vector<Vec>& points, int k)
{

    std::vector<Vec> centroids;
    // choose random points to be the centroid
    // can be better by using the kmeans++ initialization
    Random random(0, points.size() - 1);
    for (int i = 0; i < k; i++)
    {
        int idx = random.gen();
        centroids.push_back(points[idx]);
    }
    

    for (size_t i = 0; i < 100; i++)
    {
        std::vector<std::vector<Vec>> coord_sums(k);
        // assign points to centroids
        for (auto p : points)
        {
            int id = nf::assign_centroid_id(p, centroids);
            coord_sums[id].push_back(p);
        }
        
        // update centroids
        for (size_t n = 0; n < k; n++)
        {
            centroids[n] = std::reduce(std::execution::par, 
                coord_sums[n].begin(), coord_sums[n].end()) / coord_sums[n].size();
        } 
    }
    
    return centroids;
}


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