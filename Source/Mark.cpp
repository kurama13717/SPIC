#include <imgui.h>
#include "Mark.h"
#include "Bullet.h"
#include "Player.h"
#include "Graphics/LambertShader.h"
#include <functional>


Mark::Mark()
{
	StageManager& stageManager = StageManager::Instance();

	{  
		mark0 = new Model("Data/Model/Mark/mark.mdl");
		position[0].x = 6.0f;
		position[0].y = 15.0f;
		position[0].z = -3.0f;
		scale[0].x = 0.01f;
		scale[0].y = 0.05f;
		scale[0].z = 0.05f;
		angle[0].x = DirectX::XMConvertToRadians(60.0f);
		angle[0].y = DirectX::XMConvertToRadians(180.0f);
		angle[0].z = DirectX::XMConvertToRadians(53.0f);

		Do = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\1ド.wav");
		Re = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\2レ.wav");
		Mi = Audio::Instance().LoadAudioSource(".\\Data\\Sound\\3ミ.wav");

	}

	{
		mark1 = new Model("Data/Model/Mark/mark.mdl");
		position[1].x = -5.5f;
		position[1].y = 21.4f;
		position[1].z = -10.5f;
		scale[1].x = 0.01f;
		scale[1].y = 0.05f;
		scale[1].z = 0.05f;
		angle[1].x = DirectX::XMConvertToRadians(70.0f);
		angle[1].y = DirectX::XMConvertToRadians(180.0f);
		angle[1].z = DirectX::XMConvertToRadians(70.0f);
	}

	{
		mark2 = new Model("Data/Model/Mark/mark.mdl");
		position[2].x = 0.0f;
		position[2].y = 20.0f;
		position[2].z = 5.0f;
		scale[2].x = 0.01f;
		scale[2].y = 0.05f;
		scale[2].z = 0.05f;
		angle[2].x = DirectX::XMConvertToRadians(90.0f);
		angle[2].y = DirectX::XMConvertToRadians(180.0f);
		angle[2].z = DirectX::XMConvertToRadians(90.0f);
	}
	StageManager::Instance().Register(this);

}

Mark::~Mark()
{
	delete mark0;
	delete mark1;
	delete mark2;
}

void Mark::UpdateTransform()
{
	for (int i = 0; i < 10; i++) {
		// スケール行列を作成
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale[i].x, scale[i].y, scale[i].z);
		// 全部サイズが固定だとだめだから変数入れる

		// 回転行列を作成
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle[i].x, angle[i].y, angle[i].z);
		// オイラー角

		// 位置行列を作成
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(position[i].x, position[i].y, position[i].z);

		// 3つの行列を組み合わせ、ワールド行列を作成
		DirectX::XMMATRIX W = S * R * T;
		// ☆　行列の順番を変えてはいけない



		// 計算したワールド行列を取り出す //再変換
		DirectX::XMStoreFloat4x4(&transform[i], W);
	}
}

void Mark::Update(float elapsedTime)
{
	UpdateTransform();
	mark0->UpdateTransform(transform[0]);
	mark1->UpdateTransform(transform[1]);
	mark2->UpdateTransform(transform[2]);
}

void Mark::Render(ID3D11DeviceContext* dc, Shader* shader, int flag)
{

	DirectX::XMFLOAT4 color0{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 color1{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 color2{ 1.0f, 1.0f, 1.0f, 1.0f };
	//// タッチしている壁の番号
	//int selectNo = 1;

	std::function<void(DirectX::XMFLOAT4* c)> callback[] = {
		[&](DirectX::XMFLOAT4* c) {
			shader->Draw(dc, mark0, c); 

		},
		[&](DirectX::XMFLOAT4* c) {
			shader->Draw(dc, mark1, c);

		},
		[&](DirectX::XMFLOAT4* c) {
			shader->Draw(dc, mark2, c);
		}
	};

	color0 = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.7f);
	color1 = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.7f);
	color2 = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.7f);
	

	if (StageManager::Instance().flag0_r)
	{
		scale[0].x = 0.0f;
		scale[0].y = 0.0f;
		scale[0].z = 0.0f;
	}
	if (StageManager::Instance().flag1_r)
	{
		scale[1].x = 0.0f;
		scale[1].y = 0.0f;
		scale[1].z = 0.0f;
	}
	if (StageManager::Instance().flag2_r)
	{
		scale[2].x = 0.0f;
		scale[2].y = 0.0f;
		scale[2].z = 0.0f;
	}

	//auto test = mark;


	callback[0](&color0);
	callback[1](&color1);
	callback[2](&color2);
}

