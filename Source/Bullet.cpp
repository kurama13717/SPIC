//���ρ@
//Inner Product   Product(��)Inner(������)
//Dot Product 
//Scalar   Scalar(�X�J���[)

//�O��
//Outer Product
//Cross Product
//Vector Product

#include"Bullet.h"
#include"BulletManager.h"
#include "StageManager.h"
#include"Graphics/Graphics.h"
#include <functional>


//�R���X�g���N�^
Bullet::Bullet()
{
    model = new Model("Data/model/Sword/Sword.mdl");

    //�\���T�C�Y�𒲐�
    scale.x = scale.y = scale.z = 3.0f;

	//manager->Register(this);
    
}

//�f�o�b�O�v���~�e�B�u�`��
void Bullet::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//�Փ˔���p�̃f�o�b�O����`��
	debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}



////void Bullet::UpdateVelocity(float elapsedTime)
//{
//	//�����ړ��X�V����
//	UpdateHorizontalMove(elapsedTime);
//}

/*void Bullet::UpdateHorizontalMove(float elapsedTime)
{
    //position.x += velocity.x * elapsedTime;
    //position.z += velocity.z * elapsedTime

    //�������͗ʌv�Z
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
            //�t�x�N�g���Ɩ@���x�N�g���̓���
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(DirectX::XMVectorNegate(Vec), Normal);

            // �␳�ʒu�̌v�Z
            //�@���x�N�g��*����+���C�̏I�[//R�x�N�g�����߂�
            DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiplyAdd(Normal, Dot, End);
            DirectX::XMFLOAT3 collectPosition;
            DirectX::XMStoreFloat3(&collectPosition, CollectPosition);
            // �ǂ�������փ��C�L���X�g
            HitResult hit2;
            if (!StageManager::Instance().RayCast(hit.position, collectPosition, hit2))
            {
                // �ǂ�������ŕǂɓ�����Ȃ�������␳�ʒu�Ɉړ�
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

	//�O�x�N�g�����Z�o z
	Front = DirectX::XMLoadFloat3(&direction);
	Front = DirectX::XMVector3Normalize(Front);

	//���̏�x�N�g�����Z�o  y
	Up = DirectX::XMVectorSet(0.001f, 1, 0, 0);
	//�u�����x�N�g���ŊO�ς���ƃ[���x�N�g���ɂȂ�v ���ۂ�h������0.001f
	Up = DirectX::XMVector3Normalize(Up);

	//�E�x�N�g�����Z�o x
	Right = DirectX::XMVector3Cross(Up, Front);
	Right = DirectX::XMVector3Normalize(Right);

	//��x�N�g�����Z�o y
	Up = DirectX::XMVector3Cross(Front, Right);


	DirectX::XMFLOAT3 right, up, front;
	DirectX::XMStoreFloat3(&right, Right);
	DirectX::XMStoreFloat3(&up, Up);
	DirectX::XMStoreFloat3(&front, Front);

	//�Ƃ肠�����A���ŉ�]�͖��������s����쐬����
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

	//���˕���
	this->direction = front;
}




//�j��
void Bullet::Destroy()
{
	manager->Remove(this);
}*/

void Bullet::Update(float elapsedTime)
{
	//�ړ�
	//float speed = this->speed * elapsedTime;
	//position.x += direction.x * speed;
	//position.y += direction.y * speed;
	//position.z += direction.z * speed;
	BulletRays(elapsedTime);

	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();
	//���f���s����X�V
	model->UpdateTransform(transform);



	

}


void Bullet::UpdateTransform()
{
		// �X�P�[���s����쐬
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
		// �S���T�C�Y���Œ肾�Ƃ��߂�����ϐ������

		// ��]�s����쐬
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(direction.x, direction.y, direction.z);
		// �I�C���[�p

		// �ʒu�s����쐬
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

		// 3�̍s���g�ݍ��킹�A���[���h�s����쐬
		DirectX::XMMATRIX W = S * R * T;
		// ���@�s��̏��Ԃ�ς��Ă͂����Ȃ�

		// �v�Z�������[���h�s������o�� //�ĕϊ�
		DirectX::XMStoreFloat4x4(&transform, W);
}


void Bullet::Render(ID3D11DeviceContext* dc, Shader* shader)
{

	shader->Draw(dc, model,c);
}

//����
void Bullet::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
	this->direction = direction;
	this->position = position;
}


bool Bullet::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	return Collision::IntersectRayVsModel(start, end, model, hit);
}


//�����蔻��
void Bullet::BulletRays(float elapsedTime)
{
	//�������͗ʌv�Z
	float velocityLengthXZ = sqrtf(direction.x * direction.x + direction.z * direction.z);
	if (velocityLengthXZ > 0.0f)
	{
		float mx = direction.x * elapsedTime * 3.0f;
		float my = direction.y * elapsedTime * 3.0f;
		float mz = direction.z * elapsedTime * 3.0f;

		DirectX::XMFLOAT3 start = { position.x, position.y, position.z };
		DirectX::XMFLOAT3 end = { position.x + mx , position.y + my, position.z + mz };

		HitResult hit;
		if (StageManager::Instance().RayCast(start, end, hit))
		{
			DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
			DirectX::XMVECTOR End = DirectX::XMLoadFloat3(&end);
			DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);

			DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&hit.normal);
			//�t�x�N�g���Ɩ@���x�N�g���̓���
			DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(DirectX::XMVectorNegate(Vec), Normal);

			// �␳�ʒu�̌v�Z
			//�@���x�N�g��*����+���C�̏I�[//R�x�N�g�����߂�
			DirectX::XMVECTOR CollectPosition = DirectX::XMVectorMultiplyAdd(Normal, Dot, End);
			DirectX::XMFLOAT3 collectPosition;
			DirectX::XMStoreFloat3(&collectPosition, CollectPosition);
			// �ǂ�������փ��C�L���X�g
			HitResult hit2;
			if (!StageManager::Instance().RayCast(hit.position, collectPosition, hit2))
			{
				// �ǂ�������ŕǂɓ�����Ȃ�������␳�ʒu�Ɉړ�
				position.x = collectPosition.x;
				position.z = collectPosition.z;
			}



			else
			{
				position.x = hit2.position.x;
				position.y = hit2.position.y;
				position.z = hit2.position.z;
			}
		}
		else
		{
			position.x += mx;
			position.y += my;
			position.z += mz;
		}
	}

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
			ImGui::InputFloat3("Position", &this->position.x);
			//angle
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(direction.x);
			a.y = DirectX::XMConvertToDegrees(direction.y);
			a.z = DirectX::XMConvertToDegrees(direction.z);
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