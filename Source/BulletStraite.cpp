#include"BulletStraite.h"




//デストラクタ
//BulletStraite::~BulletStraite()
//{
//	//delete model;
//}

//更新処理
//void BulletStraite::Update(float elapsedTime)
//{
//	//寿命処理
//	//lifeTimer -= 0.1f;
//	//if (lifeTimer < 0)
//	//{
//	//	//自分を削除
//	//	Destroy();
//	//}
//	//移動
//	float speed = this->speed * elapsedTime;
//	position.x += direction.x * speed;
//	position.y += direction.y * speed;
//	position.z += direction.z * speed;
//
//	//オブジェクト行列を更新
//	UpdateTransform();
//	//モデル行列を更新
//	model->UpdateTransform(transform);
//
//	//UpdateVelocity(elapsedTime);
//}

//描画処理
//void BulletStraite::Render(ID3D11DeviceContext* dc, Shader* shader)
//{
//	shader->Draw(dc, model);
//}

//bool BulletStraite::RayCast(DirectX::XMFLOAT3& start, DirectX::XMFLOAT3& end, HitResult& hit)
//{
//	return Collision::IntersectRayVsModel(start, end, model, hit);
//
//}


////発射
//void BulletStraite::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
//{
//	this->direction = direction;
//	this->position = position;
//}