#include "Camera.h"

Camera::Camera()
{
   /* this->pos = vector3<float>(0.0f, 0.0f, 0.0f);
    this->posVector = XMLoadFloat3(&this->pos);
    this->rot = vector3<float>(0.0f, 0.0f, 0.0f);
    this->rotVector = XMLoadFloat3(&this->rot);
   */ this->UpdateViewMatrix();
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
    float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
   // this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const  matrix4<float> & Camera::GetViewMatrix() const
{
    return this->viewMatrix;
}

const matrix4<float>& Camera::GetProjectionMatrix() const
{
    return this->projectionMatrix;
}

const vector4<float> & Camera::GetPositionVector() const
{
    return this->posVector;
}

const vector3<float> & Camera::GetPositionFloat3() const
{
    return this->pos;
}

const vector4<float> & Camera::GetRotationVector() const
{
    return this->rotVector;
}

//const vector3<float> & Camera::GetRotationFloat3() const
//{
//    return this->rot;
//}

void Camera::SetPosition(const vector4<float> & pos)
{
   // vector3<float>(&this->pos, pos);
    this->posVector = pos;
    this->UpdateViewMatrix();
}

void Camera::SetPosition(const vector3<float> & pos)
{
    this->pos = pos;
  //  this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
    this->pos = vector3<float>(x, y, z);
  //  this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateViewMatrix();
}

void Camera::AdjustPosition(const vector4<float> & pos)
{
    this->posVector += pos;
   // XMStoreFloat3(&this->pos, this->posVector);
    this->UpdateViewMatrix();
}

void Camera::AdjustPosition(const vector3<float> & pos)
{
    this->pos.x += pos.y;
    this->pos.y += pos.y;
    this->pos.z += pos.z;
    //this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->pos.z += z;
   // this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateViewMatrix();
}

//void Camera::SetRotation(const vector4<float> & rot)
//{
//    this->rotVector = rot;
//  //  XMStoreFloat3(&this->rot, rot);
//    this->UpdateViewMatrix();
//}
//
//void Camera::SetRotation(const vector3<float> & rot)
//{
//    this->rot = rot;
//  //  this->rotVector = XMLoadFloat3(&this->rot);
//    this->UpdateViewMatrix();
//}

//void Camera::SetRotation(float x, float y, float z)
//{
//    this->rot = vector3<float>(x, y, z);
//   // this->rotVector = XMLoadFloat3(&this->rot);
//    this->UpdateViewMatrix();
//}

//void Camera::AdjustRotation(const vector4<float> & rot)
//{
//    this->rotVector += rot;
//   // XMStoreFloat3(&this->rot, this->rotVector);
//    this->UpdateViewMatrix();
//}
//
//void Camera::AdjustRotation(const vector3<float> & rot)
//{
//    this->rot.x += rot.x;
//    this->rot.y += rot.y;
//    this->rot.z += rot.z;
//   // this->rotVector = XMLoadFloat3(&this->rot);
//    this->UpdateViewMatrix();
//}

void Camera::AdjustRotation(float _angle/*x, float y, float z*/)
{
   /* this->rot.x += x;
    this->rot.y += y;
    this->rot.z += z;
    *///this->rotVector =// XMLoadFloat3(&this->rot);
    angle += _angle;
    this->UpdateViewMatrix();
}

//void Camera::SetLookAtPos(vector3<float> lookAtPos)
//{
//    //Verify that look at pos is not the same as cam pos. They cannot be the same as that wouldn't make sense and would result in undefined behavior.
//    if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z)
//        return;
//
//    lookAtPos.x = this->pos.x - lookAtPos.x;
//    lookAtPos.y = this->pos.y - lookAtPos.y;
//    lookAtPos.z = this->pos.z - lookAtPos.z;
//
//    float pitch = 0.0f;
//    if (lookAtPos.y != 0.0f)
//    {
//        const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
//        pitch = atan(lookAtPos.y / distance);
//    }
//
//    float yaw = 0.0f;
//    if (lookAtPos.x != 0.0f)
//    {
//        yaw = atan(lookAtPos.x / lookAtPos.z);
//    }
//    if (lookAtPos.z > 0)
//        yaw += XM_PI;
//
//    this->SetRotation(pitch, yaw, 0.0f);
//}

const vector4<float> & Camera::GetForwardVector()
{
    return this->vec_forward;
}

const vector4<float> & Camera::GetRightVector()
{
    return this->vec_right;
}

const vector4<float> & Camera::GetBackwardVector()
{
    return this->vec_backward;
}

const vector4<float> & Camera::GetLeftVector()
{
    return this->vec_left;
}

void Camera::UpdateViewMatrix() //Updates view matrix and also updates the movement vectors
{
    //Calculate camera rotation matrix
    // matrix4<float> camRotationMatrix =  matrix4<float>(this->rot.x, this->rot.y, this->rot.z);
    //Calculate unit vector of cam target based off camera forward value transformed by cam rotation matrix
   // vector4<float> camTarget = vector4<float>TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRotationMatrix);
    //Adjust cam target to be offset by the camera's current position
    //camTarget += this->posVector;
    //Calculate up direction based on current rotation
   // vector4<float> upDir = vector4<float>(this->DEFAULT_UP_VECTOR, camRotationMatrix);

    matrix4<float> theResult = MATRIX4::build_identity<float>();

    matrix4<float> translation = MATRIX4::build_translation<float>(pos.x,pos.y,pos.z);
    matrix4<float> rotation = MATRIX4::build_rotation<float>(angle);
    matrix4<float> scale = MATRIX4::build_scale<float>(zoom);

    theResult *= translation;
    theResult *= rotation;
    theResult *= scale;

    theResult = MATRIX4::transpose(theResult);

    //Rebuild view matrix
    this->viewMatrix = translation * rotation * scale ;

}