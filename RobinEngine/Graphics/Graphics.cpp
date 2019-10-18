#include  "Graphics.h"

bool Graphics::Init(HWND hwnd, int width, int height)
{
    if (!InitDirectX(hwnd, width, height))
        return  false;

    return  true;
}

bool Graphics::InitDirectX(HWND hwnd, int width, int height)
{
    std::vector<AdapterData> adapters = AdapterReader::GetAdapters();

    return  true;
}
