#include  "Graphics.h"

bool Graphics::Init(HWND hwnd, int width, int height)
{
    if (!InitDirectX(hwnd, width, height))
        return  false;

    if(!InitShaders())
        return false;

    if(!InitScene())
        return false;

    return  true;
}

void Graphics::RenderFrame()
{
    //Able to set up background color
    float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);

    this->deviceContext->IASetInputLayout(this->vertexshader.GetInputLayout());
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    this->deviceContext->RSSetState(this->rasterizerState.Get());

    this->deviceContext->VSSetShader(vertexshader.GetShader(), NULL, 0);
    this->deviceContext->PSSetShader(pixelshader.GetShader(), NULL, 0);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);


    this->deviceContext->Draw(3, 0);

    //If want to turn on the vSync put the value 1, otherwise put 0 
    this->swapChain->Present(1, NULL);
}

bool Graphics::InitDirectX(HWND hwnd, int width, int height)
{
    std::vector<AdapterData> adapters = AdapterReader::GetAdapters();

    if(adapters.size() < 1)
    {
        ErrorLogger::Log("No IDXGI Adapters found.");
        return false;
    }

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;

    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;

    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = hwnd;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    //Ʃ�丮�� 9
    HRESULT hr;
    hr = D3D11CreateDeviceAndSwapChain(adapters[0].pAdapter, 
                                D3D_DRIVER_TYPE_UNKNOWN,
                          NULL,
                            NULL,
                      NULL,
                       0,
                         D3D11_SDK_VERSION,
                                 &scd,
                        this->swapChain.GetAddressOf(),
                          this->device.GetAddressOf(),
                       NULL,
                   this->deviceContext.GetAddressOf());
    if(FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create device and swapchain.");
        return  false;
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer;
    hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backbuffer.GetAddressOf()));

    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "GetBuffer Failed");
        return  false;
    }

    hr = this->device->CreateRenderTargetView(backbuffer.Get(), NULL, this->renderTargetView.GetAddressOf());

    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create render target view");
        return  false;
    }
    this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), NULL);

    //Create Viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = width;
    viewport.Height = height;

    //Set the viewport
    this->deviceContext->RSSetViewports(1, &viewport);

    //Create Rasterizer State
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

    //RasterizerDesc!! 
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
   /* rasterizerDesc.FrontCounterClockwise = TRUE;*/

    hr = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizerState.GetAddressOf());
    if(hr != S_OK)
    {
        ErrorLogger::Log(hr, "Failed to create rasterizer state.");
        return false;
    }

    return  true;
}

bool Graphics::InitShaders()
{
    std::wstring shaderfolder = L"";
#pragma  region DetermineShaderPath

    if (IsDebuggerPresent() == TRUE) 
    {
#ifdef  _DEBUG // Debug mode
#ifdef  _WIN64 //x64
        shaderfolder = L"..\\x64\\Debug\\";
#else //x86(Win32)
        shaderfloder = L"..\\Debug\\";
#endif
#else // Release mode
#ifdef _WIN64
        shaderfolder = L"..\\x64\\Release\\";
#else
        shaderfolder = L"..\\Release\\";
#endif
#endif
    }

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION",0,DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA}
    };

    UINT numElements = ARRAYSIZE(layout);


    if (!vertexshader.Initialize(this->device,  shaderfolder + L"vertexshader.cso",layout,numElements))
        return  false;

    if(!pixelshader.Initialize(this->device, shaderfolder + L"pixelshader.cso"))
        return false;

    return true;
}

bool Graphics::InitScene()
{
    Vertex v[] = {
        //Ordering must be ClockWise
        Vertex(-0.5f, -0.5f, 1.0f, 0.0f,0.0f),//bottom left
        Vertex(0.0f,   0.5f,0.0f,1.0f,0.0f), //top middle 
        Vertex(0.5f, -0.5f, 0.0f,0.0f,1.0f), //bottom right
    };

    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(Vertex)* ARRAYSIZE(v);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexBufferData;
    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = v;

    HRESULT hr = this->device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, this->vertexBuffer.GetAddressOf());

    if(FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create vertex buffer.");
        return false;
    }
    return true;
}