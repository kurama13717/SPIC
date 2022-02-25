#include"BurretManager.h"

//コンストラクタ
BurretManager::BurretManager()
{

}

//デストラクタ
BurretManager::~BurretManager()
{
	Clear();
}

//更新処理
void BurretManager::Update(float elapsedTime)
{
	//更新処理
	for (Burret* burret : burrets)
	{
		burret->Update(elapsedTime);
	}

	//破棄処理
	//burretsの範囲for文中でerase()すると不具合が発生してしまうため、
	//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する
	for (Burret* burret : removes)
	{
		//std::vectorから要素を削除する場合はイテレーターで削除しなければならない
		std::vector<Burret*>::iterator it = std::find(burrets.begin(), burrets.end(), burret);

		if (it != burrets.end())
		{
			burrets.erase(it);
		}

		//弾丸の破棄処理
		delete burret;
	}
	//破棄リストをクリア
	removes.clear();
}

//描画処理
void BurretManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (Burret* burret : burrets)
	{
		burret->Render(dc, shader);
	}
}

//デバッグプリミティブ描画
void  BurretManager::DrawDebugPrimitive()
{
	for (Burret* burret : burrets)
	{
		burret->DrawDebugPrimitive();
	}
}

// 弾丸登録
void BurretManager::Register(Burret* burret)
{
	burrets.emplace_back(burret);
}

void BurretManager::Remove(Burret* burret)
{
	//破棄リストに追加
	removes.emplace_back(burret);
}


//弾丸全削除
void BurretManager::Clear()
{
	for (Burret* burret : burrets)
	{
		delete burret;
	}
	burrets.clear();
}