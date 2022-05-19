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


	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//デバッグプリミティブ描画
	void DrawDebugPrimitive();

	// 弾丸登録
	void Register(Bullet* bullet);


	//弾丸全削除
	void Clear();

	//弾丸数取得
	int GetBulletCount() const { return static_cast<int>(bullets.size()); }

	//弾丸取得
	Bullet* GetBullet(int index) { return bullets.at(index); }

	bool GetisMaterial() { return isMaterial; }
	void SetisMateril(bool ismaterial) { this->isMaterial = ismaterial; }

	bool GetisClearFlag() { return ClearFlag; }
	void SetClearFlag(bool ClearFlag) { this->ClearFlag = ClearFlag; }

	bool GetPrediction() { return prediction; }
	void SetPrediction(bool prediction) { this->prediction = prediction; }



	const DirectX::XMFLOAT3 GetPosition(int index) const { return reflectedPosition[index]; }
	void SetPosition( DirectX::XMFLOAT3 Position,int index) { this->reflectedPosition[index] = Position; }
	

	//弾丸削除
	void Remove(Bullet* bullet);

	//レイキャスト
	//bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit, int index);



private:
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> removes;

	DirectX::XMFLOAT3 reflectedPosition[10] = {};

	bool isMaterial = true;
	bool ClearFlag = false;
	bool prediction = false;

};