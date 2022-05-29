#include <imgui.h>
#include "player.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "Collision.h"
#include"Input/Input.h"
#include "Graphics/Graphics.h"
#include "BulletStraite.h"
#include "CameraController.h"
#include <functional>

static Player* instance = nullptr;

Player& Player::Instance()
{
    return *instance;
}

Player::Player()
{
    instance = this;
    //model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");
    model = new Model("Data/Model/Jummo/Jummo.mdl");
    //model->PlayAnimation(0);
    scale.x = scale.y = scale.z = 0.01f;

    position.x = 0.0f;
    position.y = 20.0f;
    position.x = -18.0f;


    hitEffect = new Effect("Data/Effect/Hit.efk");
    //待機ステートへ遷移
    TransitionIdleState();

    

}

Player::~Player()
{
    delete hitEffect;
    delete model;
}

void Player::Update(float elapsedTime)
{
    CollisionPlayerVsEnemies();
    InputMove(elapsedTime);

    //InputJump();
    //InputProjectile();

    //弾丸入力処理
    InputBullet();

    // 弾丸更新処理
    BulletManager::Instance().Update(elapsedTime);

 
    //ステート毎の処理
    switch (state)
    {
    case State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case State::Move:
        UpdateMoveState(elapsedTime);
        break;
    case State::Land:
        UpdateLandState(elapsedTime);
        break;
    case State::Attack:
        UpdateAttackState(elapsedTime);
        break;
    case State::Damage:
        UpdateDamageState(elapsedTime);
        break;
    case State::Death:
        UpdateDeathState(elapsedTime);
        break;
    case State::Revive:
        UpdateReviveState(elapsedTime);
        break;
    }
    //UpdateVelocity(elapsedTime);
    UpdateTransform();

    UpdateInvincibleTimer(elapsedTime);
    model->UpdateAnimation(elapsedTime);
    model->UpdateTransform(transform);
    
}

void Player::SpectatorUpdate(float elapsedTime)
{
    InputMove(elapsedTime);

    BulletManager::Instance().Update(elapsedTime);


    //ステート毎の処理
    switch (state)
    {
    case State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case State::Move:
        UpdateMoveState(elapsedTime);
        break;
    }
    UpdateVelocity(elapsedTime);
    UpdateTransform();
}

void Player::OnLanding() 
{
    jumpCount = 0;

    //if (velocity.y < gravity * 5.0f)
    //{
    //    // 着地ステートへ遷移
    //    TransitionLandState();
    //}
    if (velocity.y < gravity * 5.0f && state != State::Damage && state != State::Death)
    {
        TransitionLandState();
    }
}

void Player::InputBullet()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //直進弾丸発射
    if (gamePad.GetButtonDown() & GamePad::BTN_A && !Player::Instance().GetFiring() && !BulletManager::Instance().GetisMaterial())
    {
        Player::Instance().SetFiring(true);

        //前方向
        DirectX::XMFLOAT3 dir;
        dir.x = ct.x;
        dir.y = ct.y;
        dir.z = ct.z;
       
        //発射位置
        DirectX::XMFLOAT3 pos;
        pos.x = position.x;
        pos.y = position.y;
        pos.z = position.z;
        //発射   ここで発射される位置（プレイヤーのposition）と角度をbulletに情報を入れる
        bullet = new Bullet();
        //bullet->SetisMateril(true);
        BulletManager::Instance().SetisMateril(true);
        bullet->SetSpeed(20);
        bullet->Launch(dir, pos);
        BulletManager::Instance().Register(bullet);
    }

    // 軌道描画用弾発射
    if ((gamePad.GetButtonDown() & GamePad::BTN_ENTER || gamePad.GetButtonDown() & GamePad::BTN_LEFT_SHOULDER) && !BulletManager::Instance().GetPrediction())
    {
       
        //Player::Instance().SetFiring(true);
        //if(!BulletManager::Instance().GetisMaterial())
            
        
        //前方向
        DirectX::XMFLOAT3 dir;
        dir.x = ct.x;
        dir.y = ct.y;
        dir.z = ct.z;

        //発射位置
        DirectX::XMFLOAT3 pos;
        pos.x = position.x;
        pos.y = position.y;
        pos.z = position.z;
        //発射   ここで発射される位置（プレイヤーのposition）と角度をbulletに情報を入れる
        //BulletManager::Instance().Remove(bullet);
        bullet2 = new Bullet();
        BulletManager::Instance().Register(bullet2);
        bullet2->SetSpeed(120.0f);
       // bullet2->SetRadius(1.0f);
        //bullet->SetisMateril(false);
        BulletManager::Instance().SetisMateril(false);
        bullet2->Launch(dir, pos);
        BulletManager::Instance().SetPrediction(true);
    }

    if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT_SHOULDER && BulletManager::Instance().GetPrediction())
    {
        BulletManager::Instance().Remove(bullet2);
        BulletManager::Instance().SetPrediction(false);

    }



}

