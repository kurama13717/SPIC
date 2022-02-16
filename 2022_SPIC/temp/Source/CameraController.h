#pragma once
#include <DirectXMath.h>

//カメラコントローラー
class CameraController
{
public:
    CameraController() {}
    ~CameraController() {}
    //更新処理
    void Update(float elapsedTime);
    void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }
    void cameraDebugGUI();
    float GetFov() { return fov; }
    void SetFov(float fov_) { fov = fov_; }
    void SetAngle(DirectX::XMFLOAT3 angle_) { angle = angle_; }
private:
    DirectX::XMFLOAT3 target = { 0,0,0 };
    DirectX::XMFLOAT3 angle = { 0,0,0 };
    DirectX::XMFLOAT2 sensitivity = { 1,1 };
    bool Inversion = false;
    int reverse = 1;
    float rollSpeed = DirectX::XMConvertToRadians(90);
    float range = 10.0f;
    float maxAngleX = DirectX::XMConvertToRadians(45);
    float minAngleX = DirectX::XMConvertToRadians(-45);
    float fov = 40;
};