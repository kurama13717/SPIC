#pragma once
#include <DirectXMath.h>

//カメラコントローラー
class CameraController
{
public:
    CameraController() {}
    ~CameraController() {}
    //更新処理
    void Update(float elapsedTime);             // 通常
    void FpsUpdate(float elapsedTime);          // FPS
    void ViewUpdate(float elapsedTime);         // View
    void SpectatorUpdate(float elapsedTime);    // Spectator

    // セッター
    void SetEye(DirectX::XMFLOAT3 eye_) { eye = eye_; }                         // ポジション
    void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }  // 注視点
    void SetAngle(DirectX::XMFLOAT3 angle_) { angle = angle_; }                 // アングル
    void SetCurrentAngle(DirectX::XMFLOAT3 angle_) { currentangle = angle_; }   // アングル（瞬間）
    void SetFov(float fov_) { fov = fov_; }                                     // 視野角

    // ゲッター
    const DirectX::XMFLOAT3& GetEye() const { return eye; }             // ポジション
    const DirectX::XMFLOAT3& GetAngle() const { return angle; }             // アングル
    const DirectX::XMFLOAT3& GetTarget() const { return cameraTarget; }     // 注視点
    float GetFov() { return fov; }                                          // 視野角
    const DirectX::XMFLOAT3& GetForward() const { return cameraForward; }   // 姿勢（前方）
    const DirectX::XMFLOAT3& GetUp() const { return cameraUp; }             // 姿勢（上方）

    //デバッグ用GUI
    void cameraDebugGUI();

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
    float range = 45.0f;
    float maxAngleX = DirectX::XMConvertToRadians(45);
    float minAngleX = DirectX::XMConvertToRadians(-45);
    float fov = 40;

    DirectX::XMVECTOR Front;
    DirectX::XMFLOAT3 front;

    bool cameraturn_r = false;
    bool cameraturn_l = false;
    DirectX::XMFLOAT3 currentangle = {0,0,0};
    float axisX = 0;

};