#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include"Graphics/Graphics.h"
#include"Camera.h"
class CoordinateTransformation
{
public:
   
    //3D->2Dç¿ïWÇ…ïœä∑//PositionÇï‘Ç∑
    DirectX::XMFLOAT2 Get2DPosition(DirectX::XMMATRIX View, DirectX::XMMATRIX Projection, DirectX::XMMATRIX World, D3D11_VIEWPORT viewport, DirectX::XMFLOAT3 worldPosition);
    //2D->3Dç¿ïWÇ…ïœä∑//VectorÇï‘Ç∑
    DirectX::XMVECTOR Get3DPosition(DirectX::XMMATRIX View, DirectX::XMMATRIX Projection, DirectX::XMMATRIX World, D3D11_VIEWPORT viewport, DirectX::XMVECTOR screenPosition);
};