#include <imgui.h>
#include "Mark.h"
#include "Bullet.h"
#include "Player.h"
#include "Graphics/LambertShader.h"
#include "CameraController.h"
#include <functional>


Mark::Mark(int StageNum)
{
	StageManager& stageManager = StageManager::Instance();

	if (StageNum == 1)
	{
		for (int i = 0; i < 2; i++)
		{
			model.push_back(std::make_unique<Model>("Data/Model/Mark/MarkTex.mdl"));
			model[i]->scale = { 0.02f,0.02f,0.02f };
			model[i]->count = i;
		}
		model[0]->position = { 5.0f,10.0f,0.0f };
		model[0]->name = "Mark0";
		model[1]->position = { -1.0f,8.0f,0.0f };
		model[1]->name = "Mark1";
	

	}



	if (StageNum == 2)
	{
		{
			model.push_back(std::make_unique<Model>("Data/Model/Mark/MarkTex.mdl"));

			model[0]->position.x = 5.0f;
			model[0]->position.y = 19.5f;
			model[0]->position.z = 5.0f;
			model[0]->scale.x = 0.02f;
			model[0]->scale.y = 0.02f;
			model[0]->scale.z = 0.02f;
			model[0]->angle.x = DirectX::XMConvertToRadians(90.0f);
			model[0]->angle.y = DirectX::XMConvertToRadians(180.0f);
			model[0]->angle.z = DirectX::XMConvertToRadians(90.0f);
			model[0]->count = 2;
			model[0]->name = "Mark0";

		}

		{
			//mark1 = new Model("Data/Model/Mark/mark.mdl");
			model.push_back(std::make_unique<Model>("Data/Model/Mark/MarkTex.mdl"));

			model[1]->position.x = -5.5f;
			model[1]->position.y = 22.4f;
			model[1]->position.z = -10.5f;
			model[1]->scale.x = 0.02f;
			model[1]->scale.y = 0.02f;
			model[1]->scale.z = 0.02f;
			model[1]->angle.x = DirectX::XMConvertToRadians(110.0f);
			model[1]->angle.y = DirectX::XMConvertToRadians(25.0f);
			model[1]->angle.z = DirectX::XMConvertToRadians(70.0f);
			model[1]->count = 1;
			model[1]->name = "Mark1";



		}

		{
			model.push_back(std::make_unique<Model>("Data/Model/Mark/MarkTex.mdl"));


			model[2]->position.x = 6.5f;
			model[2]->position.y = 15.0f;
			model[2]->position.z = -3.0f;
			model[2]->scale.x = 0.02f;
			model[2]->scale.y = 0.02f;
			model[2]->scale.z = 0.02f;
			model[2]->angle.x = DirectX::XMConvertToRadians(60.0f);
			model[2]->angle.y = DirectX::XMConvertToRadians(180.0f);
			model[2]->angle.z = DirectX::XMConvertToRadians(53.0f);
			model[2]->count = 0;
			model[2]->name = "Mark2";



		}
	}


	if (StageNum == 3)
	{
		for (int i = 0; i < 6; i++)
		{
			model.push_back(std::make_unique<Model>("Data/Model/Mark/MarkTex.mdl"));
			model[i]->scale = { 0.02f,0.02f,0.02f };
			model[i]->count = i;
		}
		model[0]->position = { 0.0f,29.5f,-15.0f };
		model[0]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(-20.0f) };
		model[0]->name = "Mark0";

		model[1]->position = { 0.0f,36.5f,-9.5f };
		model[1]->angle = { DirectX::XMConvertToRadians(-40.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(90.0f) };
		model[1]->name = "Mark1";

		model[2]->position = { 18.0f,33.0f,2.5f };
		model[2]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(0.0f) };
		model[2]->name = "Mark2";

		model[3]->position = { -2.0f,30.0f,15.0f };
		model[3]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(40.0f),DirectX::XMConvertToRadians(-40.0f) };
		model[3]->name = "Mark3";

		model[4]->position = { -2.5f,5.0f,13.5f };
		model[4]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(48.0f) };
		model[4]->name = "Mark4";

		model[5]->position = { -3.5f,5.0f,-13.0f };
		model[5]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(0.0f) };
		model[5]->name = "Mark5";


	}



	if (StageNum == 4)
	{

		for (int i = 0; i < 5; i++)
		{
			model.push_back(std::make_unique<Model>("Data/Model/Mark/MarkTex.mdl"));
			model[i]->scale = { 0.02f,0.02f,0.02f };
			model[i]->count = i;
			StageManager::Instance().flag_r[i] = false;

		}
		model[0]->position = { 0.0f,24.0f,14.0f };
		model[0]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(0.0f) };
		model[0]->name = "Mark0";

		model[1]->position = { -17.0f,28.0f,0.0f };
		model[1]->angle = { DirectX::XMConvertToRadians(-40.0f),DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(-45.0f) };

		model[1]->name = "Mark1";

		model[2]->position = { -4.0f,7.5f,6.0f };
		model[2]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(-90.0f),DirectX::XMConvertToRadians(-45.0f) };
		model[2]->name = "Mark2";

		model[3]->position = { 9.0f,13.0f,-15.0f };
		model[3]->angle = { DirectX::XMConvertToRadians(60.0f),DirectX::XMConvertToRadians(-60.0f),DirectX::XMConvertToRadians(45.0f) };
		model[3]->name = "Mark3";

		model[4]->position = { 13.5f,32.5f,0.0f };
		model[4]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(-60.0f) };
		model[4]->name = "Mark4";




		StageManager::Instance().Register(new MarkSplit());

	}


	Do = Audio::Instance().LoadAudioSource("Data//Sound//1ド.wav");
	Re = Audio::Instance().LoadAudioSource("Data//Sound//2レ.wav");
	Mi = Audio::Instance().LoadAudioSource("Data//Sound//3ミ.wav");
	Fa = Audio::Instance().LoadAudioSource("Data//Sound//4ファ.wav");
	So = Audio::Instance().LoadAudioSource("Data//Sound//5ソ.wav");
	Ra = Audio::Instance().LoadAudioSource("Data//Sound//6ラ.wav");

	StageManager::Instance().Register(this);
	StageManager::Instance().SetMarkCount(model.size()); //ここでMarkの表示数を記録してその数分ヒットしていたらクリア...StageManager::ClearFlag()
	StageManager::Instance().SetStageClear(false);
	BulletManager::Instance().SetPrediction(false);

	for (int i = 0; i < model.size(); i++)
	{
		StageManager::Instance().flag_r[i] = false;
		BulletManager::Instance().SetPosition(DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), i);
	}

}

