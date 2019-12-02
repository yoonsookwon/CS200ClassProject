#include "Model.h"
#include "vector2.hpp"

bool Model::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader)
{
    this->device = device;
    this->deviceContext = deviceContext;
    this->texture = texture;
    this->cb_vs_vertexshader = &cb_vs_vertexshader;

    float theta = 0;
    float posX = 0;
    float posY = 0;
    float radius = 0.7f;
    vector2<float> stores[21] = { vector2(0.f,0.f) };

    for (int i = 0; i <= 20; i++)
    {

        theta = ((MATHLIB_PI * i) / (20.f)) - (MATHLIB_PI / 2);
        posX = (radius * cos(theta))* 1.2f;//+2.0f;

        posY = (radius * sin(theta))*0.7f;//+0.7f;
        stores[i].x = posX;
        stores[i].y = posY;
    }


    Vertex v[] =
    {
        //Rectangle & texturing
        Vertex(-2.9f,  0.5f, 0.0f, 0.0f, 1.0f), //FRONT Bottom Left   - [0]
        Vertex(-2.9f,   1.2f, 0.0f, 0.0f, 0.0f), //FRONT Top Left      - [1]
        Vertex(-1.5f,   1.2f, 0.0f, 1.0f, 0.0f), //FRONT Top Right     - [2]
        Vertex(-1.5f,  0.5f, 0.0f, 1.0f, 1.0f), //FRONT Bottom Right   - [3]

        //Triangle
        Vertex(1.25f, 0.25f,0.0f, 0.0f, 1.0f), //[4]
        Vertex(2.0f, 1.45f, 0.0f, 0.0f, 0.0f),//[5]
        Vertex(2.75f,0.25f, 0.0f, 1.0f, 1.0f),//[6]

        //Quad
       Vertex(-2.50f, -2.25f,0.0f, 0.0f, 1.0f),//7
       Vertex(-2.50f, -1.25f,0.0f, 0.0f, 0.0f),//8
       Vertex(-1.0f,   -1.0f,0.0f, 1.0f, 0.0f), //9
        Vertex(-1.0f, -2.5f, 0.0f, 1.0f, 1.0f), //10

         //Line
          Vertex(0.5f, -1.5f, 0.0f, 1.0f, 1.0f),
          Vertex(0.5f, -1.47f, 0.0f, 1.0f, 1.0f),
          Vertex(2.5f, -1.0f, 0.0f, 1.0f, 1.0f),
          Vertex(2.5f, -0.97f, 0.0f, 1.0f, 1.0f),

          //Circle
          Vertex(stores[0].x, stores[0].y + radius,0.0f, 0.0f, 1.0f), //7
          Vertex(stores[0].x, stores[0].y,0.0f, 0.0f, 1.0f), //8
          Vertex(stores[1].x, stores[1].y,0.0f, 0.0f, 1.0f), //9


          Vertex(stores[1].x, stores[1].y ,0.0f, 0.0f, 1.0f),   //10
          Vertex(stores[2].x, stores[2].y, 0.0f , 0.0f, 1.0f),    //11


          Vertex(stores[2].x, stores[2].y ,0.0f, 0.0f, 1.0f),//12
          Vertex(stores[3].x, stores[3].y,0.0f, 0.0f, 1.0f), //13

          Vertex(stores[3].x, stores[3].y ,0.0f, 0.0f, 1.0f),//14
          Vertex(stores[4].x, stores[4].y, 0.0f, 0.0f, 1.0f), //15

          Vertex(stores[4].x, stores[4].y ,0.0f, 0.0f, 1.0f),//16
          Vertex(stores[5].x, stores[5].y, 0.0f, 0.0f, 1.0f), //17

          Vertex(stores[5].x, stores[5].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[6].x, stores[6].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[6].x, stores[6].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[7].x, stores[7].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[7].x, stores[7].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[8].x, stores[8].y ,0.0f, 0.0f, 1.0f),

          Vertex(stores[8].x, stores[8].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[9].x, stores[9].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[9].x, stores[9].y , 0.0f, 0.0f, 1.0f),
          Vertex(stores[10].x, stores[10].y,0.0f, 0.0f, 1.0f),

          Vertex(stores[10].x, stores[10].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[11].x, stores[11].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[11].x, stores[11].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[12].x, stores[12].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[12].x, stores[12].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[13].x, stores[13].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[13].x, stores[13].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[14].x, stores[14].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[14].x, stores[14].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[15].x, stores[15].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[15].x, stores[15].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[16].x, stores[16].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[16].x, stores[16].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[17].x, stores[17].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[17].x, stores[17].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[18].x, stores[18].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[18].x, stores[18].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[19].x, stores[19].y, 0.0f, 0.0f, 1.0f),

          Vertex(stores[19].x, stores[19].y ,0.0f, 0.0f, 1.0f),
          Vertex(stores[20].x, stores[20].y, 0.0f, 0.0f, 1.0f),//47

          /////////////////////////////////////////////half

          Vertex(stores[0].x, stores[0].y, 0.0f, 0.0f, 1.0f), //48
          Vertex(-stores[1].x, stores[1].y,0.0f, 0.0f, 1.0f), //49


          Vertex(-stores[1].x, stores[1].y ,0.0f, 0.0f, 1.0f),   //10
          Vertex(-stores[2].x, stores[2].y, 0.0f, 0.0f, 1.0f),    //11


          Vertex(-stores[2].x, stores[2].y ,0.0f, 0.0f, 1.0f),//12
          Vertex(-stores[3].x, stores[3].y, 0.0f, 0.0f, 1.0f), //13

          Vertex(-stores[3].x, stores[3].y ,0.0f, 0.0f, 1.0f),//14
          Vertex(-stores[4].x, stores[4].y, 0.0f, 0.0f, 1.0f), //15

          Vertex(-stores[4].x, stores[4].y ,0.0f, 0.0f, 1.0f),//16
          Vertex(-stores[5].x, stores[5].y, 0.0f, 0.0f, 1.0f), //17

          Vertex(-stores[5].x, stores[5].y ,0.0f , 0.0f, 1.0f),
          Vertex(-stores[6].x, stores[6].y, 0.0f , 0.0f, 1.0f),

          Vertex(-stores[6].x, stores[6].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[7].x, stores[7].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[7].x, stores[7].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[8].x, stores[8].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[8].x, stores[8].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[9].x, stores[9].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[9].x, stores[9].y , 0.0f, 0.0f, 1.0f),
          Vertex(-stores[10].x, stores[10].y,0.0f, 0.0f, 1.0f),

          Vertex(-stores[10].x, stores[10].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[11].x, stores[11].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[11].x, stores[11].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[12].x, stores[12].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[12].x, stores[12].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[13].x, stores[13].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[13].x, stores[13].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[14].x, stores[14].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[14].x, stores[14].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[15].x, stores[15].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[15].x, stores[15].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[16].x, stores[16].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[16].x, stores[16].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[17].x, stores[17].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[17].x, stores[17].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[18].x, stores[18].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[18].x, stores[18].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[19].x, stores[19].y, 0.0f, 0.0f, 1.0f),

          Vertex(-stores[19].x, stores[19].y ,0.0f, 0.0f, 1.0f),
          Vertex(-stores[20].x, stores[20].y, 0.0f, 0.0f, 1.0f),




    };

    //Load Vertex Data
    HRESULT hr = this->vertexBuffer.Initialize(this->device, v, ARRAYSIZE(v));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create vertex buffer.");
        return false;
    }

    DWORD indices[] =
    {
        //Rectangle
        0,1,2,
        0,2,3,
        //Triangle
        4,5,6,

        //Quad
        7,8,9,
        7,9,10,

        11,12,13,
        11,13,14,

        //Circle
        15,16,17,
        15,17,18,
        15,18,19,
        15,19,20,
        15,20,21,
        15,21,22,
        15,22,23,
        15,23,24,
        15,24,25,
        15,25,26,
        15,26,27,
        15,27,28,
        15,28,29,
        15,29,30,
        15,30,31,
        15,31,32,
        15,32,33,
        15,33,34,
        15,34,35,
        15,35,36,
        15,36,37,
        15,37,38,
        15,38,39,
        15,39,40,
        15,40,41,
        15,41,42,
        15,42,43,
        15,43,44,
        15,44,45,
        15,45,46,
        15,46,47,
        15,47,48,
        15,48,49,
        15,49,50,
        15,50,51,
        15,51,52,
        15,52,53,
        15,53,54,
        15,54,55,
        // 15//////
         15,55,56,
         15,56,57,
         15,57,58,
         15,58,59,
         15,59,60,
         15,60,61,

         15,61,62,
         15,62,63,
         15,63,64,
         15,64,65,
         15,65,66,
         15,66,67,
         15,67,68,
         15,68,69,
         15,69,70,
         15,70,71,
         15,71,72,
         15,72,73,
         15,73,74,
         15,74,75,
         15,75,76,
         15,76,77,
         15,77,78,
         15,78,79,
         15,79,80,
         15,80,81,
         15,81,82,
         15,82,83,
         15,83,84,
         15,84,85,
         15,85,86,
         15,86,87,
         15,87,88,
         15,88,89,
         15,89,90,
         15,90,91,
         15,91,92,
         15,92,93,
         15,93,94,
         15,94,95,


    };

    //Load index data

    hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create indices buffer");
        return hr;
    }
    this->SetPosition(0.0f, 0.0f, 0.0f);
    this->SetRotation(0.0f, 0.0f, 0.0f);
    this->UpdateWorldMatrix();
    return true;
}

