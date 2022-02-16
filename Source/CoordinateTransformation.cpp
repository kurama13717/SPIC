#include "CoordinateTransformation.h"

DirectX::XMFLOAT2 CoordinateTransformation::Get2DPosition(DirectX::XMMATRIX View, DirectX::XMMATRIX Projection, DirectX::XMMATRIX World, D3D11_VIEWPORT viewport, DirectX::XMFLOAT3 worldPosition)
{
	//�|�W�V�������x�N�g���ɕϊ�
	DirectX::XMVECTOR WorldPosition = DirectX::XMLoadFloat3(&worldPosition);
	//���[���h���W����X�N���[�����W�֕ϊ�����
	DirectX::XMVECTOR ScreenPosition = DirectX::XMVector3Project(
		WorldPosition, viewport.TopLeftX, viewport.TopLeftY,
		viewport.Width, viewport.Height, viewport.MinDepth, viewport.MaxDepth,
		Projection, View, World);
	//�X�N���[�����W
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