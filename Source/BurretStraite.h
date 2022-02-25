#pragma once

#include"Graphics/Model.h"
#include"BurretManager.h"

//’¼i’eŠÛ
class BurretStraite :public Burret
{
public:
	BurretStraite(BurretManager* manager);
	~BurretStraite()override;

	//XVˆ—
	void Update(float elapsedTime)override;

	//•`‰æˆ—
	void Render(ID3D11DeviceContext* dc, Shader* shader)override;

	//”­Ë
	void Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position);

private:
	Model* model = nullptr;
	float speed = 10.0f;
	float lifeTimer = 3.0f;
};
