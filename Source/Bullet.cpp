//内積　
//Inner Product   Product(積)Inner(内側の)
//Dot Product 
//Scalar   Scalar(スカラー)

//外積
//Outer Product
//Cross Product
//Vector Product

#include"Bullet.h"
#include"BulletManager.h"
#include "Player.h"
#include "StageManager.h"
#include"Graphics/Graphics.h"
#include <functional>


//コンストラクタ
Bullet::Bullet()
{
    model = new Model("Data/model/Sword/Sword.mdl");

    //表示サイズを調整
    scale.x = scale.y = scale.z = 3.0f;

	//trajectEffect = new Effect("Data/Effect/Trajectory.efkefc");
	trajectEffect = new Effect("Data/Effect/Hit.efkefc");
}

//デバッグプリミティブ描画
void Bullet::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバッグ球を描画
	debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));


}



////void Bullet::UpdateVelocity(float elapsedTime)
//{
//	//水平移動更新処理
//	UpdateHorizontalMove(elapsedTime);
//}

/*void Bullet::UpdateHorizontalMove(float elapsedTime)
{
    //position.x += velocity.x * elapsedTime;
    //position.z += velocity.z * elapsedTime

    //水平速力量計算
    float velocityLengthXZ = sqrtf(position.x * position.x + position.z * position.z);
    if (velocityLengthXZ > 0.0f)
    {
        float mx = position.x * elapsedTime;
        float mz = position.z * elapsedTime;

        DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
        DirectX::XMFLOAT3 end = { position.x + mx, position.y + stepOffset, position.z + mz };

        HitResult hit;
        if (StageManager::Instance().RayCast(start, end, hit))
        {
            DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
            DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);

            DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);
            //逆ベクトルと法線ベクトルの内積
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(DirectX::XMVectorNegate(Vec), Normal);

            // 補正位置の計算
            //法線ベクトル*内積+レイの終端//Rベクトル求める
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiplyAdd(Normal, Dot, End);
            DirectX::XMFLOAT3 collectPosition;
            DirectX::XMStoreFloat3(&collectPosition, CollectPosition);
            // 壁ずり方向へレイキャスト
            HitResult hit2;
            if (!StageManager::Instance().RayCast(hit.position, collectPosition, hit2))
            {
                // 壁ずり方向で壁に当たらなかったら補正位置に移動
                position.x = collectPosition.x;
                position.z = collectPosition.z;
            }
            else
            {
                position.x = hit2.position.x;
                position.z = hit2.position.z;
            }
        }
        else
        {
            position.x += mx;
            position.z += mz;
        }
    }
}





void Bullet::UpdateTransform()
{
	DirectX::XMVECTOR Front, Up, Right;

	//前ベクトルを算出 z
	Front = DirectX::XMLoadFloat3(&direction);
	Front = DirectX::XMVector3Normalize(Front);

	//仮の上ベクトルを算出  y
	Up = DirectX::XMVectorSet(0.001f, 1, 0, 0);
	//「同じベクトルで外積するとゼロベクトルになる」 現象を防ぐため0.001f
	Up = DirectX::XMVector3Normalize(Up);

	//右ベクトルを算出 x
	Right = DirectX::XMVector3Cross(Up, Front);
	Right = DirectX::XMVector3Normalize(Right);

	//上ベクトルを算出 y
	Up = DirectX::XMVector3Cross(Front, Right);


	DirectX::XMFLOAT3 right, up, front;
	DirectX::XMStoreFloat3(&right, Right);
	DirectX::XMStoreFloat3(&up, Up);
	DirectX::XMStoreFloat3(&front, Front);

	//とりあえず、仮で回転は無視した行列を作成する
	transform._11 = right.x * scale.x;
	transform._12 = right.y * scale.x;
	transform._13 = right.z * scale.x;
	transform._14 = 0.0f;
	transform._21 = up.x * scale.y;
	transform._22 = up.y * scale.y;
	transform._23 = up.z * scale.y;
	transform._24 = 0.0f;
	transform._31 = front.x * scale.z;
	transform._32 = front.y * scale.z;
	transform._33 = front.z * scale.z;
	transform._34 = 0.0f;
	transform._41 = position.x;
	transform._42 = position.y;
	transform._43 = position.z;
	transform._44 = 1.0f;

	//発射方向
	this->direction = front;
}




//破棄
void Bullet::Destroy()
{
	manager->Remove(this);
}*/

void Bullet::Update(float elapsedTime)
{
	//移動
	//float speed = this->speed * elapsedTime;
	//position.x += direction.x * speed;
	//position.y += direction.y * speed;
	//position.z += direction.z * speed;

	if (Player::Instance().GetFiring()) {
		BulletRays(elapsedTime);
	}
	//オブジェクト行列を更新
	UpdateTransform();
	//モデル行列を更新
	model->UpdateTransform(transform);
}


