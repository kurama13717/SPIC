#pragma once

#include<d3d11.h>
#include<DirectXMath.h>
#include "PerlinNoise.h"
using namespace DirectX;

#include "Graphics/Graphics.h"

const LONG SCREEN_WIDTH = 1280;
const LONG SCREEN_HEIGHT = 720;
class Shake
{
public:
    void SetShake(float set_timer, float max_position, float max_angle);
    void ShakeUpdate(float elapsedTime);
    void SetMaxShakePosition(float position) { max_shake_positon = position; }
    void SetMaxShakeAngle(float angle) { max_shake_angle = angle; }
    float GetTimer() { return timer; }
    bool IsShake() { return shake_bool; }
    XMMATRIX GetShake() { return data; }
    static Shake& Instance()
    {
        static Shake camera;
        return camera;
    }
private:
    PerlinNoise pn;
    XMMATRIX data{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    float max_shake_positon  = 5.0f;
    float max_shake_angle = 8.0f;
    float seed = 0;
    float seed_shifting_factor = 3.00f;
    bool shake_bool = false;
    float timer = 0.0f;
    float max_timer = 0.0f;
    Graphics& graphics = Graphics::Instance();
};