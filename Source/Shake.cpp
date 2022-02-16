#include"Shake.h"

void Shake::SetShake(float set_timer,float max_position, float max_angle)
{ 
	//start shake
	shake_bool = true;
	max_timer = set_timer;
	max_shake_positon = max_position;
	max_shake_angle = max_angle;
	timer = 0.0f;
}

void Shake::ShakeUpdate(float elapsedTime)
{
	if (max_timer > timer) {
		timer+= elapsedTime;
	}
	else {
		shake_bool = false;
		//reset position
		data = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	}
	if (shake_bool){
		seed += elapsedTime;
		const float shake = 2.0f 
			* static_cast<float>(pn.noise(seed * seed_shifting_factor, seed * seed_shifting_factor, 0)) - 1.0f;
		//A matrix in which the rotation matrix and transformation matrix are changed
		data = XMMatrixTranslation(
			shake * max_shake_positon / graphics.GetScreenWidth(), 
			shake * max_shake_positon / graphics.GetScreenHeight(),0)
			* XMMatrixRotationRollPitchYaw(0, 0, XMConvertToRadians(shake * max_shake_angle));
	}
}
