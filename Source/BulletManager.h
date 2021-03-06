#pragma once
#include<vector>
#include"Bullet.h"



class BulletManager
{
public:
	BulletManager() {};
	~BulletManager() {};
	static BulletManager& Instance()
	{
		static BulletManager instance;
		return instance;
	}


	//?X?V????
	void Update(float elapsedTime);

	//?`?揈??
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//?f?o?b?O?v???~?e?B?u?`??
	void DrawDebugPrimitive();

	// ?e?ۓo?^
	void Register(Bullet* bullet);


	//?e?ۑS?폜
	void Clear();

	//?e?ې??擾
	int GetBulletCount() const { return static_cast<int>(bullets.size()); }

	//?e?ێ擾
	Bullet* GetBullet(int index) { return bullets.at(index); }

	bool GetisMaterial() { return isMaterial; }
	void SetisMateril(bool ismaterial) { this->isMaterial = ismaterial; }

	bool GetisClearFlag() { return ClearFlag; }
	void SetClearFlag(bool ClearFlag) { this->ClearFlag = ClearFlag; }

	bool GetPrediction() { return prediction; }
	void SetPrediction(bool prediction) { this->prediction = prediction; }



	const DirectX::XMFLOAT3 GetPosition(int index) const { return reflectedPosition[index]; }
	void SetPosition( DirectX::XMFLOAT3 Position,int index) { this->reflectedPosition[index] = Position; }
	

	//?e?ۍ폜
	void Remove(Bullet* bullet);

	//???C?L???X?g
	//bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit, int index);



private:
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> removes;

	DirectX::XMFLOAT3 reflectedPosition[10] = {};

	bool isMaterial = true;
	bool ClearFlag = false;
	bool prediction = false;

};