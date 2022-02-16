#include <imgui.h>
#include "CameraController.h"
#include "Camera.h"
#include "Input/Input.h"

void CameraController::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisRX();
    float ay = gamePad.GetAxisRY();
    //�J�����̉�]���x
    float speed = rollSpeed * elapsedTime;
    //�X�e�B�b�N�̓��͒l�ɍ��킹��X����Y������]
    if (Inversion) { reverse = -1; }
    else { reverse = 1; }
    angle.x += speed * ay * sensitivity.y * reverse;
    angle.y += speed * ax * sensitivity.x * reverse;
    //���E�l

    if (angle.x >= maxAngleX)
    {
        angle.x = maxAngleX;
    }
    if (angle.x <= minAngleX)
    {
        angle.x = minAngleX;
    }
    if (angle.y < -DirectX::XM_PI)
    {
        angle.y += DirectX::XM_2PI;
    }
    if (angle.y > DirectX::XM_2PI)
    {
        angle.y -= DirectX::XM_2PI;
    }
    //�J������]�l����]�s��ɕϊ�
    DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
    //��]�s�񂩂�O�����x�N�g���Ɏ��o��
    DirectX::XMVECTOR Front = Transform.r[2];
    DirectX::XMFLOAT3 front;
    DirectX::XMStoreFloat3(&front, Front);
    //�����_������x�N�g�������Ɉ�苗�����ꂽ�J�������_�����߂�
    DirectX::XMFLOAT3 eye;
    eye.x = target.x + range * -front.x;
    eye.y = target.y + range * -front.y;
    eye.z = target.z + range * -front.z;

    Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
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
