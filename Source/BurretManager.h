#pragma once
#include<vector>
#include"Burret.h"



class BurretManager
{
public:
	BurretManager();
	~BurretManager();

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	// �e�ۓo�^
	void Register(Burret* burret);

	//�e�ۑS�폜
	void Clear();

	//�e�ې��擾
	int GetBurretCount() const { return static_cast<int>(burrets.size()); }

	//�e�ێ擾
	Burret* GetBurret(int index) { return burrets.at(index); }

	//�e�ۍ폜
	void Remove(Burret* burret);

private:
	std::vector<Burret*> burrets;
	std::vector<Burret*> removes;
};