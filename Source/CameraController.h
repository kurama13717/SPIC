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

    // FPS モード時更新処理
    void FpsUpdate(float elapsedTime);

    // View モード時処理
    void ViewUpdate(float elapsedTime);

    void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }
    void cameraDebugGUI();
    float GetFov() { return fov; }
    void SetFov(float fov_) { fov = fov_; }
    void SetAngle(DirectX::XMFLOAT3 angle_) { angle = angle_; }
    const DirectX::XMFLOAT3& GetAngle() const { return angle; }


    void SetEye(DirectX::XMFLOAT3 eye_) { eye = eye_; }

    const DirectX::XMFLOAT3& GetTarget() const { return cameraTarget; }
    const DirectX::XMFLOAT3& GetForward() const { return cameraForward; }
    const DirectX::XMFLOAT3& GetUp() const { return cameraUp; }

private:
    DirectX::XMFLOAT3 target = { 0,0,0 };
    DirectX::XMFLOAT3 angle = { 0,0,0 };
    DirectX::XMFLOAT2 sensitivity = { 1,1 };
    DirectX::XMFLOAT3 eye;
    DirectX::XMFLOAT3 cameraTarget;
    DirectX::XMFLOAT3 cameraForward;
    DirectX::XMFLOAT3 cameraUp;
    bool Inversion = false;
    int reverse = 1;
    float rollSpeed = DirectX::XMConvertToRadians(90);
    float range = 40.0f;
    float maxAngleX = DirectX::XMConvertToRadians(45);
    float minAngleX = DirectX::XMConvertToRadians(-45);
    float fov = 40;

    DirectX::XMVECTOR Front;
    DirectX::XMFLOAT3 front;

    bool CameraTurn_R = false;
    bool CameraTurn_L = false;
    DirectX::XMFLOAT3 NowAngle = {0,0,0};
};