void Player::DestroyBullet()
{
    Player::Instance().SetFiring(false);
    BulletManager::Instance().Remove(bullet);
}


bool Player::InputMove(float elapsedTime)
{
    moveVec = GetMoveVec();
  //  Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed);
    Move(moveVec.x, moveVec.y,moveVec.z, moveSpeed);
    Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
    //進行ベクトルがゼロベクトルでない場合は入力された
    return moveVec.x != 0.0f || moveVec.y != 0.0f || moveVec.z != 0.0f;
}
bool Player::InputJump()
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_A)
    {
        if (jumpCount < jumpLimit)
        {
            jumpCount++;
            Jump(jumpSpeed);
            return true;
        }
    }
    //reset_position
    if (gamePad.GetButtonDown() & GamePad::BTN_BACK)
    {
        position.x = position.y = position.z = 0.0f;
    }
    return false;
}



bool Player::InputAttack()
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        return true;
    }
    return false;
}
void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{

    DirectX::XMFLOAT4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

    std::function<void(DirectX::XMFLOAT4* c)> callback = {
        [&](DirectX::XMFLOAT4* c) {
            shader->Draw(dc, model,c);
            }
    };

    color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    callback(&color);

    // 弾丸描画処理
    //BulletManager::Instance().Render(dc,shader);
}

void Player::DrawDebugGUI()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
    {
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            //position
            ImGui::InputFloat3("Position", &position.x);
            //angle
            DirectX::XMFLOAT3 a;
            a.x = DirectX::XMConvertToDegrees(angle.x);
            a.y = DirectX::XMConvertToDegrees(angle.y);
            a.z = DirectX::XMConvertToDegrees(angle.z);
            ImGui::InputFloat3("Angle", &a.x);
            angle.x = DirectX::XMConvertToRadians(a.x);
            angle.y = DirectX::XMConvertToRadians(a.y);
            angle.z = DirectX::XMConvertToRadians(a.z);
            //scale
            ImGui::InputFloat3("Scale", &scale.x);
        }

    }
    ImGui::End();
}
//スティック入力値から移動ベクトルを取得
DirectX::XMFLOAT3 Player::GetMoveVec() const
{
    //入力情報を取得
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    float ay = gamePad.GetAxisLY();
    //カメラ方向とスティックの入力値によって進行方向を計算する
    Camera& camera = Camera::Instance();
    const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
    const DirectX::XMFLOAT3& cameraFront = camera.GetFront();
    //移動ベクトルはXZ平面に水平なベクトルになるようにする
    //カメラ右方向ベクトルをXZ単位ベクトルに変換
    float cameraRightX = cameraRight.x;
    float cameraRightY = cameraRight.y;
    float cameraRightZ = cameraRight.z;
    //ベクトルの長さ
    float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightY * cameraRightY + cameraRightZ * cameraRightZ);
    if (cameraRightLength > 0.0f)
    {
        cameraRightX /= cameraRightLength;
        cameraRightY /= cameraRightLength;
        cameraRightZ /= cameraRightLength;
    }
    //カメラ前方向
    float cameraFrontX = cameraFront.x;
    float cameraFrontY = cameraFront.y;
    float cameraFrontZ = cameraFront.z;
    float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontY * cameraFrontY + cameraFrontZ * cameraFrontZ);
    if (cameraFrontLength > 0.0f)
    {
        cameraFrontX /= cameraFrontLength;
        cameraFrontY /= cameraFrontLength;
        cameraFrontZ /= cameraFrontLength;
    }
    DirectX::XMFLOAT3 vec;

    vec.x = cameraFrontX * ay + cameraRightX * ax;
    vec.z = cameraFrontZ * ay + cameraRightZ * ax;
    vec.y = cameraFrontY * ay + cameraRightY * ax;
    return vec;
}

