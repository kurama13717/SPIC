#include "Graphics/Graphics.h"
#include<imgui.h>
#include "EffectManager.h"
#include "SceneGame.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "EnemySlime.h"
#include "Input/Input.h"
#include "StageManager.h"
#include "StageMain.h"
#include "Cube.h"
#include "Bullet.h"
#include "BulletManager.h"
// ������
void SceneGame::Initialize()
{
	StageManager& stageManager = StageManager::Instance();
	stageMain = new Cube();
	stageManager.Register(stageMain);

	mark = new Mark();
	stageManager.Register(mark);
	
	BulletManager& bulletManager = BulletManager::Instance();
	bullet = new Bullet();
	bulletManager.Register(bullet);


	player = new Player();
	cameracontroller = new CameraController();
	//shake.SetShake(2.0f, 5.0f, 8.0f);
	//�J���������ݒ�

	camera.SetLookAt(DirectX::XMFLOAT3(0, 10, -10), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1, 0));
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	cameracontroller->SetAngle(DirectX::XMFLOAT3(DirectX::XMConvertToRadians(15), 0.0f, 0.0f));
	cameracontroller->SetFov(120.0f);

	CamMode = Mode::FPSMode;
	
	//�G�l�~�[������
	//EnemyManager& enemyManager = EnemyManager::Instance();
#if 0
	EnemySlime* slime = new EnemySlime();
	slime->SetPosition(DirectX::XMFLOAT3(0, 0, 5));
	enemyManager.Register(slime);
#else
	/*for (int i = 0; i < 4; ++i)
	{
		EnemySlime* slime = new EnemySlime();
		slime->SetPosition(DirectX::XMFLOAT3(i * 2.0f, 0, 5));
		enemyManager.Register(slime);
	}*/
#endif 

	//�Q�[�W�X�v���C�g
	gauge = new Sprite();
}

// �I����
void SceneGame::Finalize()
{
	//�Q�[�W�X�v���C�g�I����
	if (gauge != nullptr)
	{
		delete gauge;
		gauge = nullptr;
	}
	/*EnemyManager& enemyManager = EnemyManager::Instance();
	enemyManager.Clear();*/
	//EnemyManager::Instance().Clear();
	StageManager::Instance().Clear();
	BulletManager::Instance().Clear();
	if (cameracontroller != nullptr)
	{
		delete cameracontroller;
		cameracontroller = nullptr;
	}
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();


	//�J�����R���g���[���[�X�V����
	switch (CamMode)
	{
	case Mode::ViewMode:
		// ��p�J�����R���g���[���[�A�N�e�B�u
		ViewCamera();
		cameracontroller->Update(elapsedTime);

		if (gamePad.GetButtonDown() & GamePad::BTN_A) //�X�y�[�X
		{
			CamMode = Mode::FPSMode;
		}
		break;

	case Mode::FPSMode:
		// ��p�J�����R���g���[���[�A�N�e�B�u
		FpsCamera();
		cameracontroller->FpsUpdate(elapsedTime);
		if (gamePad.GetButtonDown() & GamePad::BTN_ENTER)
		{
			CamMode = Mode::ViewMode;
			cameracontroller->SetFov(120.0f);
			cameracontroller->SetAngle(DirectX::XMFLOAT3(DirectX::XMConvertToRadians(0), 0.0f, 0.0f));
			cameracontroller->SetTarget(DirectX::XMFLOAT3(0, 0, -30));
		}

		break;
	}

	//�e�����˒��̏ꍇ�J������e�ɐݒ肷��
	if (Player::Instance().GetFiring())
	{
		TrackingCamera();
		cameracontroller->FpsUpdate(elapsedTime);
	}
	



	StageManager::Instance().Update(elapsedTime);
	//stageMain->Update(elapsedTime);
	player->Update(elapsedTime);
	//EnemyManager::Instance().Update(elapsedTime);
	//�G�t�F�N�g�X�V����
	EffectManager::Instance().Update(elapsedTime);

	shake.ShakeUpdate(elapsedTime);

	player->ct = cameracontroller->GetForward();

}

// �`�揈��
void SceneGame::Render()
{
	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// �`�揈��

	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ���C�g�����i�������j

	//�J�����p�����[�^�[�ݒ�
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	//// �r���[�s��
	//{
	//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// �J�����̎��_�i�ʒu�j
	//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// �J�����̒����_�i�^�[�Q�b�g�j
	//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// �J�����̏����
	//	//vector�ɕϊ����Ă�����(���ɓ����) 
	//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	//	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
	//	//�v�Z
	//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	//	//�������o��
	//	DirectX::XMStoreFloat4x4(&rc.view, View);
	//}
	//// �v���W�F�N�V�����s��
	//{
	//	float fovY = DirectX::XMConvertToRadians(60);	// ����p
	//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// ��ʏc���䗦(��������)
	//	float nearZ = 0.1f;	// �J�������f���o���̍ŋߋ���
	//	float farZ = 1000.0f;	// �J�������f���o���̍ŉ�����
	//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
	//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
	//}

	// 3D���f���`��
	{
		Shader* shader = graphics.GetShader(0);
		shader->Begin(dc, rc);
		//StageManager::Instance().Render(dc, shader);
		stageMain->Render(dc, shader,ViewMode);
		mark->Render(dc, shader,true);
		BulletManager::Instance().Render(dc, shader);

		//player->Render(dc, shader);

		//EnemyManager::Instance().Render(dc, shader);
		shader->End(dc);
	}
	//3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}
	// 3D�f�o�b�O�`��
	{
		//�v���~�e�B�u�f�o�b�N�`��
		player->DrawDebugPrimitive();
		//EnemyManager::Instance().DrawDebugPrimitive();
		// ���C�������_���`����s
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// �f�o�b�O�����_���`����s
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	}

	// 2D�X�v���C�g�`��
	{
	}
#ifdef _DEBUG
	// 2D�f�o�b�OGUI�`��
	{
		player->DrawDebugGUI();
		stageMain->DrawDebugGUI();
		mark->DrawDebugGUI();
		cameracontroller->cameraDebugGUI();
		bullet->DrawDebugGUI();

	}
#endif // _DEBUG
	
}


