/************************************************
 *NAME              : yoonsoo.kwon
 *ASSIGNMENT NUMBER : 1
 *COURSE NAME       : CS230
 *TERM              : Spring 2019
 ************************************************/

template <typename T>
vector4<T>::vector4() noexcept
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}
template <typename T>
vector4<T>::vector4(T repeated_float) noexcept
{
    x = repeated_float;
    y = repeated_float;
    z = repeated_float;
    w = repeated_float;
}
template <typename T>
vector4<T>::vector4(T fx, T fy, T fz ,T fw) noexcept
{
    x = fx;
    y = fy;
    z = fz;
    w = fw;
}
template <typename T>
constexpr void operator+=(vector4<T>& v, const vector4<T>& adding_vector) noexcept
{
    v.x += adding_vector.x;
    v.y += adding_vector.y;
    v.z += adding_vector.z;
    v.w += adding_vector.w;
}

template <typename T>
constexpr void operator-=(vector4<T>& v, const vector4<T>& subtracting_vector) noexcept
{
    v.x -= subtracting_vector.x;
    v.y -= subtracting_vector.y;
    v.z -= subtracting_vector.z;
    v.w -= subtracting_vector.w;
}
template <typename T>
constexpr void operator*=(vector4<T>& v, float scale) noexcept
{
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;
    v.w *= scale;
}
template <typename T>
constexpr void operator/=(vector4<T>& v, float divisor) noexcept
{
    assert(divisor != 0);
    v.x /= divisor;
    v.y /= divisor;
    v.z /= divisor;
    v.w /= divisor;
}
template <typename T>
constexpr vector4<T> operator-(const vector4<T>& v) noexcept
{
    vector4<T> result_vec;

    result_vec.x = -(v.x);
    result_vec.y = -(v.y);
    result_vec.z = -(v.z);
    result_vec.w = -(v.w);

    return result_vec;
}
template <typename T>
constexpr vector4<T> operator+(const vector4<T>& v1, const vector4<T>& v2) noexcept
{
    vector4<T> result_vec;
    result_vec.x = v1.x + v2.x;
    result_vec.y = v1.y + v2.y;
    result_vec.z = v1.z + v2.z;
    result_vec.w = v1.w + v2.w;

    return result_vec;
}
template <typename T>
constexpr vector4<T> operator-(const vector4<T>& v1, const vector4<T>& v2) noexcept
{
    vector4<T> result_vec;

    v2.x > v1.x ? result_vec.x = v2.x - v1.x : result_vec.x = v1.x - v2.x;
    v2.y > v1.y ? result_vec.y = v2.y - v1.y : result_vec.y = v1.y - v2.y;
    v2.z > v1.z ? result_vec.z = v2.z - v1.z : result_vec.z = v1.z - v2.z;
    v2.w > v1.w ? result_vec.w = v2.w - v1.w : result_vec.w = v1.w - v2.w;
    return result_vec;
}
template <typename T>
constexpr vector4<T> operator*(const vector4<T>& v, float scale) noexcept
{
    vector4<T> result_vec(v.x * scale, v.y * scale, v.z * scale, v.w * scale);

    return result_vec;
}
template <typename T>
constexpr vector4<T> operator*(float scale, const vector4<T>& v) noexcept
{
    vector4<T> result_vec(scale * v.x, scale * v.y, scale * v.z, scale* v.w);

    return result_vec;
}
template <typename T>
constexpr vector4<T> operator/(const vector4<T>& v, float divisor) noexcept
{
    assert(divisor != 0);
    vector4<T> result_vec;

    result_vec.x = v.x / divisor;
    result_vec.y = v.y / divisor;
    result_vec.z = v.z / divisor;
    result_vec.w = v.w / divisor;

    return result_vec;
}

template <typename T>
constexpr bool operator==(const vector4<T>& v1, const vector4<T>& v2) noexcept
{
    if (std::abs(v2.x - v1.x) <= std::numeric_limits<float>::epsilon() &&
        std::abs(v2.y - v1.y) <= std::numeric_limits<float>::epsilon() &&
        std::abs(v2.z - v1.z) <= std::numeric_limits<float>::epsilon() && 
        std::abs(v2.w - v1.w) <= std::numeric_limits<float>::epsilon())
    {
        return true;
    }
    return false;
}

template <typename T>
constexpr bool operator!=(const vector4<T>& v1, const vector4<T>& v2) noexcept
{
    if (std::abs(v2.x - v1.x) <= std::numeric_limits<float>::epsilon() &&
        std::abs(v2.y - v1.y) <= std::numeric_limits<float>::epsilon() &&
        std::abs(v2.z - v1.z) <= std::numeric_limits<float>::epsilon() && 
        std::abs(v2.w - v1.w) <= std::numeric_limits<float>::epsilon())
    {
        return false;
    }
    else
        return true;
}
