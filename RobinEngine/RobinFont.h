/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#pragma once
#include "BitmapFont.hpp"
#include "Graphics/Model.h"
#include <d3d11.h>
#include <vector2.hpp>

class RobinFont
{
public:
    RobinFont() {};
    void Init(ID3D11Device* _device, ID3D11DeviceContext* _device_context,ConstantBuffer<CB_VS_vertexshader>& _constant_vsBuffer);
    void Update();
    void SetText(std::wstring text, float offsetX, float offsetY = 1.5f);

private:
    BitmapFont robin_font;
    ID3D11Device* device;
    ID3D11DeviceContext* device_context;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> font;
    ConstantBuffer<CB_VS_vertexshader>* constant_vsBuffer;
    ConstantBuffer<CB_PS_pixelshader> constant_psBuffer;
    VertexBuffer<Vertex> vertexBuffer;
    IndexBuffer indexBuffer;
    Vertex* v;
    DWORD *indices;

};
