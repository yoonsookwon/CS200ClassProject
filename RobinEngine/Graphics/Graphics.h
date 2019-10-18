#pragma once
#include "AdapterReader.h"

class Graphics
{
public:
    bool Init(HWND hwnd, int width, int height);

private:
    bool InitDirectX(HWND hwnd, int width, int height);

    //Work like smart pointer
    Microsoft::WRL::ComPtr<  ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>renderTargetView;
};
