#include "Camera.h"

	// ビュー行列
void Camera::SetLookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT3& up)
{
	//vectorに変換してあげる(箱に入れる) 
	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
	//計算
	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	//情報を取り出す
	DirectX::XMStoreFloat4x4(&view, View);
	//ワールド座標に変換
	DirectX::XMMATRIX World = DirectX::XMMatrixInverse(nullptr, View);
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, World);
	//world = camerashake.GetData();
	this->right.x = world._11;
	this->right.y = world._12;
	this->right.z = world._13;

	this->up.x = world._21;
	this->up.y = world._22;
	this->up.z = world._23;

	this->front.x = world._31;
	this->front.y = world._32;
	this->front.z = world._33;

	this->eye = eye;
	this->focus = focus;
}
// プロジェクション行列
void Camera::SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ)
{
	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, nearZ, farZ);
	//Projection *= shake.GetShake();
	DirectX::XMStoreFloat4x4(&projection, Projection);
}
