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
// 初期化
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
	//カメラ初期設定

	camera.SetLookAt(DirectX::XMFLOAT3(0, 10, -10), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1, 0));
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	cameracontroller->SetAngle(DirectX::XMFLOAT3(DirectX::XMConvertToRadians(15), 0.0f, 0.0f));
	cameracontroller->SetFov(120.0f);

	CamMode = Mode::FPSMode;
	
	//エネミー初期化
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

	//ゲージスプライト
	gauge = new Sprite();
}

// 終了化
void SceneGame::Finalize()
{
	//ゲージスプライト終了化
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

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();


	//カメラコントローラー更新処理
	switch (CamMode)
	{
	case Mode::ViewMode:
		// 専用カメラコントローラーアクティブ
		ViewCamera();
		cameracontroller->Update(elapsedTime);

		if (gamePad.GetButtonDown() & GamePad::BTN_A) //スペース
		{
			CamMode = Mode::FPSMode;
		}
		break;

	case Mode::FPSMode:
		// 専用カメラコントローラーアクティブ
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

	//弾が発射中の場合カメラを弾に設定する
	if (Player::Instance().GetFiring())
	{
		TrackingCamera();
		cameracontroller->FpsUpdate(elapsedTime);
	}
	



	StageManager::Instance().Update(elapsedTime);
	//stageMain->Update(elapsedTime);
	player->Update(elapsedTime);
	//EnemyManager::Instance().Update(elapsedTime);
	//エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);

	shake.ShakeUpdate(elapsedTime);

	player->ct = cameracontroller->GetForward();

}

// 描画処理
void SceneGame::Render()
{
	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 描画処理

	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）

	//カメラパラメーター設定
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(cameracontroller->GetFov()), graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);
	//// ビュー行列
	//{
	//	DirectX::XMFLOAT3 eye = { 0, 10, -10 };	// カメラの視点（位置）
	//	DirectX::XMFLOAT3 focus = { 0, 0, 0 };	// カメラの注視点（ターゲット）
	//	DirectX::XMFLOAT3 up = { 0, 1, 0 };		// カメラの上方向
	//	//vectorに変換してあげる(箱に入れる) 
	//	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	//	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	//	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
	//	//計算
	//	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	//	//情報を取り出す
	//	DirectX::XMStoreFloat4x4(&rc.view, View);
	//}
	//// プロジェクション行列
	//{
	//	float fovY = DirectX::XMConvertToRadians(60);	// 視野角
	//	float aspectRatio = graphics.GetScreenWidth() / graphics.GetScreenHeight();	// 画面縦横比率(幅÷高さ)
	//	float nearZ = 0.1f;	// カメラが映し出すの最近距離
	//	float farZ = 1000.0f;	// カメラが映し出すの最遠距離
	//	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, nearZ, farZ);
	//	DirectX::XMStoreFloat4x4(&rc.projection, Projection);
	//}

	// 3Dモデル描画
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
	//3Dエフェクト描画
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}
	// 3Dデバッグ描画
	{
		//プリミティブデバック描画
		player->DrawDebugPrimitive();
		//EnemyManager::Instance().DrawDebugPrimitive();
		// ラインレンダラ描画実行
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// デバッグレンダラ描画実行
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
	}

	// 2Dスプライト描画
	{
	}
#ifdef _DEBUG
	// 2DデバッグGUI描画
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
	//ビューポート左上X位置//ビューポート左上Y位置// ビューポート幅// ビューポート高さ
	// 深度値の範囲を表す最小値// 深度値の範囲を表す最大値
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);
	//変換行列
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

	//全ての敵の頭上にHPゲージを表示
	EnemyManager& enemyManager = EnemyManager::Instance();
	int enemyCount = enemyManager.GetEnemyCount();

	for (int i = 0; i < enemyCount; ++i)
	{
		//表示させる場所をとってくる//WorldPosition
		Enemy* enemy = enemyManager.GetEnemy(i);
		DirectX::XMFLOAT3 worldPosition = enemy->GetPosition();
		worldPosition.y += enemy->GetHeight();

		DirectX::XMFLOAT2 gaugePositon =
			coordinateTransformation->Get2DPosition(View, Projection, World, viewport, worldPosition);
		//ゲージの長さ
		const float gaugeWidth = 60.0f;
		const float gaugeHeight = 8.0f;
		float healthGauge = enemy->GetHealth() / static_cast<float>(enemy->GetMaxHealth());
		//頑張ってみたてでけた
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

	//エネミー配置処理
	Mouse& mouse = Input::Instance().GetMouse();
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{
		DirectX::XMFLOAT3 screenPosition;
		screenPosition.x = static_cast<float>(mouse.GetPositionX());
		screenPosition.y = static_cast<float>(mouse.GetPositionY());
		screenPosition.z = 0.0f;
		DirectX::XMVECTOR ScreenPosition, WorldPosition;
		// レイの始点を算出
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		WorldPosition = 
			coordinateTransformation->Get3DPosition(View, Projection, World, viewport, ScreenPosition);

		DirectX::XMFLOAT3 rayStart;
		DirectX::XMStoreFloat3(&rayStart, WorldPosition);
		// レイの終点を算出
		screenPosition.z = 1.0f;
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		WorldPosition = 
			coordinateTransformation->Get3DPosition(View, Projection, World, viewport, ScreenPosition);
		DirectX::XMFLOAT3 rayEnd;
		DirectX::XMStoreFloat3(&rayEnd, WorldPosition);
		// レイキャスト
		HitResult hit;
		if (StageManager::Instance().RayCast(rayStart, rayEnd, hit))
		{
			// 敵を配置
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

//弾の追尾カメラ
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

