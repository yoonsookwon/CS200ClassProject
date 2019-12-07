#define   CATCH_CONFIG_MAIN 
#include  "catch.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include  "matrix3.hpp"
#include  "matrix4.hpp"


TEST_CASE("vector2<float> constructor")
{
    vector2<float> test;
    REQUIRE(test.x == 0);
    REQUIRE(test.y == 0);
}

TEST_CASE("vector2<float>(float fx, float fy) constructor")
{
    vector2<float > test(1, 2);

    REQUIRE(test.x == 1);
    REQUIRE(test.y == 2);
}

TEST_CASE("operato+=(vector2<T>& v, const vector2<float>& adding_vector)")
{
    vector2<float> test(1,2);
    vector2<float> test2(2,3);
    REQUIRE(test.x + test2.x == 3);
    REQUIRE(test.y + test2.y == 5);
}
TEST_CASE("operator-=(vector2<T>& v, const vector2<float>& subtracting_vector)")
{
    vector2<float> test(1, 2);
    vector2<float> test2(2, 3);
    REQUIRE(test.x - test2.x == -1);
    REQUIRE(test.y - test2.y == -1);
}
TEST_CASE("operator*=(vector2<float>& v,  float scale)")
{
    vector2<float> test(5, 2);
    vector2<float> test2(2, 3);
    REQUIRE(test.x * test2.x == 10);
    REQUIRE(test.y * test2.y == 6);
}
TEST_CASE("operator/=(vector2<float>& v, float divisor)")
{
    vector2<float> test(19, 6);
    vector2<float> test2(2, 3);
    REQUIRE(Approx( test.x / test2.x).epsilon(0.1) == 9.5);
    REQUIRE( test.y / test2.y == 2);
}
TEST_CASE("operator==(const vector2<float>& v1, const vector2<float>& v2")
{
    vector2<float> test(2, 12);
    vector2<float> test2(2, 12);
    REQUIRE(test.x == test2.x);
    REQUIRE(test.y == test2.y);
}
TEST_CASE("operator!=(const vector2<float>& v1, const vector2<float>& v2")
{
    vector2<float> test(12, 4);
    vector2<float> test2(2, 3);
    REQUIRE(test.x != test2.x);
    REQUIRE(test.y != test2.y);
}
TEST_CASE("dot(vector2<flaot> a, vector2<float> b)")
{
    vector2<float> test(2, 4);
    vector2<float> test2(2, 3);

    REQUIRE(dot(test, test2) == 16);
}
TEST_CASE("perpendicular_to(vector2<float> a)")
{
    vector2<float> test(12, 4);
    test = perpendicular_to(test);;
    REQUIRE(test.x == -4);
    REQUIRE(test.y == 12);
}
TEST_CASE("magnitude_squared(vector2<float> a) ")
{
    vector2<float> test(12, 4);
    REQUIRE(magnitude_squared(test) == 160 );
}
TEST_CASE("magnitude(vector2<float> a) ")
{
    vector2<float> test(12, 4);
    REQUIRE(Approx(magnitude(test)).epsilon(0.001) == sqrt(160));
}
//TEST_CASE("normalize(vector2<float> a) ")
//{
//    vector2<float> test(12, 4);
//    REQUIRE(normalize(test).x == 160);
//}
TEST_CASE("distance_between_squared(vector2<float> a, vector2<float> b)")
{
    //vector2<float> test(12, 4);
    vector2<float> test(10, 4);
    vector2<float> test2(4, 2);
    REQUIRE(distance_between_squared(test,test2) == 40);
}
TEST_CASE("distance_between(vector2<float> a, vector2<float> b)")
{
    vector2<float> test(10, 4);
    vector2<float> test2(4, 2);
    REQUIRE(Approx(distance_between(test, test2)).epsilon(0.001) == sqrt(40));
}
//TEST_CASE("angle_between(vector2<float> a, vector2<float> b)")
//{
//    vector2<float> test(1, 0);
//    vector2<float> test2(0, 1);
//    REQUIRE(angle_between(test,test2) == 0.90);
//}
//TEST_CASE("rotate_by(float angle_in_radians, vector2<float> v)")
//{
//    vector2<float> test(1.0,0.0);
//    REQUIRE(rotate_by(90, test).x == 0.0);
//}


