#include <imgui.h>
#include "Cube.h"
#include "Bullet.h"
#include "Player.h"
#include "StageManager.h"
#include "Graphics/LambertShader.h"
#include <functional>


Cube::Cube()
{
	{  //下面...ステージの床
		flat_Down = new Model("Data/Model/Stage/flatpanel.mdl");
		position[0].x = 0;
		position[0].y = 0;
		position[0].z = 0;
		scale[0].x = 0.2f;
		scale[0].y = 0.1f;
		scale[0].z = 0.2f;
	}

	{	//上面...ステージの天井
		flat_Up = new Model("Data/Model/Stage/flatpanel.mdl");
		position[1].x = 0.0f;
		position[1].y = 40.0f;
		position[1].z = 0.0f;
		scale[1].x = 0.2f;
		scale[1].y = 0.1f;
		scale[1].z = 0.2f;
		angle[1].x = DirectX::XMConvertToRadians(180.0f);
	}

	{	//左面...ステージの左壁
		flat_Left = new Model("Data/Model/Stage/flatpanel.mdl");
		position[2].x = -20.0f;
		position[2].y = 20.0f;
		position[2].z = 0.0f;
		scale[2].x = 0.2f;
		scale[2].y = 0.1f;
		scale[2].z = 0.2f;
		angle[2].z = DirectX::XMConvertToRadians(-90.0f);
	}

	{	//右面...ステージの右壁
		flat_Right = new Model("Data/Model/Stage/flatpanel.mdl");
		position[3].x = 20.0f;
		position[3].y = 20.0f;
		position[3].z = 0.0f;
		scale[3].x = 0.2f;
		scale[3].y = 0.1f;
		scale[3].z = 0.2f;
		angle[3].z = DirectX::XMConvertToRadians(90.0f);
	}

	{	//前面...ステージの右壁
		flat_Forward = new Model("Data/Model/Stage/flatpanel.mdl");
		position[4].x = 0.0f;
		position[4].y = 20.0f;
		position[4].z = 20.0f;
		scale[4].x = 0.2f;
		scale[4].y = 0.1f;
		scale[4].z = 0.2f;
		angle[4].x = DirectX::XMConvertToRadians(-90.0f);
	}

	{	//後面...ステージの後壁
		flat_Back = new Model("Data/Model/Stage/flatpanel.mdl");
		position[5].x = 0.0f;
		position[5].y = 20.0f;
		position[5].z = -20.0f;
		scale[5].x = 0.2f;
		scale[5].y = 0.1f;
		scale[5].z = 0.2f;
		angle[5].x = DirectX::XMConvertToRadians(90.0f);
	}
	StageManager::Instance().Register(this);
}

Cube::~Cube()
{
	delete flat_Down;
	delete flat_Up;
	delete flat_Left;
	delete flat_Right;
	delete flat_Forward;
	delete flat_Back;

	
}

void Cube::UpdateTransform()
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

void Cube::Update(float elapsedTime)
{
	UpdateTransform();
	flat_Down->UpdateTransform(transform[0]);
	flat_Up->UpdateTransform(transform[1]);
	flat_Left->UpdateTransform(transform[2]);
	flat_Right->UpdateTransform(transform[3]);
	flat_Forward->UpdateTransform(transform[4]);
	flat_Back->UpdateTransform(transform[5]);
}

void Cube::Render(ID3D11DeviceContext* dc, Shader* shader, int flag)
{

	//DirectX::XMFLOAT4 normal{ 1.0f, 1.0f, 1.0f, 1.0f };
	//DirectX::XMFLOAT4 skelton{ 1.0f, 1.0f, 1.0f, 0.5f };
	//DirectX::XMFLOAT4 red	{ 1.0f, 0.0f, 0.0f, 0.5f };
	//DirectX::XMFLOAT4 Cyan	{ 0.0f, 1.0f, 1.0f, 0.5f };
	//DirectX::XMFLOAT4 green	{ 0.0f, 1.0f, 0.0f, 0.5f };
	//DirectX::XMFLOAT4 purple{ 1.0f, 0.0f, 1.0f, 0.5f };

	////// タッチしている壁の番号
	////int selectNo = 1;

	//std::function<void(DirectX::XMFLOAT4* c)> callback[] = {
	//	[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Down, c); } ,
	//	[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Up, c); } ,
	//	[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Left, c); } ,
	//	[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Right, c); } ,
	//	[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Forward, c); } ,
	//	[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Back, c); }
	//};
	//

	////for (int i = 0; i < 6; ++i) {
	////	if (selectNo == i + 1 && sg->ViewMode) {
	////		// 選択された時の色
	////		color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	////	}
	////	else {
	////		// 選択されていない時の色
	////		color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);

	////	}
	////

	//	//if(flag)color =  DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);


	//	//else 	color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	//	//callback[0](&color);
	//	//callback[1](&color);
	//	//callback[2](&color);
	//	//callback[3](&color);
	//	//callback[4](&color);
	//	//callback[5](&color);
	//	
	//callback[0](&normal);
	//callback[1](&normal);
	//callback[2](&red);
	//callback[3](&Cyan);
	//callback[4](&green);
	//callback[5](&purple);
}

