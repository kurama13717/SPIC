#include <imgui.h>
#include "CameraController.h"
#include "Camera.h"
#include "Input/Input.h"

void CameraController::Update(float elapsedTime)
{
    //GamePad& gamePad = Input::Instance().GetGamePad();
    //ax = gamePad.GetAxisLX();
    //float ay = gamePad.GetAxisRY()*0;

    ////�J�����̉�]���x
    //float speed = rollSpeed * elapsedTime;
    ////�X�e�B�b�N�̓��͒l�ɍ��킹��X����Y������]
    //if (Inversion) { reverse = -1; }
    //else { reverse = 1; }
    //angle.x += speed * ay * sensitivity.y * reverse*0;
    //angle.y += speed * ax * sensitivity.x * reverse;

    //// �J�������񏈗�(�E���)
    //if (cameraturn_r == false )
    //{
    //    if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT)
    //    {
    //        currentangle.y = angle.y;
    //        cameraturn_r = true;
    //    }
    //}
    //if (cameraturn_r == true)
    //{
    //    angle.y -= DirectX::XM_2PI * 0.25f / 30;
    //    if (angle.y < currentangle.y - 1.57f)
    //    {
    //        cameraturn_r = false;
    //        angle.y = currentangle.y - DirectX::XM_2PI * 0.25f;
    //    }
    //}

    //// �J�������񏈗�(�����)
    //if (cameraturn_l == false )
    //{
    //    if (gamePad.GetButtonDown() & GamePad::BTN_LEFT )
    //    {
    //        currentangle.y = angle.y;
    //        cameraturn_l = true;
    //    }
    //}
    //if (cameraturn_l == true)
    //{
    //    angle.y += DirectX::XM_2PI * 0.25f / 30;
    //    if (angle.y > currentangle.y + 1.57f)
    //    {
    //        cameraturn_l = false;
    //        angle.y = currentangle.y + DirectX::XM_2PI * 0.25f;
    //    }
    //}

    ////���E�l
    ////if (angle.x >= maxAngleX)
    ////{
    ////    angle.x = maxAngleX;
    ////}
    ////if (angle.x <= minAngleX)
    ////{
    ////    angle.x = minAngleX;
    ////}
    ////if (angle.y < -DirectX::XM_PI)
    ////{
    ////    angle.y += DirectX::XM_2PI;
    ////}
    ////if (angle.y > DirectX::XM_2PI)
    ////{
    ////    angle.y -= DirectX::XM_2PI;
    ////}
    ////�J������]�l����]�s��ɕϊ�
    //DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
    ////��]�s�񂩂�O�����x�N�g���Ɏ��o��
    //Front = Transform.r[2];
    //DirectX::XMStoreFloat3(&front, Front);
    ////�����_������x�N�g�������Ɉ�苗�����ꂽ�J�������_�����߂�
    ////DirectX::XMFLOAT3 eye;
    //eye.x = target.x + range * -front.x;
    //eye.y = target.y + 10;
    //eye.z = target.z + range * -front.z;

    //Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}

void CameraController::ViewUpdate(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    axisX = gamePad.GetAxisLX();
    if (cameraturn_r == false && cameraturn_l == false)
    {
        if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT || axisX > 0.8f)
        {
            currentangle.y = angle.y;
            cameraturn_r = true;
        }

        if (gamePad.GetButtonDown() & GamePad::BTN_LEFT || axisX < -0.8f)
        {
            currentangle.y = angle.y;
            cameraturn_l = true;
        }
    }
    // �J�������񏈗�(�E���)
    if (cameraturn_r == true)
    {
        angle.y -= DirectX::XM_2PI * 0.25f / 45;
        if (angle.y < currentangle.y - 1.57f)
        {
            cameraturn_r = false;
            angle.y = currentangle.y - DirectX::XM_PI * 0.5f;
        }
    }
    // �J�������񏈗�(�����)
    if (cameraturn_l == true)
    {
        angle.y += DirectX::XM_2PI * 0.25f / 45;
        if (angle.y > currentangle.y + 1.57f)
        {
            cameraturn_l = false;
            angle.y = currentangle.y + DirectX::XM_PI * 0.5f;
        }
    }

    //�J������]�l����]�s��ɕϊ�
    DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
    //��]�s�񂩂�O�����x�N�g���Ɏ��o��
    Front = Transform.r[2];
    DirectX::XMStoreFloat3(&front, Front);
    //�����_������x�N�g�������Ɉ�苗�����ꂽ�J�������_�����߂�
    //DirectX::XMFLOAT3 eye;
    eye.x = target.x + range * -front.x;
    eye.y = target.y + 10;
    eye.z = target.z + range * -front.z;

    Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}

