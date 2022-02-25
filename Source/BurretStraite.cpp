#include"BurretStraite.h"

//�R���X�g���N�^
BurretStraite::BurretStraite(BurretManager* manager) :Burret(manager)
{
	model = new Model("Data/model/Sword/Sword.mdl");

	//�\���T�C�Y�𒲐�
	scale.x = scale.y = scale.z = 3.0f;
}

//�f�X�g���N�^
BurretStraite::~BurretStraite()
{
	delete model;
}

//�X�V����
void BurretStraite::Update(float elapsedTime)
{
	//��������
	//lifeTimer -= 0.1f;
	if (lifeTimer < 0)
	{
		//�������폜
		Destroy();
	}
	//�ړ�
	float speed = this->speed * elapsedTime;
	position.x += direction.x * speed;
	position.z += direction.z * speed;

	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();
	//���f���s����X�V
	model->UpdateTransform(transform);
}

//�`�揈��
void BurretStraite::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}

//����
void BurretStraite::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
	this->direction = direction;
	this->position = position;
}