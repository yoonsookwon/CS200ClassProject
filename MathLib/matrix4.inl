template <typename T>
constexpr matrix4<T>::matrix4() noexcept
{
    column0.x = 0.0f;
    column0.y = 0.0f;
    column0.z = 0.0f;
    column0.w = 0.0f;

    column1.x = 0.0f;
    column1.y = 0.0f;
    column1.z = 0.0f;
    column1.w = 0.0f;

    column2.x = 0.0f;
    column2.y = 0.0f;
    column2.z = 0.0f;
    column2.w = 0.0f;

    column3.x = 0.0f;
    column3.y = 0.0f;
    column3.z = 0.0f;
    column3.w = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            elements[i][j] = 0.0f;
        }
    }
}
template <typename T>
constexpr  matrix4<T>::matrix4(T column0_row0, T column0_row1, T column0_row2, T column0_row3, T column1_row0, T column1_row1,
    T column1_row2, T column1_row3, T column2_row0, T column2_row1, T column2_row2, T column2_row3, T column3_row0, T column3_row1, T column3_row2, T column3_row3) noexcept
{

    elements[0][0] = column0_row0;
    elements[1][0] = column1_row0;
    elements[2][0] = column2_row0;
    elements[3][0] = column3_row0;


    elements[0][1] = column0_row1;
    elements[1][1] = column1_row1;
    elements[2][1] = column2_row1;
    elements[3][1] = column3_row1;


    elements[0][2] = column0_row2;
    elements[1][2] = column1_row2;
    elements[2][2] = column2_row2;
    elements[3][2] = column3_row2;

    elements[0][3] = column0_row3;
    elements[1][3] = column1_row3;
    elements[2][3] = column2_row3;
    elements[3][3] = column3_row3;



}


template <typename T>
constexpr T matrix4<T>::operator()(int column, int row) const noexcept
{
    assert(column >= 0 && column <= 3);
    assert(row >= 0 && row <= 3);

    float element_val = 0.0f;

    element_val = elements[column][row];

    return element_val;
}




template <typename T>
constexpr T& matrix4<T>::operator()(int column, int row) noexcept
{
    assert(column >= 0 && column <= 3);
    assert(row >= 0 && row <= 3);

    return elements[column][row];
}

template <typename T>
constexpr matrix4<T> operator*(const matrix4<T>& m1, const matrix4<T>& m2) noexcept
{
    matrix4<T> result_matrix;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int z = 0; z < 4; z++)
            {
                result_matrix.elements[j][i] += m1.elements[z][i] * m2.elements[j][z];
            }
        }
    }
    return result_matrix;
}

template <typename T>
constexpr void    operator*=(matrix4<T>& m1, const matrix4<T>& m2) noexcept
{
    m1 = m1 * m2;
}


template <typename T>
constexpr matrix4<T> MATRIX4::transpose(const matrix4<T>& m) noexcept
{
    matrix4<T> result_matrix;

    result_matrix.elements[0][0] = m.elements[0][0];
    result_matrix.elements[0][1] = m.elements[1][0];
    result_matrix.elements[0][2] = m.elements[2][0];
    result_matrix.elements[0][3] = m.elements[3][0];

    result_matrix.elements[1][0] = m.elements[0][1];
    result_matrix.elements[1][1] = m.elements[1][1];
    result_matrix.elements[1][2] = m.elements[2][1];
    result_matrix.elements[1][3] = m.elements[3][1];

    result_matrix.elements[2][0] = m.elements[0][2];
    result_matrix.elements[2][1] = m.elements[1][2];
    result_matrix.elements[2][2] = m.elements[2][2];
    result_matrix.elements[2][3] = m.elements[3][2];

    result_matrix.elements[3][0] = m.elements[0][3];
    result_matrix.elements[3][1] = m.elements[1][3];
    result_matrix.elements[3][2] = m.elements[2][3];
    result_matrix.elements[3][3] = m.elements[3][3];

    return result_matrix;
}


template <typename T>
constexpr matrix4<T> MATRIX4::build_rotation(float angle_in_radians) noexcept
{
    matrix4<T>   result_matrix;
    const int zero_val = 0;

    result_matrix.column0.x = static_cast<T>(cos(angle_in_radians));
    result_matrix.column0.y = static_cast<T>(sin(angle_in_radians));
    result_matrix.column0.z = 0.0f;
    result_matrix.column0.w = 0.0f;
    result_matrix.column1.x = static_cast<T>(-(sin(angle_in_radians)));
    result_matrix.column1.y = static_cast<T>(cos(angle_in_radians));
    result_matrix.column1.z = 0.0f;
    result_matrix.column1.w = 0.0f;
    result_matrix.column2.x = 0.0f;
    result_matrix.column2.y = 0.0f;
    result_matrix.column2.z = 1.0f;
    result_matrix.column2.w = 0.0f;
    result_matrix.column3.x = 0.0f;
    result_matrix.column3.y = 0.0f;
    result_matrix.column3.z = 0.0f;
    result_matrix.column3.w = 1.0f;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (std::abs(result_matrix.elements[i][j]) <= std::numeric_limits<float>::epsilon())
            {
                result_matrix.elements[i][j] = (float)zero_val;
            }
        }
    }

    return result_matrix;
}


template <typename T>
constexpr matrix4<T> MATRIX4::build_identity() noexcept
{
    matrix4<T> result_matrix;

    result_matrix.column0.x = 1.0f;
    result_matrix.column1.y = 1.0f;
    result_matrix.column2.z = 1.0f;
    result_matrix.column3.w = 1.0f;

    return result_matrix;
}

template <typename T>
constexpr matrix4<T> MATRIX4::build_scale(float scale_x, float scale_y) noexcept
{
    matrix4<T> result_matrix;

    result_matrix.elements[0][0] = scale_x;
    result_matrix.elements[1][1] = scale_y;
    result_matrix.elements[2][2] = 0.0f;
    result_matrix.elements[3][3] = 1.0f;

    return result_matrix;
}

template <typename T>
constexpr matrix4<T> MATRIX4::build_scale(float scale) noexcept
{
    matrix4<T> result_matrix;
    result_matrix.column0.x = scale;
    result_matrix.column1.y = scale;
    result_matrix.column2.z = 0.0f;
    result_matrix.column3.w = 1.0f;

    return result_matrix;
}

template <typename T>
constexpr matrix4<T> MATRIX4::build_scale(const vector2<T>& scale) noexcept
{
    matrix4<T> result_matrix;
    result_matrix.column0.x = scale.x;
    result_matrix.column1.y = scale.y;
    result_matrix.column2.z = 0.0f;
    result_matrix.column3.w = 1.0f;

    return result_matrix;
}

template <typename T>
constexpr matrix4<T> MATRIX4::build_translation(float translate_x, float translate_y) noexcept
{
    matrix4<T> result_matrix;

    result_matrix.column0.x = 1.0f;
    result_matrix.column1.y = 1.0f;
    result_matrix.column2.z = 1.0f;
    result_matrix.column3.x = translate_x;
    result_matrix.column3.y = translate_y;
    result_matrix.column3.w = 1.0f;

    return result_matrix;
}