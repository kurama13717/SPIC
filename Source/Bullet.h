#pragma once
#include"Graphics/Shader.h"
#include "Collision.h"
#include "Stage.h"
#include "Effect.h"

class BulletManager;

//�e��
class Bullet
{
public:
	Bullet();
	~Bullet() {}

	//�X�V����
	void Update(float elapsedTime);

	void Render(ID3D11DeviceContext* dc, Shader* shader,int flag);
	//void Render_c(ID3D11DeviceContext* dc, Shader* shader, bool flag) {};

	//���x�X�V����
	//void UpdateVelocity(float elapsedTime);
	//
	////�����ړ��X�V����
	//void UpdateHorizontalMove(float elapsedTime);

	//bool RayCast(DirectX::XMFLOAT3& start, DirectX::XMFLOAT3& end, HitResult& hit);
	//bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;

	//���˂̊p�x�ƈʒu�̓��͏���
	void Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position);

	//�����蔻��
	void BulletRays(float elapsedTime);

	//����
	void Reflection(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& Normal);


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

	//bool GetisMaterial() { return isMaterial; }
	//void SetisMateril(bool ismaterial) { this->isMaterial = ismaterial; }

	void SetSpeed(float speed) { this->speed = speed; }

	void RenderReflectingRay();

	void DrawDebugGUI();

	//�e���ǂɓ������Ă��邩...�A�˂̐���
	bool bulletFlag = false;
	////�j��
	//void Destroy();

protected:
	void UpdateTransform();
protected:
	DirectX::XMFLOAT3   position = { 0,0,0 };
	DirectX::XMFLOAT3   direction = { 0,0,1 };
	DirectX::XMFLOAT3   scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

private:
	BulletManager* manager = nullptr;
	float radius = 0.5f;
	float stepOffset = 1.0f;
	float speed = 10.0f;

	DirectX::XMFLOAT3 velocity = { 0,0,0 };
	DirectX::XMFLOAT4 color{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4* c = &color;

	DirectX::XMFLOAT3 start ={0,0,0};
	DirectX::XMFLOAT3 end	={0,0,0};


	Model* model = nullptr;

	// ���C�`��o���b�g�p
	//bool isMaterial = true;
	DirectX::XMFLOAT3 reflectedPosition[10] = {};
	int reflectCount = 0;

	DirectX::XMFLOAT3 currentPosition[999] = {};
	int timer, num = 0;
	int count = 0;
	float mx, my, mz = 0.0f;
};