//vector3
TEST_CASE("vector3<float> constructor")
{
    vector3<float> test;
    REQUIRE(test.x == 0);
    REQUIRE(test.y == 0);
    REQUIRE(test.z == 0);
}

TEST_CASE("vector3<float>(float fx, float fy) constructor")
{
    vector3<float > test(1, 2,3);

    REQUIRE(test.x == 1);
    REQUIRE(test.y == 2);
    REQUIRE(test.z == 3);
}

TEST_CASE("operato+=(vector3<T>& v, const vector3<float>& adding_vector)")
{
    vector3<float> test(1, 2,2);
    vector3<float> test2(2, 3,5);
    REQUIRE(test.x + test2.x == 3);
    REQUIRE(test.y + test2.y == 5);
    REQUIRE(test.z + test2.z == 7);
}
TEST_CASE("operator-=(vector3<T>& v, const vector3<float>& subtracting_vector)")
{
    vector3<float> test(1, 2,8);
    vector3<float> test2(2, 3,5);
    REQUIRE(test.x - test2.x == -1);
    REQUIRE(test.y - test2.y == -1);
    REQUIRE(test.z - test2.z ==  3);
}
TEST_CASE("operator*=(vector3<float>& v,  float scale)")
{
    vector3<float> test(5, 2,5);
    vector3<float> test2(2, 3,4);
    REQUIRE(test.x * test2.x == 10);
    REQUIRE(test.y * test2.y == 6);
    REQUIRE(test.z * test2.z == 20);
}
TEST_CASE("operator/=(vector3<float>& v, float divisor)")
{
    vector3<float> test(19, 6, 10);
    vector3<float> test2(2, 3,2);
    REQUIRE(Approx(test.x / test2.x).epsilon(0.1) == 9.5);
    REQUIRE(test.y / test2.y == 2);
    REQUIRE(test.z / test2.z == 5);
}
TEST_CASE("operator==(const vector3<float>& v1, const vector3<float>& v2")
{
    vector3<float> test(2, 12, 15);
    vector3<float> test2(2, 12,15);
    REQUIRE(test.x == test2.x);
    REQUIRE(test.y == test2.y);
    REQUIRE(test.z == test2.z);
}
TEST_CASE("operator!=(const vector3<float>& v1, const vector3<float>& v2)")
{
    vector3<float> test(12, 4,9);
    vector3<float> test2(2, 3,8);
    REQUIRE(test.x != test2.x);
    REQUIRE(test.y != test2.y);
    REQUIRE(test.z != test2.z);
}
TEST_CASE("dot(vector3<flaot> a, vector3<float> b)")
{
    vector3<float> test(2, 4,5);
    vector3<float> test2(2, 3,5);
    REQUIRE(dot(test, test2) == 41);
}
TEST_CASE(" cross(vector3<float> a, vector3<float> b)")
{
    vector3<float> test(3, 4,2);
    vector3<float> test2(6, 4, 2);
    vector3<float> result = cross(test, test2);
    REQUIRE(result.x == 0);
    REQUIRE(result.y == 6);
    REQUIRE(result.z == -12);
}
//TEST_CASE("normalize(vector2<float> a) ")
//{
//    vector2<float> test(12, 4);
//    REQUIRE(normalize(test).x == 160);
//}
//
TEST_CASE("magnitude_squared(vector3<float> a) ")
{
    vector3<float> test(12, 4,4);
    REQUIRE(magnitude_squared(test) == 176);
}
TEST_CASE("magnitude(vector3<float> a) ")
{
    vector3<float> test(12, 4, 4);
    REQUIRE(Approx(magnitude(test)).epsilon(0.001) == sqrt(176));
}
TEST_CASE("distance_between_squared(vector3<float> a, vector3<float> b)")
{
    //vector2<float> test(12, 4);
    vector3<float> test(10, 4,4);
    vector3<float> test2(4, 2,1);
    REQUIRE(distance_between_squared(test, test2) == 49);
}
TEST_CASE("distance_between(vector3<float> a, vector3<float> b)")
{
    vector3<float> test(10, 4,4);
    vector3<float> test2(4, 2,1);
    REQUIRE(Approx(distance_between(test, test2)).epsilon(0.001) == sqrt(49));
}


