#include "Space.h"


SpaceDome::SpaceDome()
{
	//��
	model.push_back(std::make_unique<Model>("Data/Model/�F��/universe.mdl"));
	model[0]->position = { 0.0f,0.0f,0.0f };
	model[0]->scale = { 5,5,5 };



}

void SpaceDome::UpdateTransform()
{
	for (auto& models : model) {
		// �X�P�[���s����쐬
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(models->scale.x, models->scale.y, models->scale.z);
		// �S���T�C�Y���Œ肾�Ƃ��߂�����ϐ������

		// ��]�s����쐬
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(models->angle.x, models->angle.y, models->angle.z);
		// �I�C���[�p

		// �ʒu�s����쐬
		DirectX::CXMMATRIX T = DirectX::XMMatrixTranslation(models->position.x, models->position.y, models->position.z);

		// 3�̍s���g�ݍ��킹�A���[���h�s����쐬
		DirectX::XMMATRIX W = S * R * T;
		// ���@�s��̏��Ԃ�ς��Ă͂����Ȃ�

		// �v�Z�������[���h�s������o�� //�ĕϊ�
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