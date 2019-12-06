
template <typename T>
constexpr matrix4<T>::matrix4() noexcept
{
    column0 = { 0.0, 0.0, 0.0, 0.0 };
    column1 = { 0.0, 0.0, 0.0, 0.0 };
    column2 = { 0.0, 0.0, 0.0, 0.0 };
    column3 = { 0.0, 0.0, 0.0, 0.0 };
}


template <typename T>
constexpr matrix4<T>::matrix4(vector4<T> first_column, vector4<T> second_column, vector4<T> third_column, vector4<T> fourth_column) noexcept
{
    column0 = first_column;
    column1 = second_column;
    column2 = third_column;
    column3 = fourth_column;
}


template <typename T>
constexpr matrix4<T>::matrix4(T column0_row0, T column0_row1, T column0_row2, T column0_row3, T column1_row0, T column1_row1,
    T column1_row2, T column1_row3, T column2_row0, T column2_row1, T column2_row2, T column2_row3, T column3_row0,
    T column3_row1, T column3_row2, T column3_row3) noexcept
{
    column0 = { column0_row0, column0_row1, column0_row2, column0_row3 };
    column1 = { column1_row0, column1_row1, column1_row2, column1_row3 };
    column2 = { column2_row0, column2_row1, column2_row2, column2_row3 };
    column3 = { column3_row0, column3_row1, column3_row2, column3_row3 };

}


template <typename T>
constexpr T matrix4<T>::operator()(T column, T row) const noexcept
{

    assert(column >= 0 && row >= 0 && column <= 3 && row <= 3);
    if (column == 0)
    {
        if (row == 0)
            return column0.x;
        else if (row == 1)
            return column0.y;
        else if (row == 2)
            return column0.z;
        else
            return column0.w;
    }
    else if (column == 1)
    {
        if (row == 0)
            return column1.x;
        else if (row == 1)
            return column1.y;
        else if (row == 2)
            return column1.z;
        else
            return column1.w;
    }
    else if (column == 2)
    {
        if (row == 0)
            return column2.x;
        else if (row == 1)
            return column2.y;
        else if (row == 2)
            return column2.z;
        else
            return column2.w;
    }
    else
    {
        if (row == 0)
            return column3.x;
        else if (row == 1)
            return column3.y;
        else if (row == 2)
            return column3.z;
        else
            return column3.w;
    }

}


template <typename T>
constexpr T& matrix4<T>::operator()(T column, T row) noexcept
{
    if (column == 0)
    {
        if (row == 0)
            return column0.x;
        else if (row == 1)
            return column0.y;
        else if (row == 2)
            return column0.z;
        else
            return column0.w;
    }
    else if (column == 1)
    {
        if (row == 0)
            return column1.x;
        else if (row == 1)
            return column1.y;
        else if (row == 2)
            return column1.z;
        else
            return column1.w;
    }
    else if (column == 2)
    {
        if (row == 0)
            return column2.x;
        else if (row == 1)
            return column2.y;
        else if (row == 2)
            return column2.z;
        else
            return column2.w;
    }
    else
    {
        if (row == 0)
            return column3.x;
        else if (row == 1)
            return column3.y;
        else if (row == 2)
            return column3.z;
        else
            return column3.w;
    }
}


