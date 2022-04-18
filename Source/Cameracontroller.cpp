#include <imgui.h>
#include "CameraController.h"
#include "Camera.h"
#include "Input/Input.h"

void CameraController::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisRX();
    float ay = gamePad.GetAxisRY();

    //カメラの回転速度
    float speed = rollSpeed * elapsedTime;
    //スティックの入力値に合わせてX軸とY軸を回転
    if (Inversion) { reverse = -1; }
    else { reverse = 1; }
    angle.x += speed * ay * sensitivity.y * reverse;
    angle.y += speed * ax * sensitivity.x * reverse;

    // カメラ旋回処理(右回り)
    if (CameraTurn_R == false)
    {
        if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT)
        {
            NowAngle.y = angle.y;
            CameraTurn_R = true;
        }
    }
    if (CameraTurn_R == true)
    {
        angle.y -= DirectX::XM_2PI * 0.25f / 30;
        if (angle.y < NowAngle.y - 1.57f)
        {
            CameraTurn_R = false;
            angle.y = NowAngle.y - DirectX::XM_2PI * 0.25f;
        }
    }

    // カメラ旋回処理(左回り)
    if (CameraTurn_L == false)
    {
        if (gamePad.GetButtonDown() & GamePad::BTN_LEFT )
        {
            NowAngle.y = angle.y;
            CameraTurn_L = true;
        }
    }
    if (CameraTurn_L == true)
    {
        angle.y += DirectX::XM_2PI * 0.25f / 30;
        if (angle.y > NowAngle.y + 1.57f)
        {
            CameraTurn_L = false;
            angle.y = NowAngle.y + DirectX::XM_2PI * 0.25f;
        }
    }

    //限界値
    //if (angle.x >= maxAngleX)
    //{
    //    angle.x = maxAngleX;
    //}
    //if (angle.x <= minAngleX)
    //{
    //    angle.x = minAngleX;
    //}
    //if (angle.y < -DirectX::XM_PI)
    //{
    //    angle.y += DirectX::XM_2PI;
    //}
    //if (angle.y > DirectX::XM_2PI)
    //{
    //    angle.y -= DirectX::XM_2PI;
    //}
    //カメラ回転値を回転行列に変換
    DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
    //回転行列から前方向ベクトルに取り出す
    Front = Transform.r[2];
    DirectX::XMStoreFloat3(&front, Front);
    //注視点から後ろベクトル方向に一定距離離れたカメラ視点を求める
    //DirectX::XMFLOAT3 eye;
    eye.x = target.x + range * -front.x;
    eye.y = target.y + range * -front.y;
    eye.z = target.z + range * -front.z;

    Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}

void CameraController::ViewUpdate(float elapsedTime)
{
    //eye.x = target.x + range * -front.x;
    //eye.y = target.y + range * -front.y;
    //eye.z = target.z + range * -front.z;
    Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}

void CameraController::FpsUpdate(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();


    float ax = gamePad.GetAxisRY();
    float ay = gamePad.GetAxisRX();
    //カメラの回転速度
    float speed = rollSpeed * elapsedTime;

    angle.x += (ax * speed);
    angle.y += (ay * speed);

    DirectX::XMFLOAT3 forwardf = { 0, 0, -1 };
    DirectX::XMFLOAT3 leftf = { -1, 0, 0 };
    DirectX::XMFLOAT3 upf = { 0, 1, 0 };


    auto forwardv = DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&forwardf), DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, 0));
    auto leftv = DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&leftf), DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, 0));
    auto upv = DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&upf), DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, 0));

    DirectX::XMFLOAT3 position = { 0,0,0 };

    
    DirectX::XMStoreFloat3(&cameraForward, forwardv);


  

    cameraTarget.x = eye.x + cameraForward.x;
    cameraTarget.y = eye.y + cameraForward.y;
    cameraTarget.z = eye.z + cameraForward.z;

    DirectX::XMStoreFloat3(&cameraUp, upv);

    Camera::Instance().SetLookAt(eye, cameraTarget, cameraUp);


}

void CameraController::cameraDebugGUI()
{
    ImGui::SetNextWindowPos(ImVec2(10, 310), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_None))
    {
        if (ImGui::CollapsingHeader("Controll", ImGuiTreeNodeFlags_DefaultOpen))
        {
            //カメラ感度
            ImGui::SliderFloat("Fov", &fov,2.0f,100.0f);
            ImGui::SliderFloat("Angle.x", &angle.x, 0, 360.0f);
            ImGui::SliderFloat("Angle.y", &angle.y, 0, 360.0f);
            ImGui::SliderFloat("Angle.z", &angle.z, 0, 360.0f);             
            ImGui::SliderFloat("Eye.x", &eye.x, 0, 360.0f);
            ImGui::SliderFloat("Eye.y", &eye.y, 0, 360.0f);
            ImGui::SliderFloat("Eye.z", &eye.z, 0, 360.0f);             
            ImGui::SliderFloat("front.x", &front.x, 0, 360.0f);
            ImGui::SliderFloat("front.y", &front.y, 0, 360.0f);
            ImGui::SliderFloat("front.z", &front.z, 0, 360.0f);            
            ImGui::SliderFloat2("Sensitivity", &sensitivity.x,1.0f,10.0f);
            if (ImGui::Button("reverse:true"))
            {
                Inversion = true;
            }
            if (ImGui::Button("reverse:false"))
            {
                Inversion = false;
            }
        }

    }
    ImGui::End();
}
