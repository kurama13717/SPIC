#include "Reflection.h"
// R=F+2(−F⋅N)
// F=進行ベクトル
// N=法線ベクトル
// R=反射ベクトル
DirectX::XMFLOAT3 Reflection(DirectX::XMFLOAT3 F, DirectX::XMFLOAT3 N)
{
	DirectX::XMFLOAT3 R, FN, v;
	F = { F.x * -1.0f,F.y * -1.0f,F.z * -1.0f };	// -F
	FN = { F.x * N.x,F.y * N.y,F.z * N.z };			// -F*N
	v = { 2.0f * FN.x,2.0f * FN.y,2.0f * FN.z };	// 2*-FN
	R = { v.x - F.x,v.y - F.y,v.z - F.z };			// v-(-F)
	return R;
}