void Model::SetTexture(ID3D11ShaderResourceView * texture)
{
    this->texture = texture;
}

void Model::Draw(const XMMATRIX & viewProjectionMatrix)
{
    //Update Constant buffer with WVP Matrix
    this->cb_vs_vertexshader->data.mat = this->worldMatrix * viewProjectionMatrix; //Calculate World-View-Projection Matrix
    this->cb_vs_vertexshader->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader->data.mat);

    this->cb_vs_vertexshader->ApplyChanges();
    this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());


    this->deviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
    this->deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
    UINT offset = 0;
    this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
    this->deviceContext->DrawIndexed(this->indexBuffer.BufferSize(), 0, 0); //Draw
}

void Model::UpdateWorldMatrix()
{
    this->worldMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
    XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
    this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
    this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
    this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
    this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}

const XMVECTOR & Model::GetPositionVector() const
{
    return this->posVector;
}

const XMFLOAT3 & Model::GetPositionFloat3() const
{
    return this->pos;
}

const XMVECTOR & Model::GetRotationVector() const
{
    return this->rotVector;
}

const XMFLOAT3 & Model::GetRotationFloat3() const
{
    return this->rot;
}

void Model::SetPosition(const XMVECTOR & pos)
{
    XMStoreFloat3(&this->pos, pos);
    this->posVector = pos;
    this->UpdateWorldMatrix();
}

