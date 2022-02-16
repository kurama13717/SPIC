#include"CameraShake.h"

CameraShake::CameraShake()
{
}

void CameraShake::Shake(float elapsedTime)
{
	//D3D11_VIEWPORT viewport;
	////ビューポート左上X位置//ビューポート左上Y位置// ビューポート幅// ビューポート高さ
	//// 深度値の範囲を表す最小値// 深度値の範囲を表す最大値
	//UINT numViewports = 1;
	//dc->RSGetViewports(&numViewports, &viewport);
	seed += elapsedTime;


#if 0
	const float shake = 1.0f;
#else
	const float shake = 2.0f * static_cast<float>(pn.noise(seed * seed_shifting_factor, seed * seed_shifting_factor, 0)) - 1.0f;
#endif
	//data = XMMatrixTranslation(shake * max_shake_positon / graphics.GetScreenWidth(),shake * max_shake_positon / graphics.GetScreenHeight(), 0) *
	//	XMMatrixRotationRollPitchYaw(0, 0, XMConvertToRadians(shake * max_shake_angle));

		XMStoreFloat4x4(&data, XMMatrixTranslation(shake * max_shake_positon / graphics.GetScreenWidth(),shake * max_shake_positon / graphics.GetScreenHeight(), 0) *
		XMMatrixRotationRollPitchYaw(0, 0, XMConvertToRadians(shake * max_shake_angle)));

}