Mark::~Mark()
{

}



void Mark::UpdateTransform()
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

void Mark::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	UpdateTransform();

	for (auto& models : model) {
		models->UpdateTransform(models->transform);
	}




	if (StageManager::Instance().GetRetry())
	{
		for (int i = 0; i < model.size(); i++) {
			model[i]->scale.x = 0.02f;
			model[i]->scale.y = 0.02f;
			model[i]->scale.z = 0.02f;
			StageManager::Instance().flag_r[i] = false;
		}
		StageManager::Instance().SetRetry(false);
	}

	if (StageManager::Instance().GetRetryMsp())
	{
		int i = 0;
	}


}


void Mark::Render(ID3D11DeviceContext* dc, Shader* shader, int flag)
{

	DirectX::XMFLOAT4 color0{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 color1{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 color2{ 1.0f, 1.0f, 1.0f, 1.0f };
	//// タッチしている壁の番号
	//int selectNo = 1;



	for (auto& models : model) {
		shader->Draw2(dc, models.get());
		if (StageManager::Instance().Getflag_r(models->count))
		{
			models->scale.x = 0.0f;
			models->scale.y = 0.0f;
			models->scale.z = 0.0f;



		}
	}
}

bool Mark::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{

	for (auto& models : model) {
		flag[models->count] = Collision::IntersectRayVsModel(start, end, models.get(), hit);


		if (flag[models->count] == true)
		{
			if (StageManager::Instance().flag0_r /*|| CameraController::Instance().GetCameraMode() == 2*/)return false;
			StageManager::Instance().hitObject = 2;
			if (BulletManager::Instance().GetisMaterial()) {
				StageManager::Instance().flag_r[models->count] = true;





				if (models->count == 0)Do->Play(false);
				if (models->count == 1)Re->Play(false);
				if (models->count == 2)Mi->Play(false);
				if (models->count == 3)Fa->Play(false);
				if (models->count == 4)So->Play(false);
				if (models->count == 5)Ra->Play(false);
			}
			return true;
		}
	}
	return false;
}



void Mark::Destroy()
{
	StageManager::Instance().Remove(stage);
}

void Mark::DrawDebugGUI()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Mark", nullptr, ImGuiWindowFlags_None))
	{

		for (int i = 0; i < model.size(); i++)
		{
			if (ImGui::CollapsingHeader(model[i]->name, ImGuiTreeNodeFlags_DefaultOpen))
			{
				//position
				ImGui::InputFloat3("Position", &model[i]->position.x);
				//angle
				DirectX::XMFLOAT3 a;
				a.x = DirectX::XMConvertToDegrees(model[i]->angle.x);
				a.y = DirectX::XMConvertToDegrees(model[i]->angle.y);
				a.z = DirectX::XMConvertToDegrees(model[i]->angle.z);
				ImGui::InputFloat3("Angle", &a.x);
				model[i]->angle.x = DirectX::XMConvertToRadians(a.x);
				model[i]->angle.y = DirectX::XMConvertToRadians(a.y);
				model[i]->angle.z = DirectX::XMConvertToRadians(a.z);
				//scale
				ImGui::InputFloat3("Scale", &model[i]->scale.x);

			}
		}
	}


	ImGui::End();
}

MarkSplit::MarkSplit()
{
	StageManager& stageManager = StageManager::Instance();


	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit1.mdl")); //0
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit2.mdl")); //1
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit3.mdl")); //2
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit4.mdl")); //3
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit5.mdl")); //4
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit6.mdl")); //5
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit7.mdl")); //6
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit8.mdl")); //7
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit9.mdl")); //8
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit10.mdl")); //9
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit11.mdl")); //10
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit12.mdl")); //11
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit13.mdl")); //12
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit14.mdl")); //13
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit15.mdl")); //14
	modelsplit.push_back(std::make_unique<Model>("Data/Model/Marksp/最新mdl/MarkSplit16.mdl")); //15

	//当たったら分裂するようのモデル
	modelcrack.push_back(std::make_unique<Model>("Data/Model/Mark/MarktexCrack.mdl"));
	modelcrack[0]->position = { 12.0f,26.5f,-4.0f };
	modelcrack[0]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(-60.0f) };
	modelcrack[0]->scale = { 0.02f,0.02f,0.02f };
	modelcrack[0]->count = 0;

	//for (int i = 0; i < 16; i++)
	//{
	//	modelsplit[i]->scale = { 0.02f,0.02f,0.02f };
	//	//modelsplit[i]->position = { 10,10,10 };
	//	//modelsplit[i]->angle = { DirectX::XMConvertToRadians(45),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(45.0f) };
	//}

}