void Model::SetPosition(const XMFLOAT3 & pos)
{
    this->pos = pos;
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateWorldMatrix();
}

void Model::SetPosition(float x, float y, float z)
{
    this->pos = XMFLOAT3(x, y, z);
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateWorldMatrix();
}

void Model::AdjustPosition(const XMVECTOR & pos)
{
    this->posVector += pos;
    XMStoreFloat3(&this->pos, this->posVector);
    this->UpdateWorldMatrix();
}

void Model::AdjustPosition(const XMFLOAT3 & pos)
{
    this->pos.x += pos.y;
    this->pos.y += pos.y;
    this->pos.z += pos.z;
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateWorldMatrix();
}

void Model::AdjustPosition(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->pos.z += z;
    this->posVector = XMLoadFloat3(&this->pos);
    this->UpdateWorldMatrix();
}

void Model::SetRotation(const XMVECTOR & rot)
{
    this->rotVector = rot;
    XMStoreFloat3(&this->rot, rot);
    this->UpdateWorldMatrix();
}

void Model::SetRotation(const XMFLOAT3 & rot)
{
    this->rot = rot;
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateWorldMatrix();
}

void Model::SetRotation(float x, float y, float z)
{
    this->rot = XMFLOAT3(x, y, z);
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateWorldMatrix();
}

void Model::AdjustRotation(const XMVECTOR & rot)
{
    this->rotVector += rot;
    XMStoreFloat3(&this->rot, this->rotVector);
    this->UpdateWorldMatrix();
}

void Model::AdjustRotation(const XMFLOAT3 & rot)
{
    this->rot.x += rot.x;
    this->rot.y += rot.y;
    this->rot.z += rot.z;
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateWorldMatrix();
}

void Model::AdjustRotation(float x, float y, float z)
{
    this->rot.x += x;
    this->rot.y += y;
    this->rot.z += z;
    this->rotVector = XMLoadFloat3(&this->rot);
    this->UpdateWorldMatrix();
}

void Model::SetLookAtPos(XMFLOAT3 lookAtPos)
{
    //Verify that look at pos is not the same as cam pos. They cannot be the same as that wouldn't make sense and would result in undefined behavior.
    if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z)
        return;

    lookAtPos.x = this->pos.x - lookAtPos.x;
    lookAtPos.y = this->pos.y - lookAtPos.y;
    lookAtPos.z = this->pos.z - lookAtPos.z;

    float pitch = 0.0f;
    if (lookAtPos.y != 0.0f)
    {
        const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
        pitch = atan(lookAtPos.y / distance);
    }

    float yaw = 0.0f;
    if (lookAtPos.x != 0.0f)
    {
        yaw = atan(lookAtPos.x / lookAtPos.z);
    }
    if (lookAtPos.z > 0)
        yaw += XM_PI;

    this->SetRotation(pitch, yaw, 0.0f);
}

const XMVECTOR & Model::GetForwardVector()
{
    return this->vec_forward;
}

const XMVECTOR & Model::GetRightVector()
{
    return this->vec_right;
}

const XMVECTOR & Model::GetBackwardVector()
{
    return this->vec_backward;
}

const XMVECTOR & Model::GetLeftVector()
{
    return this->vec_left;
}