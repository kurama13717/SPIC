#include"BulletStraite.h"




//�f�X�g���N�^
//BulletStraite::~BulletStraite()
//{
//	//delete model;
//}

//�X�V����
//void BulletStraite::Update(float elapsedTime)
//{
//	//��������
//	//lifeTimer -= 0.1f;
//	//if (lifeTimer < 0)
//	//{
//	//	//�������폜
//	//	Destroy();
//	//}
//	//�ړ�
//	float speed = this->speed * elapsedTime;
//	position.x += direction.x * speed;
//	position.y += direction.y * speed;
//	position.z += direction.z * speed;
//
//	//�I�u�W�F�N�g�s����X�V
//	UpdateTransform();
//	//���f���s����X�V
//	model->UpdateTransform(transform);
//
//	//UpdateVelocity(elapsedTime);
//}

//�`�揈��
//void BulletStraite::Render(ID3D11DeviceContext* dc, Shader* shader)
//{
//	shader->Draw(dc, model);
//}

//bool BulletStraite::RayCast(DirectX::XMFLOAT3& start, DirectX::XMFLOAT3& end, HitResult& hit)
//{
//	return Collision::IntersectRayVsModel(start, end, model, hit);
//
//}


////����
//void BulletStraite::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
//{
//	this->direction = direction;
//	this->position = position;
//}