#pragma once
#include <DirectXMath.h>

//�J�����R���g���[���[
class CameraController
{
public:
    CameraController() {}
    ~CameraController() {}
    //�X�V����
    void Update(float elapsedTime);             // �ʏ�
    void FpsUpdate(float elapsedTime);          // FPS
    void ViewUpdate(float elapsedTime);         // View
    void SpectatorUpdate(float elapsedTime);    // Spectator

    // �Z�b�^�[
    void SetEye(DirectX::XMFLOAT3 eye_) { eye = eye_; }                         // �|�W�V����
    void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }  // �����_
    void SetAngle(DirectX::XMFLOAT3 angle_) { angle = angle_; }                 // �A���O��
    void SetCurrentAngle(DirectX::XMFLOAT3 angle_) { currentangle = angle_; }   // �A���O���i�u�ԁj
    void SetFov(float fov_) { fov = fov_; }                                     // ����p

    // �Q�b�^�[
    const DirectX::XMFLOAT3& GetEye() const { return eye; }             // �|�W�V����
    const DirectX::XMFLOAT3& GetAngle() const { return angle; }             // �A���O��
    const DirectX::XMFLOAT3& GetTarget() const { return cameraTarget; }     // �����_
    float GetFov() { return fov; }                                          // ����p
    const DirectX::XMFLOAT3& GetForward() const { return cameraForward; }   // �p���i�O���j
    const DirectX::XMFLOAT3& GetUp() const { return cameraUp; }             // �p���i����j

    //�f�o�b�O�pGUI
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