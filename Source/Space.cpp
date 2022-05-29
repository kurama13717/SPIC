#include "Space.h"


SpaceDome::SpaceDome()
{
	//仮
	model.push_back(std::make_unique<Model>("Data/Model/宇宙/universe.mdl"));
	model[0]->position = { 0.0f,0.0f,0.0f };
	model[0]->scale = { 5,5,5 };



}

void SpaceDome::UpdateTransform()
{
	for (auto& models : model) {
		// スケール行列を作成
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(models->scale.x, models->scale.y, models->scale.z);
		// 全部サイズが固定だとだめだから変数入れる

		// 回転行列を作成
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(models->angle.x, models->angle.y, models->angle.z);
		// オイラー角

		// 位置行列を作成
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(models->position.x, models->position.y, models->position.z);

		// 3つの行列を組み合わせ、ワールド行列を作成
		DirectX::XMMATRIX W = S * R * T;
		// ☆　行列の順番を変えてはいけない

		// 計算したワールド行列を取り出す //再変換
		DirectX::XMStoreFloat4x4(&models->transform, W);
	}
}

void SpaceDome::Update(float elapsedTime)
{
	UpdateTransform();
	model[0]->UpdateTransform(model[0]->transform);
}

void SpaceDome::Render(ID3D11DeviceContext* dc, Shader* shader, int flag)
{
	shader->Draw2(dc, model[0].get());

}