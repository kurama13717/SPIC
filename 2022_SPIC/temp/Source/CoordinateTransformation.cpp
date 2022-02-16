#include "CoordinateTransformation.h"

DirectX::XMFLOAT2 CoordinateTransformation::Get2DPosition(DirectX::XMMATRIX View, DirectX::XMMATRIX Projection, DirectX::XMMATRIX World, D3D11_VIEWPORT viewport, DirectX::XMFLOAT3 worldPosition)
{
	//ポジションをベクトルに変換
	DirectX::XMVECTOR WorldPosition = DirectX::XMLoadFloat3(&worldPosition);
	//ワールド座標からスクリーン座標へ変換する
	DirectX::XMVECTOR ScreenPosition = DirectX::XMVector3Project(
		WorldPosition, viewport.TopLeftX, viewport.TopLeftY,
		viewport.Width, viewport.Height, viewport.MinDepth, viewport.MaxDepth,
		Projection, View, World);
	//スクリーン座標
	DirectX::XMFLOAT2 screenPosition;
	DirectX::XMStoreFloat2(&screenPosition, ScreenPosition);
	return screenPosition;
}

DirectX::XMVECTOR CoordinateTransformation::Get3DPosition(DirectX::XMMATRIX View, DirectX::XMMATRIX Projection, DirectX::XMMATRIX World, D3D11_VIEWPORT viewport, DirectX::XMVECTOR screenPosition)
{
	DirectX::XMVECTOR WorldPosition = DirectX::XMVector3Unproject(
		screenPosition,
		viewport.TopLeftX,
		viewport.TopLeftY,
		viewport.Width,
		viewport.Height,
		viewport.MinDepth,
		viewport.MaxDepth,
		Projection,
		View,
		World
	);
	return WorldPosition;
}