void Cube::Render(ID3D11DeviceContext* dc, Shader* shader, int mode, int surface)
{

	DirectX::XMFLOAT4 normal	{ 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 skelton	{ 1.0f, 1.0f, 1.0f, 0.4f };
	DirectX::XMFLOAT4 red		{ 1.0f, 0.0f, 0.0f, 1.0f };
	DirectX::XMFLOAT4 cyan		{ 0.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 green		{ 0.0f, 1.0f, 0.0f, 1.0f };
	DirectX::XMFLOAT4 purple	{ 1.0f, 0.0f, 1.0f, 1.0f };

	DirectX::XMFLOAT4 red_s		{ 1.0f, 0.0f, 0.0f, 1.0f };
	DirectX::XMFLOAT4 cyan_s	{ 0.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT4 green_s	{ 0.0f, 1.0f, 0.0f, 1.0f };
	DirectX::XMFLOAT4 purple_s	{ 1.0f, 0.0f, 1.0f, 1.0f };

	std::function<void(DirectX::XMFLOAT4* c)> callback[] = {
		[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Down, c); } ,
		[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Up, c); } ,
		[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Left, c); } ,
		[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Right, c); } ,
		[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Forward, c); } ,
		[&](DirectX::XMFLOAT4* c) {shader->Draw(dc, flat_Back, c); }
	};

	switch (mode)// カメラモードによって分岐
	{
	case 0:	// Viewモード
		switch (surface)	// 選択面によって分岐
		{
		case 0:	// 紫
			callback[2](&red);
			callback[3](&cyan);
			callback[4](&green);
			break;
		case 1:	// シアン
			callback[2](&red);
			callback[4](&green);
			callback[5](&purple);
			break;
		case 2:	// 緑
			callback[2](&red);
			callback[3](&cyan);
			callback[5](&purple);
			break;
		case 3:	// 赤
			callback[3](&cyan);
			callback[4](&green);
			callback[5](&purple);
			break;
		}
		break;
	case 1:	// FPSモード
		callback[2](&red);
		callback[3](&cyan);
		callback[4](&green);
		callback[5](&purple);
		break;
	case 2:	// Spectatorモード
		callback[2](&red_s);
		callback[3](&cyan_s);
		callback[4](&green_s);
		callback[5](&purple_s);
		break;
	}

	callback[0](&normal);
	callback[1](&normal);

	//for (int i = 0; i < 6; ++i) {
	//	if (selectNo == i + 1 && sg->ViewMode) {
	//		// 選択された時の色
	//		color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	//	}
	//	else {
	//		// 選択されていない時の色
	//		color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);

	//	}
	//

		//if(flag)color =  DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);


		//else 	color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		//callback[0](&color);
		//callback[1](&color);
		//callback[2](&color);
		//callback[3](&color);
		//callback[4](&color);
		//callback[5](&color);


	//callback[2](&skelton);
	//callback[3](&skelton);
	//callback[4](&skelton);
	//callback[5](&skelton);
}


bool Cube::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	bool fd_flag = Collision::IntersectRayVsModel(start, end, flat_Down, hit); // 1
	bool fu_flag = Collision::IntersectRayVsModel(start, end, flat_Up, hit);	// 2
	bool fl_flag = Collision::IntersectRayVsModel(start, end, flat_Left, hit);	// 3
	bool fr_flag = Collision::IntersectRayVsModel(start, end, flat_Right, hit);		// 4
	bool ff_flag = Collision::IntersectRayVsModel(start, end, flat_Forward, hit);	//5
	bool fb_flag = Collision::IntersectRayVsModel(start, end, flat_Back, hit);	// 6

	if (fd_flag == true || fu_flag == true || fl_flag == true || fr_flag == true || ff_flag == true || fb_flag == true)
	{
		StageManager::Instance().hitObject = 1;
		return true;
	}
	return false;

	//return Collision::IntersectRayVsModel(start, end, flat_Left, hit);
}

void Cube::DrawDebugGUI()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Flat", nullptr, ImGuiWindowFlags_None))
	{
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//position
			ImGui::InputFloat3("Position", &position[1].x);
			//angle
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle[1].x);
			a.y = DirectX::XMConvertToDegrees(angle[1].y);
			a.z = DirectX::XMConvertToDegrees(angle[1].z);
			ImGui::InputFloat3("Angle", &a.x);
			angle[1].x = DirectX::XMConvertToRadians(a.x);
			angle[1].y = DirectX::XMConvertToRadians(a.y);
			angle[1].z = DirectX::XMConvertToRadians(a.z);
			//scale
			ImGui::InputFloat3("Scale", &scale[1].x);
		}

	}
	ImGui::End();
}