void MarkSplit::UpdateTransform()
{
	for (auto& modelsplits : modelsplit) {
		// スケール行列を作成
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(modelsplits->scale.x, modelsplits->scale.y, modelsplits->scale.z);
		// 全部サイズが固定だとだめだから変数入れる

		// 回転行列を作成
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(modelsplits->angle.x, modelsplits->angle.y, modelsplits->angle.z);
		// オイラー角

		// 位置行列を作成
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(modelsplits->position.x, modelsplits->position.y, modelsplits->position.z);

		// 3つの行列を組み合わせ、ワールド行列を作成
		DirectX::XMMATRIX W = S * R * T;
		// ☆　行列の順番を変えてはいけない

		// 計算したワールド行列を取り出す //再変換
		DirectX::XMStoreFloat4x4(&modelsplits->transform, W);
	}

	for (auto& modelcracks : modelcrack) {
		// スケール行列を作成
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(modelcracks->scale.x, modelcracks->scale.y, modelcracks->scale.z);
		// 全部サイズが固定だとだめだから変数入れる

		// 回転行列を作成
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(modelcracks->angle.x, modelcracks->angle.y, modelcracks->angle.z);
		// オイラー角

		// 位置行列を作成
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(modelcracks->position.x, modelcracks->position.y, modelcracks->position.z);

		// 3つの行列を組み合わせ、ワールド行列を作成
		DirectX::XMMATRIX W = S * R * T;
		// ☆　行列の順番を変えてはいけない

		// 計算したワールド行列を取り出す //再変換
		DirectX::XMStoreFloat4x4(&modelcracks->transform, W);
	}


}


