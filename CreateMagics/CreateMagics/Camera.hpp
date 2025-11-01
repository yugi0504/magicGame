#pragma once
#include "DxLib.h"
#include <algorithm>
#include <cmath>

class Camera
{
public:
	struct Settings {
		float mouseSensitivityRadPerPixel = DX_PI_F / 2.0f;	// ���x(��]���W�A�����x)
		float pitchLimitRad = DX_PI_F * 85.0f / 180.0f;		// �}85��
		float yawLimitRad = DX_PI_F * 175.0f / 180.0f;		// �}175��
		float distance = 12.0f;								// �O�l�̋���
		bool hideMouse = true;
	};

private:
	VECTOR m_target = VGet(0, 0, 0);
	float m_yawRad = 0.0f;
	float m_pitchRad = 0.0f;
	Settings m_cfg;

public:
	Camera() = default;
	explicit Camera(const Settings cgf);
};