void Player::DrawDebugPrimitive()
{
    DebugRenderer* debugRendere = Graphics::Instance().GetDebugRenderer();
    //debugRendere->DrawCylinder(position, radius,height, DirectX::XMFLOAT4(0, 0, 1, 1));

   /* Model::Node* leftHandBone = model->FindNode("mixamorig:LeftHand");
    debugRendere->DrawSphere(DirectX::XMFLOAT3(
        leftHandBone->worldTransform._41,
        leftHandBone->worldTransform._42,
        leftHandBone->worldTransform._43),
        leftHandRadius,
        DirectX::XMFLOAT4(1, 0, 0, 1)
    );*/
    //if (attackCollisionFlag)
    //{
    //    Model::Node* leftHandBone = model->FindNode("mixamorig:LeftHand");
    //    debugRendere->DrawSphere(DirectX::XMFLOAT3(
    //        leftHandBone->worldTransform._41,
    //        leftHandBone->worldTransform._42,
    //        leftHandBone->worldTransform._43),
    //        leftHandRadius,
    //        DirectX::XMFLOAT4(1, 0, 0, 1)
    //    );
    //}

    //弾丸デバッグプリミティブ描画
    BulletManager::Instance().DrawDebugPrimitive();

}

void Player::CollisionPlayerVsEnemies()
{
    EnemyManager& enemyManager = EnemyManager::Instance();
    // 全ての敵と総当たりで衝突処理
    int enemyCount = enemyManager.GetEnemyCount();
    for (int i = 0; i < enemyCount; ++i)
    {
        Enemy* enemy = enemyManager.GetEnemy(i);
        // 衝突処理
        DirectX::XMFLOAT3 outPosition;
        if (Collision::IntersectCylinderVsCylinder(position, radius, height, enemy->GetPosition(), enemy->GetRadius(), enemy->GetHeight(), outPosition))
        {
            // 押し出し後の位置設定
            enemy->SetPosition(outPosition);
            // 敵の真上付近に当たったかを判定
            DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&position);
            DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&enemy->GetPosition());
            DirectX::XMVECTOR V = DirectX::XMVectorSubtract(P, E);
            DirectX::XMVECTOR N = DirectX::XMVector3Normalize(V);
            DirectX::XMFLOAT3 normal;
            DirectX::XMStoreFloat3(&normal, N);
            // 上から踏んづけた場合は小ジャンプする
            if (normal.y > 0.8f)
            {
                // 小ジャンプする
                enemy->applyDamage(1,0.5f);
                Jump(jumpSpeed * 0.5f);
            }
            else
            {
                // 押し出し後の位置設定
                enemy->SetPosition(outPosition);
            }
        }
    }
}

void Player::CollisionNodeVsEnemies(const char* nodeName, float nodeRadius)
{
    Model::Node* node = model->FindNode(nodeName);
    DirectX::XMFLOAT3 nodePosition;
    nodePosition.x = node->worldTransform._41;
    nodePosition.y = node->worldTransform._42;
    nodePosition.z = node->worldTransform._43;

    EnemyManager& enemyManager = EnemyManager::Instance();
    //弾と敵の最大数
    int enemyCount = enemyManager.GetEnemyCount();

    for (int i = 0; i < enemyCount; i++)
    {
        Enemy* enemy = enemyManager.GetEnemy(i);
        DirectX::XMFLOAT3 outPosition;
        if (Collision::IntersectSphereVsCylinder(
            nodePosition,
            leftHandRadius,
            enemy->GetPosition(),
            enemy->GetRadius(),
            enemy->GetHeight(),
            outPosition))
        {
            //ダメージ
            if (enemy->applyDamage(1, 0.5f))
            {
                {
                    //ノックバック
                    DirectX::XMFLOAT3 impulse;
                    const float power = 10.0f;
                    const DirectX::XMFLOAT3& e = enemy->GetPosition();
                    float vx = e.x - nodePosition.x;
                    float vz = e.z - nodePosition.z;
                    float lengthXZ = sqrtf(vx * vx + vz * vz);
                    vx /= lengthXZ;
                    vz /= lengthXZ;
                    impulse.x = vx * power;
                    impulse.y = power * 0.5f;
                    impulse.z = vz * power;
                    enemy->AddImpulse(impulse);
                }
                //エフェクト再生
                {
                    DirectX::XMFLOAT3 e = enemy->GetPosition();//敵から発生
                    e.y += enemy->GetHeight() * 0.5f;//高さ調整
                    hitEffect->Play(e, 2.0f);
                }
            }
        }
    }
    
}
void Player::TransitionIdleState()
{
    state = State::Idle;
    //待機アニメーション再生
    model->PlayAnimation(Anim_Idle, true);
}
void Player::UpdateIdleState(float elapsedTime)
{
    //更新入力処理
    if (InputMove(elapsedTime))
    {
        // 移動ステートへ遷移
        TransitionMoveState();
    }
    ////ジャンプ入力処理
    //if (InputJump())
    //{
    //    TransitionJumpState();
    //}

    if (InputAttack())
    {
        TransitionAttackState();
    }
}