void SceneGame::RenderEnemyGauge(ID3D11DeviceContext* dc,
	const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
{
	//�r���[�|�[�g����X�ʒu//�r���[�|�[�g����Y�ʒu// �r���[�|�[�g��// �r���[�|�[�g����
	// �[�x�l�͈̔͂�\���ŏ��l// �[�x�l�͈̔͂�\���ő�l
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);
	//�ϊ��s��
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

	//�S�Ă̓G�̓����HP�Q�[�W��\��
	EnemyManager& enemyManager = EnemyManager::Instance();
	int enemyCount = enemyManager.GetEnemyCount();

	for (int i = 0; i < enemyCount; ++i)
	{
		//�\��������ꏊ���Ƃ��Ă���//WorldPosition
		Enemy* enemy = enemyManager.GetEnemy(i);
		DirectX::XMFLOAT3 worldPosition = enemy->GetPosition();
		worldPosition.y += enemy->GetHeight();

		DirectX::XMFLOAT2 gaugePositon =
			coordinateTransformation->Get2DPosition(View, Projection, World, viewport, worldPosition);
		//�Q�[�W�̒���
		const float gaugeWidth = 60.0f;
		const float gaugeHeight = 8.0f;
		float healthGauge = enemy->GetHealth() / static_cast<float>(enemy->GetMaxHealth());
		//�撣���Ă݂��Ăł���
		Camera& camera = Camera::Instance();
		DirectX::XMVECTOR cameraEye = DirectX::XMLoadFloat3(&camera.GetEye());
		DirectX::XMVECTOR cameraFront = DirectX::XMLoadFloat3(&camera.GetFront());
		DirectX::XMVECTOR enemyPosition = DirectX::XMLoadFloat3(&enemy->GetPosition());
		/*DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(cameraEye, enemyPosition);
		float dot;
		DirectX::XMStoreFloat(&dot, Dot);*/

		DirectX::XMVECTOR CE = DirectX::XMVectorSubtract(cameraEye, enemyPosition);
		DirectX::XMVECTOR Dot2 = DirectX::XMVector3Dot(CE ,cameraFront);
		float dot2;
		DirectX::XMStoreFloat(&dot2, Dot2);

		{
			if (dot2 > -0.9f)continue;
			gauge->Render(
				dc,
				gaugePositon.x - gaugeWidth * 0.5f,
				gaugePositon.y - gaugeHeight,
				gaugeWidth * healthGauge,
				gaugeHeight,
				0, 0,
				static_cast<float>(gauge->GetTextureWidth()),
				static_cast<float>(gauge->GetTextureHeight()),
				0.0f,
				1.0f, 0.0f, 0.0f, 0.0f
			);
		}
		
	}

	//�G�l�~�[�z�u����
	Mouse& mouse = Input::Instance().GetMouse();
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{
		DirectX::XMFLOAT3 screenPosition;
		screenPosition.x = static_cast<float>(mouse.GetPositionX());
		screenPosition.y = static_cast<float>(mouse.GetPositionY());
		screenPosition.z = 0.0f;
		DirectX::XMVECTOR ScreenPosition, WorldPosition;
		// ���C�̎n�_���Z�o
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		WorldPosition = 
			coordinateTransformation->Get3DPosition(View, Projection, World, viewport, ScreenPosition);

		DirectX::XMFLOAT3 rayStart;
		DirectX::XMStoreFloat3(&rayStart, WorldPosition);
		// ���C�̏I�_���Z�o
		screenPosition.z = 1.0f;
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		WorldPosition = 
			coordinateTransformation->Get3DPosition(View, Projection, World, viewport, ScreenPosition);
		DirectX::XMFLOAT3 rayEnd;
		DirectX::XMStoreFloat3(&rayEnd, WorldPosition);
		// ���C�L���X�g
		HitResult hit;
		if (StageManager::Instance().RayCast(rayStart, rayEnd, hit))
		{
			// �G��z�u
			EnemySlime* slime = new EnemySlime();
			slime->SetPosition(hit.position);
			EnemyManager::Instance().Register(slime);
		}
	}
		
}

void SceneGame::FpsCamera()
{
	cameracontroller->SetEye(player->GetPosition());

}

void SceneGame::ViewCamera()
{
	cameracontroller->SetTarget({ 0,15,0 });
}

//�e�̒ǔ��J����
void SceneGame::TrackingCamera()
{
	//cameracontroller->SetEye(BulletManager);
}



void SceneGame::TargetCamera()
{
	EnemyManager& enemyManager = EnemyManager::Instance();
	int enemyCount = enemyManager.GetEnemyCount();
	
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT_THUMB && state < enemyCount - 1)
	{
		state++;
	}
	if (gamePad.GetButtonDown() & GamePad::BTN_LEFT_THUMB && state > -1)
	{
		state--;
	}


	DirectX::XMFLOAT3 target;
	if (state == -1) {
		target = player->GetPosition();
	}
	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* enemy = enemyManager.GetEnemy(i);
		if (state == i)
		{
			target = enemy->GetPosition();
		}
	}
	//target.z -= 10.0f;
	target.y += 1.0f;
	cameracontroller->SetTarget(target);
};

