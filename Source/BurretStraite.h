#pragma once

#include"Graphics/Model.h"
#include"BurretManager.h"

//���i�e��
class BurretStraite :public Burret
{
public:
	BurretStraite(BurretManager* manager);
	~BurretStraite()override;

	//�X�V����
	void Update(float elapsedTime)override;

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader)override;

	//����
	void Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position);

private:
	Model* model = nullptr;
	float speed = 10.0f;
	float lifeTimer = 3.0f;
};
