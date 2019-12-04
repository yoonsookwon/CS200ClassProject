/*
 * Rudy Castan
 * Math Library
 * CS230
 */
#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
template<typename T>
struct [[nodiscard]] vector4
{
    union {
        struct
        {
            T x, y, z, w;
        };
        struct
        {
            T r, g, b, a;
        };
        struct
        {
            T width, height, depth, ww;
        };
        T elements[4];
    };

    vector4() noexcept;
    explicit vector4(T repeated_float) noexcept;
    vector4(T fx, T fy, T fz, T fw) noexcept;
};

template<typename T>
constexpr void operator+=(vector4<T>& v, const vector4<T>& adding_vector) noexcept;
template<typename T>
constexpr void operator-=(vector4<T>& v, const vector4<T>& subtracting_vector) noexcept;
template<typename T>
constexpr void operator*=(vector4<T>& v, float scale) noexcept;
template<typename T>
constexpr void operator/=(vector4<T>& v, float divisor) noexcept;

template<typename T>
constexpr vector4<T> operator-(const vector4<T>& v) noexcept;

template<typename T>
constexpr vector4<T> operator+(const vector4<T>& v1, const vector4<T>& v2) noexcept;
template<typename T>
constexpr vector4<T> operator-(const vector4<T>& v1, const vector4<T>& v2) noexcept;
template<typename T>
constexpr vector4<T> operator*(const vector4<T>& v, float scale) noexcept;
template<typename T>
constexpr vector4<T> operator*(float scale, const vector4<T>& v) noexcept;
template<typename T>
constexpr vector4<T> operator/(const vector4<T>& v, float divisor) noexcept;

template<typename T>
constexpr bool operator==(const vector4<T>& v1, const vector4<T>& v2) noexcept;
template<typename T>
constexpr bool operator!=(const vector4<T>& v1, const vector4<T>& v2) noexcept;


template<typename T>
constexpr float dot(vector4<T> a, vector4<T> b) noexcept;
template<typename T>
constexpr vector4<T>             cross(vector4<T> a, vector4<T> b) noexcept;
template<typename T>
constexpr float magnitude_squared(vector4<T> a) noexcept;
template<typename T>
constexpr float magnitude(vector4<T> a) noexcept;
template<typename T>
constexpr vector4<T>             normalize(vector4<T> a) noexcept;
template<typename T>
constexpr float distance_between_squared(vector4<T> a, vector4<T> b) noexcept;
template<typename T>
constexpr float distance_between(vector4<T> a, vector4<T> b) noexcept;
template<typename T>
constexpr float angle_between(vector4<T> a, vector4<T> b) noexcept;

#pragma warning(pop)
#include <cassert>
#include <limits>
#include "vector4.inl"