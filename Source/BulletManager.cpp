#include"BulletManager.h"

////コンストラクタ
//BulletManager::BulletManager()
//{
//
//}
//
////デストラクタ
//BulletManager::~BulletManager()
//{
//	Clear();
//}

//更新処理
void BulletManager::Update(float elapsedTime)
{
	//更新処理
	for (Bullet* bullet : bullets)
	{
		bullet->Update(elapsedTime);
	}

	//破棄処理
	//bulletsの範囲for文中でerase()すると不具合が発生してしまうため、
	//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する
	for (Bullet* bullet : removes)
	{
		//std::vectorから要素を削除する場合はイテレーターで削除しなければならない
		std::vector<Bullet*>::iterator it = std::find(bullets.begin(), bullets.end(), bullet);

		if (it != bullets.end())
		{
			bullets.erase(it);
		}

		//弾丸の破棄処理
		delete bullet;
	}
	//破棄リストをクリア
	removes.clear();
}

//描画処理
void BulletManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (Bullet* bullet : bullets)
	{
		bullet->Render(dc, shader,false);
	}
}

//デバッグプリミティブ描画
void  BulletManager::DrawDebugPrimitive()
{
	for (Bullet* bullet : bullets)
	{
		bullet->DrawDebugPrimitive();
		bullet->RenderReflectingRay();
	}
}

// 弾丸登録
void BulletManager::Register(Bullet* bullet)
{
	bullets.emplace_back(bullet);
}

void BulletManager::Remove(Bullet* bullet)
{
	//破棄リストに追加
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


//弾丸全削除
void BulletManager::Clear()
{
	for (Bullet* bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();
}