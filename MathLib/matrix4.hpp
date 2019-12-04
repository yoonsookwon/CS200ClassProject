#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
#include "vector3.hpp"
#include  "vector4.hpp"

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
    constexpr matrix4(vector4<T> first_column, vector4<T> second_column, vector4<T> third_column, vector4<T> fourth_column) noexcept;
    constexpr matrix4(T column0_row0, T column0_row1, T column0_row2, T column0_row3, T column1_row0, T column1_row1,
        T column1_row2, T column1_row3, T column2_row0, T column2_row1, T column2_row2, T column2_row3, T column3_row0,
        T column3_row1, T column3_row2, T column3_row3) noexcept;

    constexpr T  operator()(T column, T row) const noexcept;
    constexpr T& operator()(T column, T row) noexcept;
};

//static_assert(sizeof(matrix3<T>) == sizeof(float) * 3 * 3, "matrix3 should be 3x3 floats");

template <typename T>
constexpr matrix4<T> operator*(const matrix4<T>& m1, const matrix4<T>& m2) noexcept;

template <typename T>
constexpr void    operator*=(matrix4<T>& m1, const matrix4<T>& m2) noexcept;

template <typename T>
constexpr vector4<T> operator*(const matrix4<T>& m, vector4<T> v) noexcept;

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
    constexpr matrix4<T> build_scale(float scale_x, float scale_y, float scale_z) noexcept;

    template <typename T>
    constexpr matrix4<T> build_scale(float scale) noexcept;

    template <typename T>
    constexpr matrix4<T> build_scale(const vector3<T>& scale) noexcept;

    template <typename T>
    constexpr matrix4<T> build_translation(float translate_x, float translate_y, float translate_z) noexcept;

    template <typename T>
    constexpr matrix4<T> build_translation(const vector3<T>& translation) noexcept;
}


#pragma warning(pop)
#include <cassert>
#include <limits>
#include "vector2.hpp"
#include "vector4.hpp"
#include "matrix4.inl"
