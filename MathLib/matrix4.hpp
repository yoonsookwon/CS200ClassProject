#pragma once
#include "vector4.hpp"
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
/**
 * \brief 4x4 matrix
 */
template <typename T>
struct [[nodiscard]] matrix4
{
public:
union {
T elements[4][4];
struct
{
vector4<T> column0;
vector4<T> column1;
vector4<T> column2;
vector4<T> column3;
};
};

public:
constexpr matrix4() noexcept;
constexpr matrix4(T column0_row0, T column0_row1, T column0_row2, T column0_row3,T column1_row0, T column1_row1,
    T column1_row2, T column1_row3,T column2_row0, T column2_row1, T column2_row2, T column2_row3, T column3_row0, T column3_row1, T column3_row2, T column3_row3) noexcept;

constexpr T  operator()(int column, int row) const noexcept;
constexpr T& operator()(int column, int row) noexcept;
};

template <typename T>
constexpr matrix4<T> operator*(const matrix4<T>& m1, const matrix4<T>& m2) noexcept;
template <typename T>
constexpr void    operator*=(matrix4<T>& m1, const matrix4<T>& m2) noexcept;



template <typename T>
struct vector2;
namespace MATRIX4
{
    template <typename T>
    constexpr matrix4<T> transpose(const matrix4<T>& m) noexcept;
    template <typename T>
    constexpr matrix4<T> build_rotation(float angle_in_radians) noexcept;
    template <typename T>
    constexpr matrix4<T> build_identity() noexcept;
    template <typename T>
    constexpr matrix4<T> build_scale(float scale_x, float scale_y) noexcept;
    template <typename T>
    constexpr matrix4<T> build_scale(float scale) noexcept;
    template <typename T>
    constexpr matrix4<T> build_scale(const vector2<T>& scale) noexcept;
    template <typename T>
    constexpr matrix4<T> build_translation(float translate_x, float translate_y) noexcept;
}


#pragma warning(pop)
#include "vector2.hpp"
#include <cassert>
#include <limits>
#include "matrix4.inl"