#pragma once
#include "matrix4.hpp"
#include "vector4.hpp"
#include  "Model.h"
#include <DirectXMath.h>
using namespace DirectX;

class Camera
{
public:
    Camera();
    void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

    const  matrix4<float>& GetViewMatrix() const;
    const matrix4<float> & GetProjectionMatrix() const;/*

    const vector4<float> & GetPositionVector() const;
    const vector3<float> & GetPositionFloat3() const;
    const vector4<float> & GetRotationVector() const;
    const vector3<float>& GetRotationFloat3() const;*/

    void SetPosition(const vector4<float> & pos);
    //void SetPosition(const vector3<float> & pos);
    void SetPosition(float x, float y, float z);

    void AdjustPosition(const vector4<float> & pos);
    void AdjustPosition(const vector3<float> & pos);
    void AdjustPosition(float x, float y, float z);

  //  void SetRotation(const vector4<float> & rot);
   // void SetRotation(const vector3<float> & pos);
  //  void SetRotation(float x, float y, float z);

   // void AdjustRotation(const vector4<float> & rot); 
  //  void AdjustRotation(const vector3<float> & pos);
    void AdjustRotation(/*float angle*/float x, float y, float z);
    void AdjustCameraZoom(float _zoom);


    void SetLookAtPos(vector3<float> lookAtPos);
    const vector4<float> & GetForwardVector();
    const vector4<float> & GetRightVector();
    const vector4<float> & GetBackwardVector();
    const vector4<float> & GetLeftVector();
    void UpdateViewMatrix();
    float zoom = 0.3f;
    float angle = 0;
private:
    vector4<float> posVector;
    vector4<float> rotVector;

    vector2<float> pos;
    vector3<float> rot;
    float translation_x=0;
    float translation_y=0;
    float translation_z=0;
    matrix4<float> viewMatrix = MATRIX4::build_identity<float>();
    matrix4<float> projectionMatrix = MATRIX4::build_identity<float>();

     vector4<float> DEFAULT_FORWARD_VECTOR = vector4<float>(0.0f, 0.0f, 1.0f, 0.0f);
     vector4<float> DEFAULT_UP_VECTOR = vector4<float>(0.0f, 1.0f, 0.0f, 0.0f);
     vector4<float> DEFAULT_BACKWARD_VECTOR = vector4<float>(0.0f, 0.0f, -1.0f, 0.0f);
     vector4<float> DEFAULT_LEFT_VECTOR = vector4<float>(-1.0f, 0.0f, 0.0f, 0.0f);
     vector4<float> DEFAULT_RIGHT_VECTOR = vector4<float>(1.0f, 0.0f, 0.0f, 0.0f);

    vector4<float> vec_forward;
    vector4<float> vec_left;
    vector4<float> vec_right;
    vector4<float> vec_backward;
};