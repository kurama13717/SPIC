#include"BulletManager.h"

////�R���X�g���N�^
//BulletManager::BulletManager()
//{
//
//}
//
////�f�X�g���N�^
//BulletManager::~BulletManager()
//{
//	Clear();
//}

//�X�V����
void BulletManager::Update(float elapsedTime)
{
	//�X�V����
	for (Bullet* bullet : bullets)
	{
		bullet->Update(elapsedTime);
	}

	//�j������
	//bullets�͈̔�for������erase()����ƕs����������Ă��܂����߁A
	//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����
	for (Bullet* bullet : removes)
	{
		//std::vector����v�f���폜����ꍇ�̓C�e���[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<Bullet*>::iterator it = std::find(bullets.begin(), bullets.end(), bullet);

		if (it != bullets.end())
		{
			bullets.erase(it);
		}

		//�e�ۂ̔j������
		delete bullet;
	}
	//�j�����X�g���N���A
	removes.clear();
}

//�`�揈��
void BulletManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (Bullet* bullet : bullets)
	{
		bullet->Render(dc, shader,false);
	}
}

//�f�o�b�O�v���~�e�B�u�`��
void  BulletManager::DrawDebugPrimitive()
{
	for (Bullet* bullet : bullets)
	{
		bullet->DrawDebugPrimitive();
		bullet->RenderReflectingRay();
	}
}

// �e�ۓo�^
void BulletManager::Register(Bullet* bullet)
{
	bullets.emplace_back(bullet);
}

void BulletManager::Remove(Bullet* bullet)
{
	//�j�����X�g�ɒǉ�
	removes.emplace_back(bullet);
}

//bool BulletManager::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit,int index)
//{
//	bool result = false;
//	hit.distance = FLT_MAX;
//	for (Bullet* bullet : bullets)
//	{
//		HitResult tmp;
//		if (bullet->RayCast(start, end, tmp) && index == 0)
//		{
//			if (hit.distance > tmp.distance)
//			{
//				hit = tmp;
//				result = true;
//			}
//		}
//		if (bullet->RayCast(start, end, tmp) && index == 1)
//		{
//			if (hit.distance > tmp.distance)
//			{
//				hit = tmp;
//				result = true;
//			}
//		}
//
//	}
//	return result;
//}


//�e�ۑS�폜
void BulletManager::Clear()
{
	for (Bullet* bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();
}