template <typename T>
constexpr matrix4<T> operator*(const matrix4<T>& m1, const matrix4<T>& m2) noexcept
{
    matrix4<T> matrix;
    matrix.column0.x = m1.column0.x * m2.column0.x + m1.column1.x * m2.column0.y + m1.column2.x * m2.column0.z + m1.column3.x * m2.column0.w;
    matrix.column0.y = m1.column0.y * m2.column0.x + m1.column1.y * m2.column0.y + m1.column2.y * m2.column0.z + m1.column3.y * m2.column0.w;
    matrix.column0.z = m1.column0.z * m2.column0.x + m1.column1.z * m2.column0.y + m1.column2.z * m2.column0.z + m1.column3.z * m2.column0.w;
    matrix.column0.w = m1.column0.w * m2.column0.x + m1.column1.w * m2.column0.y + m1.column2.w * m2.column0.z + m1.column3.w * m2.column0.w;
    matrix.column1.x = m1.column0.x * m2.column1.x + m1.column1.x * m2.column1.y + m1.column2.x * m2.column1.z + m1.column3.x * m2.column1.w;
    matrix.column1.y = m1.column0.y * m2.column1.x + m1.column1.y * m2.column1.y + m1.column2.y * m2.column1.z + m1.column3.y * m2.column1.w;
    matrix.column1.z = m1.column0.z * m2.column1.x + m1.column1.z * m2.column1.y + m1.column2.z * m2.column1.z + m1.column3.z * m2.column1.w;
    matrix.column1.w = m1.column0.w * m2.column1.x + m1.column1.w * m2.column1.y + m1.column2.w * m2.column1.z + m1.column3.w * m2.column1.w;
    matrix.column2.x = m1.column0.x * m2.column2.x + m1.column1.x * m2.column2.y + m1.column2.x * m2.column2.z + m1.column3.x * m2.column2.w;
    matrix.column2.y = m1.column0.y * m2.column2.x + m1.column1.y * m2.column2.y + m1.column2.y * m2.column2.z + m1.column3.y * m2.column2.w;
    matrix.column2.z = m1.column0.z * m2.column2.x + m1.column1.z * m2.column2.y + m1.column2.z * m2.column2.z + m1.column3.z * m2.column2.w;
    matrix.column2.w = m1.column0.w * m2.column2.x + m1.column1.w * m2.column2.y + m1.column2.w * m2.column2.z + m1.column3.w * m2.column2.w;
    matrix.column3.x = m1.column0.x * m2.column3.x + m1.column1.x * m2.column3.y + m1.column2.x * m2.column3.z + m1.column3.x * m2.column3.w;
    matrix.column3.y = m1.column0.y * m2.column3.x + m1.column1.y * m2.column3.y + m1.column2.y * m2.column3.z + m1.column3.y * m2.column3.w;
    matrix.column3.z = m1.column0.z * m2.column3.x + m1.column1.z * m2.column3.y + m1.column2.z * m2.column3.z + m1.column3.z * m2.column3.w;
    matrix.column3.w = m1.column0.w * m2.column3.x + m1.column1.w * m2.column3.y + m1.column2.w * m2.column3.z + m1.column3.w * m2.column3.w;

    return matrix;
}

template <typename T>
constexpr void operator*=(matrix4<T>& m1, const matrix4<T>& m2) noexcept
{
    m1 = m1 * m2;
}
//template <typename T>
//constexpr void operator=(const matrix4<T>& m1) noexcept
//{
//    MATRIX4<flaot> result;
//
//    
//}

template <typename T>
constexpr vector4<T> operator*(const matrix4<T>& m, vector4<T> v) noexcept
{
    vector4<T> result;
    result.x = m.column0.x * v.x + m.column1.x * v.y + m.column2.x * v.z + m.column3.x * v.w;
    result.y = m.column0.y * v.x + m.column1.y * v.y + m.column2.y * v.z + m.column3.y * v.w;
    result.z = m.column0.z * v.x + m.column1.z * v.y + m.column2.z * v.z + m.column3.z * v.w;
    result.w = m.column0.w * v.x + m.column1.w * v.y + m.column2.w * v.z + m.column3.w * v.w;
    return result;
}