//vector4
TEST_CASE("vector4<float> constructor")
{
    vector4<float> test;
    REQUIRE(test.x == 0);
    REQUIRE(test.y == 0);
    REQUIRE(test.z == 0);
    REQUIRE(test.w == 0);
}

TEST_CASE("vector4<float>(float fx, float fy) constructor")
{
    vector4<float > test(1, 2, 3,4);

    REQUIRE(test.x == 1);
    REQUIRE(test.y == 2);
    REQUIRE(test.z == 3);
    REQUIRE(test.w == 4);
}

TEST_CASE("operato+=(vector4<T>& v, const vector4<float>& adding_vector)")
{
    vector4<float> test(1, 2, 2, 4);
    vector4<float> test2(2, 3, 5,8);
    REQUIRE(test.x + test2.x == 3);
    REQUIRE(test.y + test2.y == 5);
    REQUIRE(test.z + test2.z == 7);
    REQUIRE(test.w + test2.w == 12);
}
TEST_CASE("operator-=(vector4<T>& v, const vector4<float>& subtracting_vector)")
{
    vector4<float> test(1, 2, 8,1);
    vector4<float> test2(2, 3, 5,9);
    REQUIRE(test.x - test2.x == -1);
    REQUIRE(test.y - test2.y == -1);
    REQUIRE(test.z - test2.z == 3);
    REQUIRE(test.w - test2.w == -8);
}
TEST_CASE("operator*=(vector4<float>& v,  float scale)")
{
    vector4<float> test(5, 2, 5,4);
    vector4<float> test2(2, 3, 4,12);
    REQUIRE(test.x * test2.x == 10);
    REQUIRE(test.y * test2.y == 6);
    REQUIRE(test.z * test2.z == 20);
    REQUIRE(test.w * test2.w == 48);
}
TEST_CASE("operator/=(vector4<float>& v, float divisor)")
{
    vector4<float> test(19, 6, 10,36);
    vector4<float> test2(2, 3, 2,1);
    REQUIRE(Approx(test.x / test2.x).epsilon(0.1) == 9.5);
    REQUIRE(test.y / test2.y == 2);
    REQUIRE(test.z / test2.z == 5);
    REQUIRE(test.w / test2.w == 36);
}
TEST_CASE("operator==(const vector4<float>& v1, const vector4<float>& v2")
{
    vector4<float> test(2, 12, 15,20);
    vector4<float> test2(2, 12, 15,20);
    REQUIRE(test.x == test2.x);
    REQUIRE(test.y == test2.y);
    REQUIRE(test.z == test2.z);
    REQUIRE(test.w == test2.w);
}
TEST_CASE("operator!=(const vector4<float>& v1, const vector4<float>& v2)")
{
    vector4<float> test(12, 4, 9,12);
    vector4<float> test2(2, 3, 8,1);
    REQUIRE(test.x != test2.x);
    REQUIRE(test.y != test2.y);
    REQUIRE(test.z != test2.z);
    REQUIRE(test.w != test2.w);
}

//matrix3
TEST_CASE("matrix3<float> constructor")
{
    matrix3<float> test;
    REQUIRE(test.column0.x == 0);
    REQUIRE(test.column0.y == 0);
    REQUIRE(test.column0.z == 0);
    REQUIRE(test.column1.x == 0);
    REQUIRE(test.column1.y == 0);
    REQUIRE(test.column1.z == 0);
    REQUIRE(test.column2.x == 0);
    REQUIRE(test.column2.y == 0);
    REQUIRE(test.column2.z == 0);
}

TEST_CASE("matrix3<float> all value constructor")
{
    matrix3<float> test(0,2,0,8,0,0,0,0,0);
    REQUIRE(test.column0.x == 0);
    REQUIRE(test.column0.y == 2);
    REQUIRE(test.column0.z == 0);
    REQUIRE(test.column1.x == 8);
    REQUIRE(test.column1.y == 0);
    REQUIRE(test.column1.z == 0);
    REQUIRE(test.column2.x == 0);
    REQUIRE(test.column2.y == 0);
    REQUIRE(test.column2.z == 0);
}