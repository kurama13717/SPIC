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
		position[0].x = -10;
		position[0].y = 10;
		position[0].z = 0;
		scale[0].x = 0.01f;
		scale[0].y = 0.01f;
		scale[0].z = 0.01f;
		angle[0].x = DirectX::XMConvertToRadians(45.0f);
		angle[0].y = DirectX::XMConvertToRadians(180.0f);
		angle[0].z = DirectX::XMConvertToRadians(90.0f);
	}

	{
		mark1 = new Model("Data/Model/Mark/mark.mdl");
		position[1].x = 10;
		position[1].y = 5;
		position[1].z = 20;
		scale[1].x = 0.01f;
		scale[1].y = 0.01f;
		scale[1].z = 0.01f;
		angle[1].x = DirectX::XMConvertToRadians(45.0f);
		angle[1].y = DirectX::XMConvertToRadians(180.0f);
		angle[1].z = DirectX::XMConvertToRadians(90.0f);
	}

	{
		mark2 = new Model("Data/Model/Mark/mark.mdl");
		position[2].x = -20;
		position[2].y = 10;
		position[2].z = -5;
		scale[2].x = 0.01f;
		scale[2].y = 0.01f;
		scale[2].z = 0.01f;
		angle[2].x = DirectX::XMConvertToRadians(45.0f);
		angle[2].y = DirectX::XMConvertToRadians(180.0f);
		angle[2].z = DirectX::XMConvertToRadians(90.0f);
	}
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
		// �X�P�[���s����쐬
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale[i].x, scale[i].y, scale[i].z);
		// �S���T�C�Y���Œ肾�Ƃ��߂�����ϐ������

		// ��]�s����쐬
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle[i].x, angle[i].y, angle[i].z);
		// �I�C���[�p

		// �ʒu�s����쐬
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(position[i].x, position[i].y, position[i].z);

		// 3�̍s���g�ݍ��킹�A���[���h�s����쐬
		DirectX::XMMATRIX W = S * R * T;
		// ���@�s��̏��Ԃ�ς��Ă͂����Ȃ�



		// �v�Z�������[���h�s������o�� //�ĕϊ�
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

void Mark::Render(ID3D11DeviceContext* dc, Shader* shader, bool flag)
{

	DirectX::XMFLOAT4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

	//// �^�b�`���Ă���ǂ̔ԍ�
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


	//for (int i = 0; i < 6; ++i) {
	//	if (selectNo == i + 1 && sg->ViewMode) {
	//		// �I�����ꂽ���̐F
	//		color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	//	}
	//	else {
	//		// �I������Ă��Ȃ����̐F
	//		color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);

	//	}
	//

	if (flag)
		color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.7f);
	else 	
		color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	//auto test = mark;


	callback[0](&color);
	callback[1](&color);
	callback[2](&color);
}

bool Mark::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	bool flag0 = Collision::IntersectRayVsModel(start, end, mark0, hit); // 0
	bool flag1 = Collision::IntersectRayVsModel(start, end, mark1, hit); // 1
	bool flag2 = Collision::IntersectRayVsModel(start, end, mark2, hit); // 2

	if (flag0 == true || flag1 == true || flag2 == true)
	{
		return true;
	}
	return false;

	//return Collision::IntersectRayVsModel(start, end, flat_Left, hit);
}

void Mark::Destroy()
{
	//Mark.Remove(bullet);
	
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
			ImGui::InputFloat3("Position", &position[0].x);
			//angle
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle[0].x);
			a.y = DirectX::XMConvertToDegrees(angle[0].y);
			a.z = DirectX::XMConvertToDegrees(angle[0].z);
			ImGui::InputFloat3("Angle", &a.x);
			angle[0].x = DirectX::XMConvertToRadians(a.x);
			angle[0].y = DirectX::XMConvertToRadians(a.y);
			angle[0].z = DirectX::XMConvertToRadians(a.z);
			//scale
			ImGui::InputFloat3("Scale", &scale[0].x);
		}
		if (ImGui::CollapsingHeader("Mark1", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//position
			ImGui::InputFloat3("Position", &position[1].x);
			//angle
			DirectX::XMFLOAT3 b;
			b.x = DirectX::XMConvertToDegrees(angle[1].x);
			b.y = DirectX::XMConvertToDegrees(angle[1].y);
			b.z = DirectX::XMConvertToDegrees(angle[1].z);
			ImGui::InputFloat3("Angle", &b.x);
			angle[1].x = DirectX::XMConvertToRadians(b.x);
			angle[1].y = DirectX::XMConvertToRadians(b.y);
			angle[1].z = DirectX::XMConvertToRadians(b.z);
			//scale
			ImGui::InputFloat3("Scale", &scale[1].x);
		}
		if (ImGui::CollapsingHeader("Mark2", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//position
			ImGui::InputFloat3("Position", &position[2].x);
			//angle
			DirectX::XMFLOAT3 c;
			c.x = DirectX::XMConvertToDegrees(angle[2].x);
			c.y = DirectX::XMConvertToDegrees(angle[2].y);
			c.z = DirectX::XMConvertToDegrees(angle[2].z);
			ImGui::InputFloat3("Angle", &c.x);
			angle[2].x = DirectX::XMConvertToRadians(c.x);
			angle[2].y = DirectX::XMConvertToRadians(c.y);
			angle[2].z = DirectX::XMConvertToRadians(c.z);
			//scale
			ImGui::InputFloat3("Scale", &scale[2].x);
		}
	}
	ImGui::End();
}