void MarkSplit::Update(float elapsedTime)
{
	UpdateTransform();
	for (auto& modelsplits : modelsplit)
	{
		modelsplits->UpdateTransform(modelsplits->transform);
		modelsplits->position.x += modelsplits->impulse.x;
		modelsplits->position.y += modelsplits->impulse.y;
		modelsplits->position.z += modelsplits->impulse.z;



	}
	if (scaleFlag)
	{
		if (fram < 0.0f)
		{
			for (int i = 0; i < 16; i++)
			{
				modelsplit[i]->scale = { 0.0f,0.0f,0.0f };
				modelsplit[i]->impulse.x = 0.0f;
				modelsplit[i]->impulse.y = 0.0f;
				modelsplit[i]->impulse.z = 0.0f;
			}

			for (auto& modelcracks : modelcrack)
			{
				modelcracks->testFlag = false;

			}
			scaleFlag = false;
		}

		fram--;
	}

	else if (!scaleFlag) fram = 300.0f;


	for (auto& modelcracks : modelcrack)
	{
		modelcracks->UpdateTransform(modelcracks->transform);
		if (StageManager::Instance().GetRetryMsp() && !modelcracks->testFlag)
		{
			modelcracks->scale = { 0.02f,0.02f,0.02f };
			StageManager::Instance().SetRetryMsp(false);
		}

	}

	

	//DrawDebugGUI();

}


bool MarkSplit::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	

	for (auto& modelcracks : modelcrack)
	{
		bool flag = Collision::IntersectRayVsModel(start, end, modelcracks.get(), hit);

		if (flag == true && BulletManager::Instance().GetisMaterial())
		{
			modelcracks->testFlag = flag;
			StageManager::Instance().hitObject = 3;


			for (int i = 0; i < 16; i++)
			{
				modelsplit[i]->position = { modelcracks->position };
				modelsplit[i]->angle = { modelcracks->angle };
				modelsplit[i]->scale = { 0.02f,0.02f,0.02f };


				float vel = (rand() % 100 - 50) * 0.001f;


				modelsplit[i]->impulse.x = vel;

				vel = (rand() % 100 - 50) * 0.001f;

				modelsplit[i]->impulse.y = vel;

				vel = (rand() % 100 - 50) * 0.001f;

				modelsplit[i]->impulse.z = vel;





			}

			scaleFlag = true;

			return true;
		}


	}
	return false;
}


void MarkSplit::DrawDebugGUI()
{
	//ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
	//if (ImGui::Begin("MarkCrack", nullptr, ImGuiWindowFlags_None))
	//{

	//	for (int i = 0; i < modelcrack.size(); i++)
	//	{
	//		if (ImGui::CollapsingHeader(modelcrack[i]->name, ImGuiTreeNodeFlags_DefaultOpen))
	//		{
	//			//position
	//			ImGui::InputFloat3("spPosition", &modelcrack[i]->position.x);
	//			//angle
	//			DirectX::XMFLOAT3 a;
	//			a.x = DirectX::XMConvertToDegrees(modelcrack[i]->angle.x);
	//			a.y = DirectX::XMConvertToDegrees(modelcrack[i]->angle.y);
	//			a.z = DirectX::XMConvertToDegrees(modelcrack[i]->angle.z);
	//			ImGui::InputFloat3("spAngle", &a.x);
	//			modelcrack[i]->angle.x = DirectX::XMConvertToRadians(a.x);
	//			modelcrack[i]->angle.y = DirectX::XMConvertToRadians(a.y);
	//			modelcrack[i]->angle.z = DirectX::XMConvertToRadians(a.z);
	//			//scale
	//			ImGui::InputFloat3("spScale", &modelcrack[i]->scale.x);

	//		}
	//	}
	//}


	//ImGui::End();
}


void MarkSplit::Render(ID3D11DeviceContext* dc, Shader* shader, int flag)
{
	for (auto& modelsplits : modelsplit)
	{
		shader->Draw2(dc, modelsplits.get());
	}

	for (auto& modelcracks : modelcrack)
	{
		shader->Draw2(dc, modelcracks.get());
		if (modelcracks->testFlag)
		{
			modelcracks->scale = { 0.0f,0.0f,0.0f };
		}
	}

}