void Player::TransitionMoveState()
{
    state = State::Move;
    model->PlayAnimation(Anim_Running, true);
}
void Player::UpdateMoveState(float elapsedTime)
{
    if (!InputMove(elapsedTime))
    {
        TransitionIdleState();
    }
    //ジャンプ入力処理
   /* if (InputJump())
    {
        TransitionJumpState();
    }*/
    if (InputAttack())
    {
        TransitionAttackState();
    }
}

void Player::TransitionJumpState()
{
    state = State::Jump;
    model->PlayAnimation(Anim_Jump, false);
}
void Player::UpdateJumpState(float elapsedTime)
{
    // 移動入力処理
    InputMove(elapsedTime);
    // ジャンプ入力処理
    if (InputJump()) {
        // ジャンプフリップアニメーション再生
        model->PlayAnimation(Anim_Jump_Flip, false);
    }
    // ジャンプアニメーション終了後
    if (!model->IsPlayAnimation())
    {
        // 落下アニメーション再生
        model->PlayAnimation(Anim_Falling, true);
    }
}

void Player::TransitionLandState()
{
    state = State::Land;
    model->PlayAnimation(Anim_Landing, false);
}
void Player::OnDamaged()
{
    TransitionDamageState();
}
void Player::OnDead()
{
    TransitionDeathState();
}
void Player::UpdateLandState(float elapsedTime)
{
    // 着地アニメーション終了後
    if (!model->IsPlayAnimation())
    {
        // 待機ステートへ遷移
        TransitionIdleState();
    }
}

void Player::TransitionAttackState()
{
    state = State::Attack;
    model->PlayAnimation(Anim_Attack, false);
}
void Player::UpdateAttackState(float elapsedTime)
{
    // 着地アニメーション終了後
    if (!model->IsPlayAnimation())
    {
        // 待機ステートへ遷移
        TransitionIdleState();
    }
    //CollisionNodeVsEnemies("mixamorig:LeftHand", leftHandRadius);
    float animationTime = model->GetCurrentAnimationSeconds();
    attackCollisionFlag = animationTime >= 0.3f && animationTime <= 0.4f;
    if (attackCollisionFlag)
    {
        CollisionNodeVsEnemies("mixamorig:LeftHand", leftHandRadius);
    }
}
void Player::TransitionDamageState()
{
    state = State::Damage;
    model->PlayAnimation(Anim_GetHit1, false);
}
void Player::UpdateDamageState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        TransitionIdleState();
    }
}
void Player::TransitionDeathState()
{
    state = State::Death;
    model->PlayAnimation(Anim_Death, false);
}
void Player::UpdateDeathState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        GamePad& gamePad = Input::Instance().GetGamePad();
        if (gamePad.GetButtonDown() & GamePad::BTN_A)
        {
            TransitonReviveState();
        }
    }
}
void Player::TransitonReviveState()
{
    state = State::Revive;
    health = maxHealth;
    model->PlayAnimation(Anim_Revive, false);
}
void Player::UpdateReviveState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        TransitionIdleState();
    }
}