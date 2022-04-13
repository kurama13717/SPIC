#pragma once
#include"Graphics/Shader.h"
#include "Collision.h"
#include "Stage.h"

class BulletManager;

//�e��
class Bullet : public Stage
{
public:
	Bullet();
	virtual ~Bullet() {}

	//�X�V����
	void Update(float elapsedTime)override;

	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//���x�X�V����
	//void UpdateVelocity(float elapsedTime);
	//
	////�����ړ��X�V����
	//void UpdateHorizontalMove(float elapsedTime);

	//bool RayCast(DirectX::XMFLOAT3& start, DirectX::XMFLOAT3& end, HitResult& hit);
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;

	//���˂̊p�x�ƈʒu�̓��͏���
	void Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position);

	//�����蔻��
	void BulletRays(float elapsedTime);


	//�`�揈��

	//�f�o�b�O�v���~�e�B�u�`��
	virtual void DrawDebugPrimitive();

	//�ʒu�擾
	const DirectX::XMFLOAT3& GetPosition()const { return position; }

	//�����擾
	const DirectX::XMFLOAT3& GetDirection() const { return direction; }

	//�X�P�[���擾
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//���a�擾
	float GetRadius()const { return radius; }

	void DrawDebugGUI();

	////�j��
	//void Destroy();

protected:
	void UpdateTransform();
protected:
	DirectX::XMFLOAT3   position = { 0,0,0 };
	DirectX::XMFLOAT3   direction = { 0,0,1 };
	DirectX::XMFLOAT3   scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	BulletManager* manager = nullptr;
	float radius = 0.5f;
	float stepOffset = 1.0f;
	float speed = 10.0f;


	DirectX::XMFLOAT3 velocity = { 0,0,0 };
	DirectX::XMFLOAT4 color{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4* c = &color;


	Model* model = nullptr;



};