template <typename T>
constexpr matrix4<T> MATRIX4::transpose(const matrix4<T>& m) noexcept
{
    matrix4<T> matrix;
    /*matrix.column0.x = m.column0.x;
    matrix.column0.y = m.column1.x;
    matrix.column0.z = m.column2.x;
    matrix.column0.w = m.column3.x;
    matrix.column1.x = m.column0.y;
    matrix.column1.y = m.column1.y;
    matrix.column1.z = m.column2.y;
    matrix.column1.w = m.column3.y;
    matrix.column2.x = m.column0.z;
    matrix.column2.y = m.column1.z;
    matrix.column2.z = m.column2.z;
    matrix.column2.w = m.column3.z;
    matrix.column3.x = m.column0.w;
    matrix.column3.y = m.column1.w;
    matrix.column3.z = m.column2.w;
    matrix.column3.w = m.column3.w;*/



    matrix.elements[0][0] = m.elements[0][0];
    matrix.elements[0][1] = m.elements[1][0];
    matrix.elements[0][2] = m.elements[2][0];
    matrix.elements[0][3] = m.elements[3][0];


    matrix.elements[1][0] = m.elements[0][1];
    matrix.elements[1][1] = m.elements[1][1];
    matrix.elements[1][2] = m.elements[2][1];
    matrix.elements[1][3] = m.elements[3][1];

    matrix.elements[2][0] = m.elements[0][2];
    matrix.elements[2][1] = m.elements[1][2];
    matrix.elements[2][2] = m.elements[2][2];
    matrix.elements[2][3] = m.elements[3][2];

    matrix.elements[3][0] = m.elements[0][3];
    matrix.elements[3][1] = m.elements[1][3];
    matrix.elements[3][2] = m.elements[2][3];
    matrix.elements[3][3] = m.elements[3][3];


    return matrix;
}


template <typename T>
constexpr matrix4<T> MATRIX4::build_rotation(float angle_in_radians) noexcept
{
    matrix4<T> matrix;
    matrix.column0.x = cos(angle_in_radians);
    matrix.column0.y = sin(angle_in_radians);
    matrix.column0.z = 0.0f;
    matrix.column0.w = 0.0f;


    matrix.column1.x = -sin(angle_in_radians);
    matrix.column1.y = cos(angle_in_radians);
    matrix.column1.z = 0.0f;
    matrix.column1.w = 0.0f;



    matrix.column2.x = 0.0f;
    matrix.column2.y = 0.0f;
    matrix.column2.z = 0.0f;
    matrix.column2.w = 0.0f;

    matrix.column3.x = 0.0f;
    matrix.column3.y = 0.0f;
    matrix.column3.z = 0.0f;
    matrix.column3.w = 1.0f;


    //if (std::abs(sin(angle_in_radians)) < std::numeric_limits<float>::epsilon())
    //{
    //    matrix.column0.y = 0.0f;
    //    matrix.column1.x = 0.0f;
    //}
    //else
    //{
    //    matrix.column0.y = sin(angle_in_radians);
    //    matrix.column1.x = -sin(angle_in_radians);
    //}
    //matrix.column1.y = cos(angle_in_radians);
    //matrix.column1.z = 0.0f;
    //matrix.column1.w = 0.0f;
    //matrix.column2.x = 0.0f;
    //matrix.column2.y = 0.0f;
    //matrix.column2.z = 0.0f;
    //matrix.column2.w = 0.0f;
    //matrix.column3.x = 0.0f;
    //matrix.column3.y = 0.0f;
    //matrix.column3.z = 0.0f;
    //matrix.column3.w = 1.0f;
    //return matrix;
    //
    return matrix;
}


