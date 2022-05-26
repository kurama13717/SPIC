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
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneTitle.h"
#include "SceneRule.h"

// 初期化
void SceneGame::Initialize()
{
	cube = new Cube();
	//stageManager.Register(stageMain);


	mark = new Mark(StageManager::Instance().GetStageNum());
	//stageManager.Register(mark);
	
	StageManager& stageManager = StageManager::Instance();
	BulletManager& bulletManager = BulletManager::Instance();
	


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
	cameracontroller->SetFov(90.0f);

	//cameramode = Mode::viewMode;
	CameraController::Instance().SetCameraMode(Mode::viewMode);
	ViewCameraInitialize();

	fixedpositions[0] = { 0.0f,20.0f,-18.0f };
	fixedpositions[1] = { 18.0f,20.0f,0.0f };
	fixedpositions[2] = { 0.0f,20.0f,18.0f };
	fixedpositions[3] = { -18.0f,20.0f,0.0f };

	fixedangles[0] = { 0.0f,3.142f,0.0f };
	fixedangles[1] = { 0.0f,1.71f,0.0f };
	fixedangles[2] = { 0.0f,0.0f,0.0f };
	fixedangles[3] = { 0.0f,-1.71f,0.0f };

	// スプライト
	gauge = new Sprite("Data/Sprite/yazirusigauge.png");
	cross = new Sprite("Data/Sprite/CrossHair.png");

	Menu = new Sprite();
	MenuGame = new Sprite("Data/Sprite/MenuGame.png");
	MenuHelp = new Sprite("Data/Sprite/MenuHelp.png");
	MenuTitle = new Sprite("Data/Sprite/MenuTitle.png");

	Rule = new Sprite("Data/Sprite/Rule.png");
	Signal = new Sprite("Data/Sprite/Signal.png");
	B = new Sprite("Data/Sprite/Bbutton.png");

	ID3D11Device* device = graphics.GetDevice();
}