bool Mark::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	flag0 = Collision::IntersectRayVsModel(start, end, mark0, hit); // 0
	flag1 = Collision::IntersectRayVsModel(start, end, mark1, hit); // 1
	flag2 = Collision::IntersectRayVsModel(start, end, mark2, hit); // 2

	if (flag0 == true)
	{
		if (StageManager::Instance().flag0_r)return false;
		StageManager::Instance().flag0_r = flag0;
		StageManager::Instance().hitObject = 2;
		Do->Play(false);
		return true;
	}

	if (flag1 == true)
	{
		if (StageManager::Instance().flag1_r)return false;
		StageManager::Instance().flag1_r = flag1;
		StageManager::Instance().hitObject = 2;
		Re->Play(false);

		return true;
	}

	if (flag2 == true)
	{
		if (StageManager::Instance().flag2_r)return false;
		StageManager::Instance().flag2_r = flag2;
		StageManager::Instance().hitObject = 2;
		Mi->Play(false);

		return true;
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
		if (ImGui::CollapsingHeader("Mark0", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//position
			ImGui::InputFloat3("Position0", &position[0].x);
			//angle
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle[0].x);
			a.y = DirectX::XMConvertToDegrees(angle[0].y);
			a.z = DirectX::XMConvertToDegrees(angle[0].z);
			ImGui::InputFloat3("Angle0", &a.x);
			angle[0].x = DirectX::XMConvertToRadians(a.x);
			angle[0].y = DirectX::XMConvertToRadians(a.y);
			angle[0].z = DirectX::XMConvertToRadians(a.z);
			//scale
			ImGui::InputFloat3("Scale0", &scale[0].x);
		}
		if (ImGui::CollapsingHeader("Mark1", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//position
			ImGui::InputFloat3("Position1", &position[1].x);
			//angle
			DirectX::XMFLOAT3 b;
			b.x = DirectX::XMConvertToDegrees(angle[1].x);
			b.y = DirectX::XMConvertToDegrees(angle[1].y);
			b.z = DirectX::XMConvertToDegrees(angle[1].z);
			ImGui::InputFloat3("Angle1", &b.x);
			angle[1].x = DirectX::XMConvertToRadians(b.x);
			angle[1].y = DirectX::XMConvertToRadians(b.y);
			angle[1].z = DirectX::XMConvertToRadians(b.z);
			//scale
			ImGui::InputFloat3("Scale1", &scale[1].x);
		}
		if (ImGui::CollapsingHeader("Mark2", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//position
			ImGui::InputFloat3("Position2", &position[2].x);
			//angle
			DirectX::XMFLOAT3 c;
			c.x = DirectX::XMConvertToDegrees(angle[2].x);
			c.y = DirectX::XMConvertToDegrees(angle[2].y);
			c.z = DirectX::XMConvertToDegrees(angle[2].z);
			ImGui::InputFloat3("Angle2", &c.x);
			angle[2].x = DirectX::XMConvertToRadians(c.x);
			angle[2].y = DirectX::XMConvertToRadians(c.y);
			angle[2].z = DirectX::XMConvertToRadians(c.z);
			//scale
			ImGui::InputFloat3("Scale2", &scale[2].x);
		}
	}
	ImGui::End();
}