template <typename T>
constexpr matrix4<T> MATRIX4::build_identity() noexcept
{
    matrix4<T> matrix(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    return matrix;
}


template <typename T>
constexpr matrix4<T> MATRIX4::build_scale(float scale_x, float scale_y, float scale_z) noexcept
{
    matrix4<T> matrix;
    matrix.column0.x = scale_x;
    matrix.column0.y = 0.0f;
    matrix.column0.z = 0.0f;
    matrix.column0.w = 0.0f;
    matrix.column1.x = 0.0f;
    matrix.column1.y = scale_y;
    matrix.column1.z = 0.0f;
    matrix.column1.w = 0.0f;
    matrix.column2.x = 0.0f;
    matrix.column2.y = 0.0f;
    matrix.column2.z = 0.0f;
    matrix.column2.w = 0.0f;
    matrix.column3.x = 0.0f;
    matrix.column3.y = 0.0f;
    matrix.column3.z = 0.0f;
    matrix.column3.w = 1.0f;
    return matrix;
}

template <typename T>
constexpr matrix4<T> MATRIX4::build_scale(float scale) noexcept
{
    matrix4<T> matrix;
    matrix.column0.x = scale;
    matrix.column0.y = 0.0f;
    matrix.column0.z = 0.0f;
    matrix.column0.w = 0.0f;
    matrix.column1.x = 0.0f;
    matrix.column1.y = scale;
    matrix.column1.z = 0.0f;
    matrix.column1.w = 0.0f;
    matrix.column2.x = 0.0f;
    matrix.column2.y = 0.0f;
    matrix.column2.z = 0.0f;
    matrix.column2.w = 0.0f;
    matrix.column3.x = 0.0f;
    matrix.column3.y = 0.0f;
    matrix.column3.z = 0.0f;
    matrix.column3.w = 1.0f;
    return matrix;
}

template <typename T>
constexpr matrix4<T> MATRIX4::build_scale(const vector3<T>& scale) noexcept
{
    matrix4<T> matrix;
    matrix.column0.x = scale.x;
    matrix.column0.y = 0.0f;
    matrix.column0.z = 0.0f;
    matrix.column0.w = 0.0f;
    matrix.column1.x = 0.0f;
    matrix.column1.y = scale.y;
    matrix.column1.z = 0.0f;
    matrix.column1.w = 0.0f;
    matrix.column2.x = 0.0f;
    matrix.column2.y = 0.0f;
    matrix.column2.z = scale.z;
    matrix.column2.w = 0.0f;
    matrix.column3.x = 0.0f;
    matrix.column3.y = 0.0f;
    matrix.column3.z = 0.0f;
    matrix.column3.w = 1.0f;

    return matrix;
}

template <typename T>
constexpr matrix4<T> MATRIX4::build_translation(float translate_x, float translate_y, float translate_z) noexcept
{
    matrix4<T> matrix;
    matrix.column0.x = 1.0f;
    matrix.column0.y = 0.0f;
    matrix.column0.z = 0.0f;
    matrix.column0.w = 0.0f;

    matrix.column1.x = 0.0f;
    matrix.column1.y = 1.0f;
    matrix.column1.z = 0.0f;
    matrix.column1.w = 0.0f;

    matrix.column2.x = 0.0f;
    matrix.column2.y = 0.0f;
    matrix.column2.z = 0.0f;
    matrix.column2.w = 0.0f;

    matrix.column3.x = translate_x;
    matrix.column3.y = translate_y;
  /*  matrix.column3.x += translate_x;
    matrix.column3.y += translate_y;
  */
    matrix.column3.z = translate_z;
    matrix.column3.w = 1.0f;

    return matrix;
}

template <typename T>
constexpr matrix4<T> MATRIX4::build_translation(const vector3<T>& translation) noexcept
{
    matrix4<T> matrix;
    matrix.column0.x = 1.0f;
    matrix.column0.y = 0.0f;
    matrix.column0.z = 0.0f;
    matrix.column0.w = 0.0f;
    matrix.column1.x = 0.0f;
    matrix.column1.y = 1.0f;
    matrix.column1.z = 0.0f;
    matrix.column1.w = 0.0f;
    matrix.column2.x = 0.0f;
    matrix.column2.y = 0.0f;
    matrix.column2.z = 1.0f;
    matrix.column2.w = 0.0f;
    matrix.column3.x += translation.x;
    matrix.column3.y += translation.y;
    matrix.column3.z += translation.z;
    matrix.column3.w = 1.0;
    return matrix;
}
