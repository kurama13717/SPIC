#include"BurretStraite.h"

//コンストラクタ
BurretStraite::BurretStraite(BurretManager* manager) :Burret(manager)
{
	model = new Model("Data/model/Sword/Sword.mdl");

	//表示サイズを調整
	scale.x = scale.y = scale.z = 3.0f;
}

//デストラクタ
BurretStraite::~BurretStraite()
{
	delete model;
}

//更新処理
void BurretStraite::Update(float elapsedTime)
{
	//寿命処理
	//lifeTimer -= 0.1f;
	if (lifeTimer < 0)
	{
		//自分を削除
		Destroy();
	}
	//移動
	float speed = this->speed * elapsedTime;
	position.x += direction.x * speed;
	position.z += direction.z * speed;

	//オブジェクト行列を更新
	UpdateTransform();
	//モデル行列を更新
	model->UpdateTransform(transform);
}

//描画処理
void BurretStraite::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}

//発射
void BurretStraite::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
	this->direction = direction;
	this->position = position;
}