// 終了化
void SceneGame::Finalize()
{
	// スプライト終了化
	if (gauge != nullptr)
	{
		delete gauge;
		gauge = nullptr;
	}
	if (cross != nullptr)
	{
		delete cross;
		cross = nullptr;
	}
	if (Menu != nullptr)
	{
		delete Menu;
		Menu = nullptr;
	}
	if (MenuGame != nullptr)
	{
		delete MenuGame;
		MenuGame = nullptr;
	}
	if (MenuHelp != nullptr)
	{
		delete MenuHelp;
		MenuHelp = nullptr;
	}
	if (MenuTitle != nullptr)
	{
		delete MenuTitle;
		MenuTitle = nullptr;
	}
	if (Rule != nullptr)
	{
		delete Rule;
		Rule = nullptr;
	}
	if (Signal != nullptr)
	{
		delete Signal;
		Signal = nullptr;
	}
	if (B != nullptr)
	{
		delete B;
		B = nullptr;
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

	if (gamePad.GetButtonDown() & GamePad::BTN_Y)
		isMenuFlag = true;
	if (isMenuFlag == true)
	{
		axisY = gamePad.GetAxisLY();
		MenuMove_D = MenuMove_U = false;
		if (axisY == 0) Moveble = true;
		if (gamePad.GetButtonDown() & GamePad::BTN_UP||axisY > 0.8f)MenuMove_U = true;
		if (gamePad.GetButtonDown() & GamePad::BTN_DOWN||axisY < -0.8f)MenuMove_D = true;
		if (MenuMove_D && Moveble)
		{
			MenuMode++;
			Moveble = false;
		}
		if (MenuMove_U && Moveble)
		{
			MenuMode--;
			Moveble = false;
		}

		if (MenuMode > 2)MenuMode = 2;
		if (MenuMode < 0)MenuMode = 0;
		menuGameColor = { 1,1,1,1 };
		menuHelpColor = { 1,1,1,1 };
		menuTitleColor = { 1,1,1,1 };

		menuGamePos = { screenWidth / 2 - MenuWidth / 2,200 };
		menuHelpPos = { screenWidth / 2 - MenuWidth / 2,400 };
		menuTitlePos = { screenWidth / 2 - MenuWidth / 2,600 };

		menuGameSize = { MenuWidth,MenuHeight };
		menuHelpSize = { MenuWidth,MenuHeight };
		menuTitleSize = { MenuWidth,MenuHeight };
		// メニュモード
		switch (MenuMode)
		{
		case menu::menuGame:
			//menuGameColor = { 1,0,0,1 };
			menuGamePos = { screenWidth / 2 - MenuWidth / 2 - 50,200 - 50 };
			menuGameSize = { MenuWidth + 100,MenuHeight + 50 };
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
				isMenuFlag = false;
			break;
		case menu::menuHelp:
			//menuHelpColor = { 1,0,0,1 };
			menuHelpPos = { screenWidth / 2 - MenuWidth / 2 - 50,400 - 50 };
			menuHelpSize = { MenuWidth + 100,MenuHeight + 50 };
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
			{
				HelpFlag = true;
			}
			break;
		case menu::menuTitle:
			//menuTitleColor = { 1,0,0,1 };
			menuTitlePos = { screenWidth / 2 - MenuWidth / 2 - 50,600 - 50 };
			menuTitleSize = { MenuWidth + 100,MenuHeight + 50 };
			if (gamePad.GetButtonDown() & GamePad::BTN_A)
			{
				isMenuFlag = false;
				SceneManager::Instance().ChangeScene(new SceneTitle);
			}
			break;
		}
		if (HelpFlag)
			Help();
	}

	else
	{
		// カメラモードで分岐
		switch (CameraController::Instance().GetCameraMode())
		{
		case Mode::viewMode:
			// 面選択処理
			ChooseSurface();

			// カメラの専用アップデート呼び出し
			cameracontroller->SetTarget({ 0,15,0 });
			cameracontroller->ViewUpdate(elapsedTime);

			// FPSモードへ移行
			if (gamePad.GetButtonDown() & GamePad::BTN_A && delaytimer == 0 && delaytimer2 == 0)FpsCameraInitialize(cameracontroller->GetCameraMode());


			if (gamePad.GetButtonDown() & GamePad::BTN_X)SpectatorCameraInitialize(CameraController::Instance().GetCameraMode());
			break;

		case Mode::fpsMode:
			// プレイヤーアップデート呼び出し
			player->Update(elapsedTime);

			// カメラ専用アップデート呼び出し
			cameracontroller->SetEye(player->GetPosition());
			cameracontroller->FpsUpdate(elapsedTime);

			// Viewモードへ移行
			if (PushPower > 0)
				PushPower -= 2.0f;
			if (PushPower == 0)
				BackFlag = false;
			if (gamePad.GetButton() & GamePad::BTN_B)
			{
				BackFlag = true;
				PushPower += 6.0f;
			}
			if (PushPower > 360)
			{
				BackFlag = false;
				ViewCameraInitialize();
			}

			// スペクテイターモードへ移行
			if (gamePad.GetButtonDown() & GamePad::BTN_X)SpectatorCameraInitialize(CameraController::Instance().GetCameraMode());

			break;

		case Mode::spectatorMode:
			// プレイヤーアップデート呼び出し
			player->SpectatorUpdate(elapsedTime);

			// カメラ専用アップデート呼び出し
			cameracontroller->SetEye(player->GetPosition());
			cameracontroller->SpectatorUpdate(elapsedTime);

			if (PushPower > 0)
				PushPower -= 2.0f;
			if (PushPower == 0)
				BackFlag = false;
			if (gamePad.GetButton() & GamePad::BTN_B)
			{
				BackFlag = true;
				PushPower += 6.0f;
			}
			if (PushPower > 360)
			{
				BackFlag = false;
				switch (BeforeCM)	// スペクテイターモードに入った際のモードで分岐
				{
				case Mode::viewMode:
					ViewCameraInitialize();
					break;
				case Mode::fpsMode:
					FpsCameraInitialize(CameraController::Instance().GetCameraMode());
					break;
				}
			}

			break;
		}

		//弾が発射中の場合カメラを弾に設定する
		if (Player::Instance().GetFiring())
		{
			TrackingCamera();
			//cameracontroller->FpsUpdate(elapsedTime);
		}




		StageManager::Instance().Update(elapsedTime);
		//stageMain->Update(elapsedTime);
		//player->Update(elapsedTime);
		//EnemyManager::Instance().Update(elapsedTime);
		//エフェクト更新処理
		EffectManager::Instance().Update(elapsedTime);

		shake.ShakeUpdate(elapsedTime);

		player->ct = cameracontroller->GetForward();

		if (StageManager::Instance().GetStageClear())SceneManager::Instance().ChangeScene(new SceneTitle);
		/*if (StageManager::Instance().GetStageClear())
		{
			StageManager::Instance().SetStageNum(2);
			Initialize();
		}*/

	}
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

#if true

	// 3Dモデル描画
	{
		Shader* shader = graphics.GetShader(0);
		shader->Begin(dc, rc);
		StageManager::Instance().Render(dc, shader,false);
		cube->Render(dc, shader, CameraController::Instance().GetCameraMode(), selectedsurface);
		BulletManager::Instance().Render(dc, shader);

		
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

#endif

	// 2Dスプライト描画
	{
		Shader* shader = graphics.GetShader(2);
		shader->Begin(dc, rc);

		float crossWidth = static_cast<float>(cross->GetTextureWidth());
		float crossHeight = static_cast<float>(cross->GetTextureHeight());
		// ゲージの MAX 長さと高さ
		const float gaugeWidth = static_cast<float>(gauge->GetTextureWidth());
		const float gaugeHeight = static_cast<float>(gauge->GetTextureHeight());
		// 現在 HP/MAXHP で 0.0(HP-MIN)～1.0(HP-MAX)の比率を出す。

		float RuleWidth = static_cast<float>(Rule->GetTextureWidth());
		float RuleHeight = static_cast<float>(Rule->GetTextureHeight());
		float SignalWidth = static_cast<float>(Signal->GetTextureWidth());
		float SignalHeight = static_cast<float>(Signal->GetTextureHeight());

		if (CameraController::Instance().GetCameraMode() == Mode::fpsMode)
		{
			cross->Render(dc,
				screenWidth / 2 - crossWidth / 4, screenHeight / 2 - crossHeight / 4,
				crossWidth / 2,
				crossHeight / 2,
				0, 0, crossWidth, crossHeight,
				0,
				1, 1, 1, 1);
		}
		if (BackFlag)
		{
			gauge->Render(dc,
				screenWidth - gaugeWidth, screenHeight - gaugeHeight,
				gaugeWidth,
				gaugeHeight,
				0, 0, gaugeWidth, gaugeHeight,
				PushPower,
				1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (isMenuFlag)
		{
			Menu->Render(dc,
				0, 0,
				screenWidth,
				screenHeight,
				0, 0, screenWidth, screenHeight,
				0,
				0, 0, 0, 0.5f);

			MenuGame->Render(dc,
				menuGamePos.x, menuGamePos.y,
				menuGameSize.x,
				menuGameSize.y,
				0, 0, MenuWidth, MenuHeight,
				0,
				menuGameColor.x, menuGameColor.y, menuGameColor.z, menuGameColor.w);

			MenuHelp->Render(dc,
				menuHelpPos.x, menuHelpPos.y,
				menuHelpSize.x,
				menuHelpSize.y,
				0, 0, MenuWidth, MenuHeight,
				0,
				menuHelpColor.x, menuHelpColor.y, menuHelpColor.z, menuHelpColor.w);

			MenuTitle->Render(dc,
				menuTitlePos.x, menuTitlePos.y,
				menuTitleSize.x,
				menuTitleSize.y,
				0, 0, MenuWidth, MenuHeight,
				0,
				menuTitleColor.x, menuTitleColor.y, menuTitleColor.z, menuTitleColor.w);
		}
		if (HelpFlag)
		{
			Rule->Render(dc,
				0, 0, screenWidth * 3, screenHeight,
				Pos.x, 0, RuleWidth, RuleHeight,
				0,
				1, 1, 1, 1);

			if (SignalTimer % 60 >= 6)
			{
				if (SceneCount == 1)
				{
					Signal->Render(dc,
						screenWidth - SignalWidth / 2, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						0,
						1, 1, 1, 1);
				}
				if (SceneCount == 2)
				{
					Signal->Render(dc,
						0, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						180,
						1, 1, 1, 1);
					Signal->Render(dc,
						screenWidth - SignalWidth / 2, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						0,
						1, 1, 1, 1);
				}
				if (SceneCount == 3)
				{
					Signal->Render(dc,
						0, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						180,
						1, 1, 1, 1);
					B->Render(dc,
						screenWidth - SignalWidth / 2, screenHeight / 2 - SignalHeight / 4, SignalWidth / 2, SignalHeight / 2,
						0, 0, SignalWidth, SignalHeight,
						0,
						1, 1, 1, 1);
				}
			}
		}
		shader->End(dc);

	}
#ifdef _DEBUG
	// 2DデバッグGUI描画
	{
		player->DrawDebugGUI();
		cube->DrawDebugGUI();
		mark->DrawDebugGUI();
		cameracontroller->cameraDebugGUI();

		// 弾の情報表示
		int count = BulletManager::Instance().GetBulletCount() - 1;
		if (count < 0)
			return;

		auto bullet = BulletManager::Instance().GetBullet(count);
		bullet->DrawDebugGUI();
	}
#endif // _DEBUG
	
}


//void SceneGame::RenderEnemyGauge(ID3D11DeviceContext* dc,
//	const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
//{
//	//ビューポート左上X位置//ビューポート左上Y位置// ビューポート幅// ビューポート高さ
//	// 深度値の範囲を表す最小値// 深度値の範囲を表す最大値
//	D3D11_VIEWPORT viewport;
//	UINT numViewports = 1;
//	dc->RSGetViewports(&numViewports, &viewport);
//	//変換行列
//	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
//	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
//	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();
//
//	//全ての敵の頭上にHPゲージを表示
//	EnemyManager& enemyManager = EnemyManager::Instance();
//	int enemyCount = enemyManager.GetEnemyCount();
//
//	for (int i = 0; i < enemyCount; ++i)
//	{
//		//表示させる場所をとってくる//WorldPosition
//		Enemy* enemy = enemyManager.GetEnemy(i);
//		DirectX::XMFLOAT3 worldPosition = enemy->GetPosition();
//		worldPosition.y += enemy->GetHeight();
//
//		DirectX::XMFLOAT2 gaugePositon =
//			coordinateTransformation->Get2DPosition(View, Projection, World, viewport, worldPosition);
//		//ゲージの長さ
//		const float gaugeWidth = 60.0f;
//		const float gaugeHeight = 8.0f;
//		float healthGauge = enemy->GetHealth() / static_cast<float>(enemy->GetMaxHealth());
//		//頑張ってみたてでけた
//		Camera& camera = Camera::Instance();
//		DirectX::XMVECTOR cameraEye = DirectX::XMLoadFloat3(&camera.GetEye());
//		DirectX::XMVECTOR cameraFront = DirectX::XMLoadFloat3(&camera.GetFront());
//		DirectX::XMVECTOR enemyPosition = DirectX::XMLoadFloat3(&enemy->GetPosition());
//		/*DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(cameraEye, enemyPosition);
//		float dot;
//		DirectX::XMStoreFloat(&dot, Dot);*/
//
//		DirectX::XMVECTOR CE = DirectX::XMVectorSubtract(cameraEye, enemyPosition);
//		DirectX::XMVECTOR Dot2 = DirectX::XMVector3Dot(CE ,cameraFront);
//		float dot2;
//		DirectX::XMStoreFloat(&dot2, Dot2);
//
//		{
//			if (dot2 > -0.9f)continue;
//			gauge->Render(
//				dc,
//				gaugePositon.x - gaugeWidth * 0.5f,
//				gaugePositon.y - gaugeHeight,
//				gaugeWidth * healthGauge,
//				gaugeHeight,
//				0, 0,
//				static_cast<float>(gauge->GetTextureWidth()),
//				static_cast<float>(gauge->GetTextureHeight()),
//				0.0f,
//				1.0f, 0.0f, 0.0f, 0.0f
//			);
//		}
//		
//	}
//
//	//エネミー配置処理
//	Mouse& mouse = Input::Instance().GetMouse();
//	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
//	{
//		DirectX::XMFLOAT3 screenPosition;
//		screenPosition.x = static_cast<float>(mouse.GetPositionX());
//		screenPosition.y = static_cast<float>(mouse.GetPositionY());
//		screenPosition.z = 0.0f;
//		DirectX::XMVECTOR ScreenPosition, WorldPosition;
//		// レイの始点を算出
//		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
//		WorldPosition = 
//			coordinateTransformation->Get3DPosition(View, Projection, World, viewport, ScreenPosition);
//
//		DirectX::XMFLOAT3 rayStart;
//		DirectX::XMStoreFloat3(&rayStart, WorldPosition);
//		// レイの終点を算出
//		screenPosition.z = 1.0f;
//		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
//		WorldPosition = 
//			coordinateTransformation->Get3DPosition(View, Projection, World, viewport, ScreenPosition);
//		DirectX::XMFLOAT3 rayEnd;
//		DirectX::XMStoreFloat3(&rayEnd, WorldPosition);
//		// レイキャスト
//		HitResult hit;
//		if (StageManager::Instance().RayCast(rayStart, rayEnd, hit))
//		{
//			// 敵を配置
//			EnemySlime* slime = new EnemySlime();
//			slime->SetPosition(hit.position);
//			EnemyManager::Instance().Register(slime);
//		}
//	}
//		
//}

// FPSカメライニシャライズ
void SceneGame::FpsCameraInitialize(int BeforeMode)
{
	PushPower = 0;

	switch (BeforeMode)
	{
	case Mode::viewMode:
		cameracontroller->SetAngle({ cameracontroller->GetAngle().x,cameracontroller->GetAngle().y + DirectX::XM_PI,cameracontroller->GetAngle().z });
		cameracontroller->SetTarget({ 0,15,0 });
		cameracontroller->SetCurrentAngle(cameracontroller->GetAngle());
		player->SetPosition(fixedpositions[selectedsurface]);
		//player->SetAngle()
		break;
	case Mode::spectatorMode:
		//cameracontroller->SetAngle(fixedangles[selectedsurface]);
		cameracontroller->SetAngle(KeepAngle);
		cameracontroller->SetTarget({ 0,15,0 });
		cameracontroller->SetCurrentAngle(cameracontroller->GetAngle());
		player->SetPosition(fixedpositions[selectedsurface]);
		break;
	}
	// モード切り替え
	CameraController::Instance().SetCameraMode(Mode::fpsMode);

}

// Viewカメライニシャライズ
void SceneGame::ViewCameraInitialize()
{
	PushPower = 0;
	//cameracontroller->SetAngle({ 0,cameracontroller->GetAngle().y + DirectX::XM_PI,0 });

	switch (selectedsurface)
	{
	case 0:
		cameracontroller->SetAngle({ 0,0,0 });
		break;
	case 1:
		cameracontroller->SetAngle({ 0,-DirectX::XM_PI * 0.5f,0 });
		break;
	case 2:
		cameracontroller->SetAngle({ 0,-DirectX::XM_PI,0 });
		break;
	case 3:
		cameracontroller->SetAngle({ 0,-DirectX::XM_PI * 1.5,0 });
		break;
	}

	// モード切り替え
	//cameramode = Mode::viewMode;
	CameraController::Instance().SetCameraMode(Mode::viewMode);
}

// スペクテイターカメライニシャライズ
void SceneGame::SpectatorCameraInitialize(int BeforeMode)
{
	BeforeCM = BeforeMode;
	PushPower = 0;
	KeepAngle = cameracontroller->GetAngle();

	switch (BeforeMode)
	{
	case Mode::viewMode:
		cameracontroller->SetAngle({ cameracontroller->GetAngle().x,cameracontroller->GetAngle().y + DirectX::XM_PI,cameracontroller->GetAngle().z });
		cameracontroller->SetTarget({ 0,15,0 });
		cameracontroller->SetCurrentAngle(cameracontroller->GetAngle());
		player->SetPosition(cameracontroller->GetEye());
		break;
	case Mode::fpsMode:
		break;
	}

	// モード切り替え
	//cameramode = Mode::spectatorMode;
	CameraController::Instance().SetCameraMode(Mode::spectatorMode);
}

// 面選択
void SceneGame::ChooseSurface()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	axisX = gamePad.GetAxisLX();
	if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT || axisX > 0.8f)
	{
		if (delaytimer == 0 && delaytimer2 == 0)
			delayflag = true;
	}
	if (delayflag == true)delaytimer++;
	if (delaytimer > 45)
	{
		selectedsurface++;
		delaytimer = 0;
		delayflag = false;
	}
	if (gamePad.GetButtonDown() & GamePad::BTN_LEFT || axisX < -0.8f)
	{
		if (delaytimer == 0 && delaytimer2 == 0)delayflag2 = true;
	}
	if (delayflag2 == true)delaytimer2++;
	if (delaytimer2 > 45)
	{
		selectedsurface--;
		delaytimer2 = 0;
		delayflag2 = false;
	}
	if (selectedsurface < 0)selectedsurface = 3;
	if (selectedsurface > 3)selectedsurface = 0;
}

//弾の追尾カメラ
void SceneGame::TrackingCamera()
{
	//cameracontroller->SetEye(BulletManager);
}

// ヘルプ画面
void SceneGame::Help()
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	axisX = gamePad.GetAxisLX();
	Graphics& graphics = Graphics::Instance();
	float screenWidth = static_cast<float>(graphics.GetScreenWidth());

	if (RuleMove_R == false && RuleMove_L == false)
	{
		if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT || axisX > 0.8f)
		{
			if (Pos.x < 1280 * 2)
			{
				RulePosX = Pos.x;
				RuleMove_R = true;
			}
		}

		if (gamePad.GetButtonDown() & GamePad::BTN_LEFT || axisX < -0.8f)
		{
			if (Pos.x > 0)
			{
				RulePosX = Pos.x;
				RuleMove_L = true;
			}
		}

		if (Pos.x == 1280 * 2 && gamePad.GetButtonDown() & GamePad::BTN_B)
		{
			HelpFlag = false;
		}
	}
	// ルール画面移動処理(右回り)
	if (RuleMove_R == true)
	{
		Pos.x += 20;
		if (Pos.x > RulePosX + 1280)
		{
			RuleMove_R = false;
			SceneCount++;
			Pos.x = RulePosX + 1280;
		}
	}
	// ルール画面移動処理(左回り)
	if (RuleMove_L == true)
	{
		Pos.x -= 20;
		if (Pos.x < RulePosX - 1280)
		{
			RuleMove_L = false;
			SceneCount--;
			Pos.x = RulePosX - 1280;
		}
	}
	SignalTimer++;
}