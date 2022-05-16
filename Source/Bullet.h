#pragma once
#include"Graphics/Shader.h"
#include "Collision.h"
#include "Stage.h"
#include "Effect.h"

class BulletManager;

//弾丸
class Bullet
{
public:
	Bullet();
	~Bullet() {}

	//更新処理
	void Update(float elapsedTime);

	void Render(ID3D11DeviceContext* dc, Shader* shader,int flag);
	//void Render_c(ID3D11DeviceContext* dc, Shader* shader, bool flag) {};

	//速度更新処理
	//void UpdateVelocity(float elapsedTime);
	//
	////水平移動更新処理
	//void UpdateHorizontalMove(float elapsedTime);

	//bool RayCast(DirectX::XMFLOAT3& start, DirectX::XMFLOAT3& end, HitResult& hit);
	//bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)override;

	//発射の角度と位置の入力処理
	void Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position);

	//当たり判定
	void BulletRays(float elapsedTime);

	//反射
	void Reflection(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& Normal);


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

	//bool GetisMaterial() { return isMaterial; }
	//void SetisMateril(bool ismaterial) { this->isMaterial = ismaterial; }

	void SetSpeed(float speed) { this->speed = speed; }

	void RenderReflectingRay();

	void DrawDebugGUI();

	//弾が壁に当たっているか...連射の制御
	bool bulletFlag = false;
	////破棄
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

	// レイ描画バレット用
	//bool isMaterial = true;
	DirectX::XMFLOAT3 reflectedPosition[10] = {};
	int reflectCount = 0;

	DirectX::XMFLOAT3 currentPosition[999] = {};
	int timer, num = 0;
	int count = 0;
	float mx, my, mz = 0.0f;
};

