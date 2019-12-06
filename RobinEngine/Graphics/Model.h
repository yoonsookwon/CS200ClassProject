#pragma once;
#include "Vertex.h"
#include "vertexbuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "matrix4.hpp"
#include "vector3.hpp"
using namespace DirectX;

class Model
{
public:
    enum MeshType{
        Elipse,
        Line,
        Rectangle, 
        Triangle,
        Quad
    };
    bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader, Model::MeshType MeshType);
    void SetTexture(ID3D11ShaderResourceView * texture);
    void Draw(const matrix4<float> & viewProjectionMatrix);


   // void AdjustPosition(const XMFLOAT3 & pos);
    void AdjustPosition(float x, float y, float z);

    void AdjustScale(float scaleX, float scaleY);
  //  void AdjustRotation(const vector3<float> & rot);
  //  void AdjustRotation(const vec & pos);
    void AdjustRotation(float angle);

 ////   void SetLookAtPos(XMFLOAT3 lookAtPos);
 //   const XMVECTOR & GetForwardVector();
 //   const XMVECTOR & GetRightVector();
 //   const XMVECTOR & GetBackwardVector();
 //   const XMVECTOR & GetLeftVector();

    void UpdateWorldMatrix();
    float angle;
    vector2<float> translation;
    vector2<float> scale;
    vector3<float> rot;
private:

    ID3D11Device * device = nullptr;
    ID3D11DeviceContext * deviceContext = nullptr;
    ConstantBuffer<CB_VS_vertexshader> * cb_vs_vertexshader = nullptr;
    //
    ConstantBuffer<CB_PS_pixelshader> * cb_ps_pixelshader = nullptr;
    ID3D11ShaderResourceView * texture = nullptr;

    VertexBuffer<Vertex> vertexBuffer;
    IndexBuffer indexBuffer;

    matrix4<float> worldMatrix = MATRIX4::build_identity<float>();//XMMatrixIdentity();

    XMVECTOR posVector;
    XMVECTOR rotVector;
   // vector3<float> pos;


    vector2<float> rotate;



    const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
    const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
    const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

    XMVECTOR vec_forward;
    XMVECTOR vec_left;
    XMVECTOR vec_right;
    XMVECTOR vec_backward;
};