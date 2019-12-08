#pragma once
#include "Vertex.h"
#include "vertexbuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include  "ConstantBufferTypes.h"
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
    enum ModelType
    {
        HierarchicalBODY
    };
    ModelType HierarchicalTYPE = HierarchicalBODY;
    
    bool Initialize(ID3D11Device * _device, ID3D11DeviceContext * _deviceContext, ID3D11ShaderResourceView * _texture, ConstantBuffer<CB_VS_vertexshader> & _cb_vs_vertexshader, Model::MeshType MeshType);
    void SetTexture(ID3D11ShaderResourceView * _texture);
    void Draw(const matrix4<float> & viewProjectionMatrix);

    void AdjustPosition(float x, float y);
    void AdjustScale(float scaleX, float scaleY);
    void AdjustRotation(float angle);

    void UpdateWorldMatrix();
    float angle;
    vector2<float> translation;
    vector2<float> scale;
    vector3<float> rot;
   
private:

    ID3D11Device * device = nullptr;
    ID3D11DeviceContext * deviceContext = nullptr;
    ConstantBuffer<CB_VS_vertexshader> * cb_vs_vertexshader = nullptr;
    
    ConstantBuffer<CB_PS_pixelshader> * cb_ps_pixelshader = nullptr;
    ID3D11ShaderResourceView * texture = nullptr;

    VertexBuffer<Vertex> vertexBuffer;
    IndexBuffer indexBuffer;

    matrix4<float> worldMatrix = MATRIX4::build_identity<float>();


    vector2<float> rotate;


};