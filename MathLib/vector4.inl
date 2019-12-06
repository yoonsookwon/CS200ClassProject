/************************************************
 *NAME              : yoonsoo.kwon
 *ASSIGNMENT NUMBER : 1
 *COURSE NAME       : CS230
 *TERM              : Spring 2019
 ************************************************/

template <typename T>
vector4<T>::vector4() noexcept
{
}
template <typename T>
vector4<T>::vector4(T repeated_float) noexcept
{
    x = repeated_float;
    y = repeated_float;
    z = 0.0f;
    w = repeated_float;
}
template <typename T>
vector4<T>::vector4(T fx, T fy, T fz ,T fw) noexcept
{
    x = fx;
    y = fy;
    z = 0.0f;
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
template <typename T>
constexpr float dot(vector4<T> a, vector4<T> b) noexcept
{
    float dot_product = 0.0f;

    dot_product += (a.x * b.x);
    dot_product += (a.y * b.y);
    dot_product += (a.z * b.z);
    dot_product += (a.w * b.w);

    return dot_product;
}
template <typename T>
constexpr vector4<T> cross(vector4<T> a, vector4<T> b) noexcept
{
    vector4<T> result_vec;

    result_vec.x = ((a.y * b.z) - (a.z * b.y));
    result_vec.y = -((a.x * b.z) - (a.z * b.x));
    result_vec.z = ((a.x * b.y) - (a.y * b.x));
  //  result_vec.w = ((a.x * b.y) - (a.y * b.x));


    return result_vec;
}
template <typename T>
constexpr float magnitude_squared(vector4<T> a) noexcept
{
    float magnitude_val_squared = 0.0f;

    magnitude_val_squared += dot(a, a);

    return magnitude_val_squared;
}
template <typename T>
constexpr float magnitude(vector4<T> a) noexcept
{
    float magnitude_val = 0.0f;

    magnitude_val += sqrt(dot(a, a));
    return magnitude_val;
}
template <typename T>
constexpr vector4<T> normalize(vector4<T> a) noexcept
{
    vector4<T> result_vec;
    float   magnitude_val = 0.0f;

    magnitude_val = magnitude(a);
    result_vec.x = a.x / magnitude_val;
    result_vec.y = a.y / magnitude_val;
    result_vec.z = a.z / magnitude_val;
    result_vec.w = a.w / magnitude_val;

    return result_vec;
}
template <typename T>
constexpr float distance_between_squared(vector4<T> a, vector4<T> b) noexcept
{
    float distance_squared = 0.0f;
    float distance_x = 0.0f;
    float distance_y = 0.0f;
    float distance_z = 0.0f;
    float distance_w = 0.0f;

    distance_x = b.x - a.x;
    distance_y = b.y - a.y;
    distance_z = b.z - a.z;
    distance_w = b.w - a.w;


    distance_squared = ((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z) + (distance_w * distance_w));

    return distance_squared;
}
template <typename T>
constexpr float distance_between(vector4<T> a, vector4<T> b) noexcept
{
    float distance = 0.0f;
    float distance_x = 0.0f;
    float distance_y = 0.0f;
    float distance_z = 0.0f;
    float distance_w = 0.0f;

    distance_x = b.x - a.x;
    distance_y = b.y - a.y;
    distance_z = b.z - a.z;
    distance_w = b.w - a.w;

    distance = sqrt((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z) + (distance_w* distance_w));

    return distance;
}
template <typename T>
constexpr float angle_between(vector4<T> a, vector4<T> b) noexcept
{
    float cos_theta = dot(a, b) / (magnitude(a) * magnitude(b));
    float radian = acosf(cos_theta);
    float angle = radian;

    return angle;
}

