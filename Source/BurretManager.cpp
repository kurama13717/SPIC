#include"BurretManager.h"

//�R���X�g���N�^
BurretManager::BurretManager()
{

}

//�f�X�g���N�^
BurretManager::~BurretManager()
{
	Clear();
}

//�X�V����
void BurretManager::Update(float elapsedTime)
{
	//�X�V����
	for (Burret* burret : burrets)
	{
		burret->Update(elapsedTime);
	}

	//�j������
	//burrets�͈̔�for������erase()����ƕs����������Ă��܂����߁A
	//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����
	for (Burret* burret : removes)
	{
		//std::vector����v�f���폜����ꍇ�̓C�e���[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<Burret*>::iterator it = std::find(burrets.begin(), burrets.end(), burret);

		if (it != burrets.end())
		{
			burrets.erase(it);
		}

		//�e�ۂ̔j������
		delete burret;
	}
	//�j�����X�g���N���A
	removes.clear();
}

//�`�揈��
void BurretManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (Burret* burret : burrets)
	{
		burret->Render(dc, shader);
	}
}

//�f�o�b�O�v���~�e�B�u�`��
void  BurretManager::DrawDebugPrimitive()
{
	for (Burret* burret : burrets)
	{
		burret->DrawDebugPrimitive();
	}
}

// �e�ۓo�^
void BurretManager::Register(Burret* burret)
{
	burrets.emplace_back(burret);
}

void BurretManager::Remove(Burret* burret)
{
	//�j�����X�g�ɒǉ�
	removes.emplace_back(burret);
}


//�e�ۑS�폜
void BurretManager::Clear()
{
	for (Burret* burret : burrets)
	{
		delete burret;
	}
	burrets.clear();
}