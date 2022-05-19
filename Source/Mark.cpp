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
		{
			model.push_back(std::make_unique<Model>("Data/Model/Mark/MarkTex.mdl"));

			//model[0].get()->GetNodes().data()->translate.x = 6.0f;
			//model[0].get()->GetNodes().data()->translate.y = 15.0f;
			//model[0].get()->GetNodes().data()->translate.z = -3.0f;
			//model[0].get()->GetNodes().data()->scale.x = 0.01f;
			//model[0].get()->GetNodes().data()->scale.y = 0.05f;
			//model[0].get()->GetNodes().data()->scale.z = 0.05f;
			//model[0].get()->GetNodes().data()->rotate.x = DirectX::XMConvertToRadians(60.0f);
			//model[0].get()->GetNodes().data()->rotate.y = DirectX::XMConvertToRadians(180.0f);
			//model[0].get()->GetNodes().data()->rotate.z = DirectX::XMConvertToRadians(53.0f);

			


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

			//position.x = -5.5f;
			//position.y = 21.4f;
			//position.z = -10.5f;
			//scale.x = 0.01f;
			//scale.y = 0.05f;
			//scale.z = 0.05f;
			//angle.x = DirectX::XMConvertToRadians(70.0f);
			//angle.y = DirectX::XMConvertToRadians(180.0f);
			//angle.z = DirectX::XMConvertToRadians(70.0f);

			//UpdateTransform();
			//model[1].get()->UpdateTransform(transform);

		}

		{
			//mark2 = new Model("Data/Model/Mark/mark.mdl");
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


	if (StageNum == 2)
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

		model[4]->position = { -2.5f,5.0f,13.0f };
		model[4]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(48.0f) };
		model[4]->name = "Mark4";

		model[5]->position = { -3.5f,5.0f,-13.0f };
		model[5]->angle = { DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(0.0f) };
		model[5]->name = "Mark5";
		

	}

	//MusicalScales.push_back(std::make_unique<AudioSource>(".\\Data\\Sound\\2レ.wav"));
	//MusicalScales.push_back(std::make_unique<AudioSource>(".\\Data\\Sound\\1ド.wav"));
	//MusicalScales.push_back(std::make_unique<AudioSource>(".\\Data\\Sound\\3ミ.wav"));
	//MusicalScales.push_back(std::make_unique<AudioSource>(".\\Data\\Sound\\4ファ.wav"));
	//MusicalScales.push_back(std::make_unique<AudioSource>(".\\Data\\Sound\\5ソ.wav"));
	//MusicalScales.push_back(std::make_unique<AudioSource>(".\\Data\\Sound\\6ラ.wav"));


	Do = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\1ド.wav");
	Re = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\2レ.wav");
	Mi = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\3ミ.wav");
	Fa = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\4ファ.wav");
	So = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\5ソ.wav");
	Ra = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\6ラ.wav");

		StageManager::Instance().Register(this);
		StageManager::Instance().SetMarkCount(model.size()); //ここでMarkの表示数を記録してその数分ヒットしていたらクリア...StageManager::ClearFlag()
	

}

Mark::~Mark()
{
	
}



void Mark::UpdateTransform()
{
	for (auto& models : model) {
		// スケール行列を作成
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(models->scale.x,models->scale.y,models->scale.z);
		// 全部サイズが固定だとだめだから変数入れる

		// 回転行列を作成
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(models->angle.x,models->angle.y,models->angle.z);
		// オイラー角

		// 位置行列を作成
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(models->position.x,models->position.y,models->position.z);

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


}


void Mark::Render(ID3D11DeviceContext* dc, Shader* shader, int flag)
{

	DirectX::XMFLOAT4 color0{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 color1{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 color2{ 1.0f, 1.0f, 1.0f, 1.0f };
	//// タッチしている壁の番号
	//int selectNo = 1;

	/*std::function<void(DirectX::XMFLOAT4* c)> callback[] = {
		[&](DirectX::XMFLOAT4* c) {
			shader->Draw(dc, model.begin()->get(), c); 

		},
		[&](DirectX::XMFLOAT4* c) {
			shader->Draw(dc, mark1, c);

		},
		[&](DirectX::XMFLOAT4* c) {
			shader->Draw(dc, mark2, c);
		}
	};*/

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
	//flag0 = Collision::IntersectRayVsModel(start, end, mark0, hit); // 0
	//flag1 = Collision::IntersectRayVsModel(start, end, mark1, hit); // 1
	//flag2 = Collision::IntersectRayVsModel(start, end, mark2, hit); // 2

	//flag0 = Collision::IntersectRayVsModel(start, end, model[0].get(), hit); // 0
	//flag1 = Collision::IntersectRayVsModel(start, end, model[1].get(), hit); // 1
	//flag2 = Collision::IntersectRayVsModel(start, end, model[2].get(), hit); // 2

	for (auto& models : model) {
		flag[models->count] = Collision::IntersectRayVsModel(start, end, models.get(), hit);

		


		if (flag[models->count] == true)
		{
			if (StageManager::Instance().flag0_r || CameraController::Instance().GetCameraMode() == 2)return false;
			StageManager::Instance().hitObject = 2;
			if (BulletManager::Instance().GetisMaterial()) {
				StageManager::Instance().flag_r[models->count] = true;
				if(models->count == 0)Do->Play(false);
				if(models->count == 1)Re->Play(false);
				if(models->count == 2)Mi->Play(false);
				if(models->count == 3)Fa->Play(false);
				if(models->count == 4)So->Play(false);
				if(models->count == 5)Ra->Play(false);
			}

			return true;
		}

		//if (flag[models->count] == true)
		//{
		//	if (StageManager::Instance().flag1_r)return false;
		//	StageManager::Instance().hitObject = 2;
		//	if (BulletManager::Instance().GetisMaterial()) {
		//		//StageManager::Instance().Setflag1_r(true);
		//		StageManager::Instance().flag_r[models->count] = true;

		//		Re->Play(false);
		//	}
		//	return true;
		//}

		//if (flag2 == true)
		//{
		//	if (StageManager::Instance().flag2_r)return false;
		//	StageManager::Instance().hitObject = 2;
		//	if (BulletManager::Instance().GetisMaterial()) {
		//		StageManager::Instance().Setflag2_r(true);
		//		Mi->Play(false);

		//	}
		//	return true;
		//}

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