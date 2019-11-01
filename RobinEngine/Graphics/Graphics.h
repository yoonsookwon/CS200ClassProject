#pragma once
#include "AdapterReader.h"
#include  "Shaders.h"
#include "Vertex.h"

class Graphics
{
public:
    bool Init(HWND hwnd, int width, int height);
    void RenderFrame();

private:
    bool InitDirectX(HWND hwnd, int width, int height);
    bool InitShaders();
    bool InitScene();

    //Work like smart pointer
    Microsoft::WRL::ComPtr<  ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>renderTargetView;


    VertexShader vertexshader;
    PixelShader pixelshader;

    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
};