void CameraController::FpsUpdate(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisRY();
    float ay = gamePad.GetAxisRX();

    //�J�����̉�]���x
    float speed = rollSpeed * elapsedTime;

    angle.x += (ax * speed);
    angle.y += (ay * speed);

    // �J�����A���O������
    if (angle.y > currentangle.y + DirectX::XM_PI * 0.5f)angle.y = currentangle.y + DirectX::XM_PI * 0.5f;
    if (angle.y < currentangle.y - DirectX::XM_PI * 0.5f)angle.y = currentangle.y - DirectX::XM_PI * 0.5f;
    if (angle.x > DirectX::XM_PI * 0.5f)angle.x = DirectX::XM_PI * 0.5f;
    if (angle.x < -DirectX::XM_PI * 0.5f)angle.x = -DirectX::XM_PI * 0.5f;

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

void CameraController::SpectatorUpdate(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisRY();
    float ay = gamePad.GetAxisRX();

    //�J�����̉�]���x
    float speed = rollSpeed * elapsedTime;

    angle.x += (ax * speed);
    angle.y += (ay * speed);

    // �J�����A���O������
    //if (angle.y > currentangle.y + DirectX::XM_PI * 0.5f)angle.y = currentangle.y + DirectX::XM_PI * 0.5f;
    //if (angle.y < currentangle.y - DirectX::XM_PI * 0.5f)angle.y = currentangle.y - DirectX::XM_PI * 0.5f;
    if (angle.x > DirectX::XM_PI * 0.5f)angle.x = DirectX::XM_PI * 0.5f;
    if (angle.x < -DirectX::XM_PI * 0.5f)angle.x = -DirectX::XM_PI * 0.5f;

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
            //�J�������x
            ImGui::SliderFloat("Fov", &fov,2.0f,100.0f);
            ImGui::SliderFloat("Angle.x", &angle.x, 0, 360.0f);
            ImGui::SliderFloat("Angle.y", &angle.y, 0, 360.0f);
            ImGui::SliderFloat("Angle.z", &angle.z, 0, 360.0f);              
            ImGui::SliderFloat("CAngle.x", &currentangle.x, 0, 360.0f);
            ImGui::SliderFloat("CAngle.y", &currentangle.y, 0, 360.0f);
            ImGui::SliderFloat("CAngle.z", &currentangle.z, 0, 360.0f);             
            ImGui::SliderFloat("Eye.x", &eye.x, 0, 360.0f);
            ImGui::SliderFloat("Eye.y", &eye.y, 0, 360.0f);
            ImGui::SliderFloat("Eye.z", &eye.z, 0, 360.0f);             
            ImGui::SliderFloat("front.x", &cameraForward.x, 0, 360.0f);
            ImGui::SliderFloat("front.y", &cameraForward.y, 0, 360.0f);
            ImGui::SliderFloat("front.z", &cameraForward.z, 0, 360.0f);
            ImGui::SliderFloat2("Sensitivity", &sensitivity.x,1.0f,10.0f);
            if (ImGui::Button("reverse:true"))
            {
                Inversion = true;
            }
            if (ImGui::Button("reverse:false"))
            {
                Inversion = false;
            }

            ImGui::InputFloat("Axis", &axisX);
        }

    }
    ImGui::End();
}