void Bullet::UpdateTransform()
{
		// スケール行列を作成
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
		// 全部サイズが固定だとだめだから変数入れる

		// 回転行列を作成
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(direction.x, direction.y, direction.z);
		// オイラー角

		// 位置行列を作成
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

		// 3つの行列を組み合わせ、ワールド行列を作成
		DirectX::XMMATRIX W = S * R * T;
		// ☆　行列の順番を変えてはいけない

		// 計算したワールド行列を取り出す //再変換
		DirectX::XMStoreFloat4x4(&transform, W);
}


void Bullet::Render(ID3D11DeviceContext* dc, Shader* shader,int flag)
{

	shader->Draw(dc, model,c);
}

//発射
void Bullet::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
	this->direction = direction;
	this->position = position;
}


bool Bullet::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	return Collision::IntersectRayVsModel(start, end, model, hit);
}


//当たり判定
void Bullet::BulletRays(float elapsedTime)
{
	//水平速力量計算
	float velocityLengthXZ = sqrtf(direction.x * direction.x + direction.z * direction.z);
	if (velocityLengthXZ > 0.0f)
	{
		float mx = direction.x * elapsedTime * 10.0f;
		float my = direction.y * elapsedTime * 10.0f;
		float mz = direction.z * elapsedTime * 10.0f;

		DirectX::XMFLOAT3 start = { position.x, position.y, position.z };
		DirectX::XMFLOAT3 end = { position.x + mx , position.y + my, position.z + mz };

		HitResult hit;
		if (StageManager::Instance().RayCast(start, end, hit))
		{
			if (StageManager::Instance().a == 1) {
				Player::Instance().Destroy();
				Player::Instance().SetFiring(false);
				if (StageManager::Instance().flag0_r) {
					if (StageManager::Instance().flag1_r) {
						if (StageManager::Instance().flag2_r) {

						}
						StageManager::Instance().flag2_r = false;

					}
					StageManager::Instance().flag1_r = false;


				}
				StageManager::Instance().flag0_r = false;


			}

			if (StageManager::Instance().a == 2) {
				Reflection(direction, hit.normal);

			}


			

			//	DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
			//	DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
			//	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);

			//	DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);
			//	//逆ベクトルと法線ベクトルの内積
			//	DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(DirectX::XMVectorNegate(Vec), Normal);

			//	// 補正位置の計算
			//	//法線ベクトル*内積+レイの終端//Rベクトル求める
			//	DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiplyAdd(Normal, Dot, End);
			//	DirectX::XMFLOAT3 collectPosition;
			//	DirectX::XMStoreFloat3(&collectPosition, CollectPosition);
			//	// 壁ずり方向へレイキャスト
			//	HitResult hit2;
			//	if (!StageManager::Instance().RayCast(hit.position, collectPosition, hit2))
			//	{
			//		// 壁ずり方向で壁に当たらなかったら補正位置に移動
			//		position.x = collectPosition.x;
			//		position.z = collectPosition.z;
			//	}

			//	else
			//	{
			//		position.x = hit2.position.x;
			//		position.y = hit2.position.y;
			//		position.z = hit2.position.z;
			//	}
			//}
		}
		else
		{
			position.x += mx;
			position.y += my;
			position.z += mz;
		}
	}

}

//反射
void Bullet::Reflection(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& Normal)
{
	DirectX::XMFLOAT3 Dir, Reflect, Vec;
	float FN;
	// R=F+2(-F⋅N)N
	// F=進行ベクトル
	// N=法線ベクトル
	// R=反射ベクトル
	Dir = { direction.x * -1.0f,direction.y * -1.0f,direction.z * -1.0f };        // -Dir
	FN = { Dir.x * Normal.x + Dir.y * Normal.y + Dir.z * Normal.z };            // -DirNormal
	Vec = { 2.0f * FN * Normal.x,2.0f * FN * Normal.y,2.0f * FN * Normal.z };    // 2(-FN)Normal
	Reflect = { Vec.x - Dir.x,Vec.y - Dir.y,Vec.z - Dir.z };                    // Vec-(-Dir)
	this->direction = Reflect;
}



void Bullet::DrawDebugGUI()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Bullet", nullptr, ImGuiWindowFlags_None))
	{
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//position
			ImGui::InputFloat3("Position", &BulletManager::Instance().GetBullet(0)->position.x);
			//angle
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(this->direction.x);
			a.y = DirectX::XMConvertToDegrees(this->direction.y);
			a.z = DirectX::XMConvertToDegrees(this->direction.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle[1].x = DirectX::XMConvertToRadians(a.x);
			angle[1].y = DirectX::XMConvertToRadians(a.y);
			angle[1].z = DirectX::XMConvertToRadians(a.z);
			//scale
			ImGui::InputFloat3("Scale", &scale.x);
		}

	}
	ImGui::End();
}