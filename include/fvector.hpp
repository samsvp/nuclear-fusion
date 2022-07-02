#pragma once


#include "nf.hpp"

#include <vector>
#include <algorithm>
#include <execution>

namespace nf
{

template <typename T>
struct fvector
{
    fvector(const std::vector<T>& v);
    const std::vector<T> v;
    const std::vector<T> to_vec() const;

    template <typename Function>
    const decltype(auto) map(Function f) const
    {
        std::vector<decltype(f(this->v[0]))> v(this->v.size());

        std::transform(std::execution::par_unseq, this->v.begin(),
            this->v.end(), v.begin(), f);

        return nf::fvector(v);
    }

    template <typename Function>
    const fvector<T> filter(Function f) const;
    
    template <typename Function>
    const T reduce(Function f) const;
    template <typename Function>
    const T reduce(Function f, T init) const;


    const fvector<T> drop(int n) const;
    const fvector<T> take(int start, int finish) const;
    const T mean() const;

    template <typename Function>
    const fvector<T> merge(const fvector<T>& other, Function f) const;
    const fvector<T> operator+(const fvector<T>& other) const;

    static const nf::fvector<T> range(T start, T end, T step=1.0);
};


}



template <typename T>
nf::fvector<T>::fvector(const std::vector<T>& v) : v(v) { }

template <typename T>
const std::vector<T> nf::fvector<T>::to_vec() const 
{ 
    return this-> v; 
}


template <typename T> 
template <typename Function>
const nf::fvector<T> nf::fvector<T>::filter(Function f) const
{
    std::vector<T> v(this->v.size());

    auto it = std::copy_if(std::execution::par_unseq, this->v.begin(),
        this->v.end(), v.begin(), f);

    // shrink container to new size
    v.resize( std::distance(v.begin(), it) );
    return nf::fvector(v);
}


template <typename T> 
template <typename Function>
const T nf::fvector<T>::reduce(Function f) const
{
    return std::reduce(std::execution::par_unseq, this->v.begin(),
        this->v.end(), f);
}
template <typename T> 
template <typename Function>
const T nf::fvector<T>::reduce(Function f, T init) const
{
    return std::reduce(std::execution::par_unseq, this->v.begin(),
        this->v.end(), init, f);
}


template <typename T>
const nf::fvector<T> nf::fvector<T>::drop(int n) const
{
    std::vector<T> v = std::vector<T>(this->v.begin() + n, this->v.end());
    return nf::fvector(v);
}


template <typename T>
const nf::fvector<T> nf::fvector<T>::take(int start, int finish) const
{
    std::vector<T> v = finish > start ? 
        std::vector<T>(this->v.begin() + start, this->v.begin() + finish) :
        std::vector<T>();

    return nf::fvector(v);
}


template <typename T>
const T nf::fvector<T>::mean() const
{
    return this->reduce([](T a, T b) { return a + b; }) / this->v.size();
}


template <typename T> 
template <typename Function>
const nf::fvector<T> nf::fvector<T>::merge(const nf::fvector<T>& other, Function f) const
{
    std::vector<T> v(this->v.size());

    std::transform(std::execution::par_unseq, this->v.begin(), this->v.end(),
        other.begin(), v.begin(), f);

    return nf::fvector(v);
}


template <typename T>
const nf::fvector<T> nf::fvector<T>::operator+(const nf::fvector<T>& other) const
{
    return this->merge(other, [](T a, T b){ return a + b; });
}


template <typename T>
const nf::fvector<T> nf::fvector<T>::range(T start, T end, T step)
{
    int length = std::ceil((end - start) / static_cast<float>(step));
    std::vector<T> v(length);

    for (size_t i = 0; i < length; i++)
    {
        v[i] = i * step + start;
    }
    
    return nf::fvector(v);
}