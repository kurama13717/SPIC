#pragma once
#include"Graphics/Shader.h"
#include "Collision.h"
#include "Stage.h"

class BulletManager;

//弾丸
class Bullet : public Stage
{
public:
	Bullet();
	virtual ~Bullet() {}

	//更新処理
	void Update(float elapsedTime)override;

	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//速度更新処理
	//void UpdateVelocity(float elapsedTime);
	//
	////水平移動更新処理
	//void UpdateHorizontalMove(float elapsedTime);

	//bool RayCast(DirectX::XMFLOAT3& start, DirectX::XMFLOAT3& end, HitResult& hit);
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;

	//発射の角度と位置の入力処理
	void Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position);

	//当たり判定
	void BulletRays(float elapsedTime);


	//描画処理

	//デバッグプリミティブ描画
	virtual void DrawDebugPrimitive();

	//位置取得
	const DirectX::XMFLOAT3& GetPosition()const { return position; }

	//方向取得
	const DirectX::XMFLOAT3& GetDirection() const { return direction; }

	//スケール取得
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//半径取得
	float GetRadius()const { return radius; }

	void DrawDebugGUI();

	////破棄
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

