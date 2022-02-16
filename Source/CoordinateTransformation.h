#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include"Graphics/Graphics.h"
#include"Camera.h"
class CoordinateTransformation
{
public:
   
    //3D->2D���W�ɕϊ�//Position��Ԃ�
    DirectX::XMFLOAT2 Get2DPosition(DirectX::XMMATRIX View, DirectX::XMMATRIX Projection, DirectX::XMMATRIX World, D3D11_VIEWPORT viewport, DirectX::XMFLOAT3 worldPosition);
    //2D->3D���W�ɕϊ�//Vector��Ԃ�
    DirectX::XMVECTOR Get3DPosition(DirectX::XMMATRIX View, DirectX::XMMATRIX Projection, DirectX::XMMATRIX World, D3D11_VIEWPORT viewport, DirectX::XMVECTOR screenPosition);
};