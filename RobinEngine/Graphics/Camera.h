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
    vector2<float> GetCameraPosition();

    const  matrix4<float>& GetViewMatrix() const;
    const matrix4<float> & GetProjectionMatrix() const;

    void SetPosition(float x, float y);

    void AdjustPosition(const vector4<float> & pos);
    void AdjustPosition(const vector3<float> & pos);
    void AdjustPosition(float x, float y, float z);

    void AdjustRotation(float x, float y, float z);
    void AdjustCameraZoom(float _zoom);


    void UpdateViewMatrix();
    float zoom = 0.3f;
   // float angle = 0;
private:
   // vector4<float> posVector;
    //vector4<float> rotVector;

    vector2<float> pos;
    vector3<float> rot;
    matrix4<float> viewMatrix = MATRIX4::build_identity<float>();
    matrix4<float> projectionMatrix = MATRIX4::build_identity<float>();


};