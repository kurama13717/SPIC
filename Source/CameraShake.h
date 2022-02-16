#pragma once

#include<d3d11.h>
#include<DirectXMath.h>
#include "PerlinNoise.h"
using namespace DirectX;

#include "Graphics/Graphics.h"

const LONG SCREEN_WIDTH = 1280;
const LONG SCREEN_HEIGHT = 720;
class CameraShake
{
public:
    CameraShake();
    void Shake(float elapsedTime);
    void SetMaxShakePosition(float position) { max_shake_positon = position; }
    void SetMaxShakeAngle(float angle) { max_shake_angle = angle; }
    //XMMATRIX GetData() { return data; }
    XMFLOAT4X4 GetData() { return data; }
    static CameraShake& Instance()
    {
        static CameraShake camera;
        return camera;
    }
private:
    PerlinNoise pn;
    //XMMATRIX data{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    XMFLOAT4X4 data{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    float max_shake_positon  = 5.0f;
    float max_shake_angle = 16.0f;
    float seed = 0;
    float seed_shifting_factor = 3.00f;
    

    Graphics& graphics = Graphics::Instance();
};