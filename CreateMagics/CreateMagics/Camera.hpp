#pragma once
#include "DxLib.h"
#include <algorithm>
#include <cmath>

using namespace std;

class Camera
{
public:
	struct Settings {
		float mouseSensitivityRadPerPixel = DX_PI_F / 2.0f;	// 感度(回転ラジアン速度)
		float pitchLimit = DX_PI_F * 85.0f / 180.0f;		// ±85°
		float yawLimit = DX_PI_F * 175.0f / 180.0f;			// ±175°
		float distance = 12.0f;								// 三人称距離
		bool hideMouse = true;
	};

private:
	const float EPSILON = 1e-8f;

	VECTOR m_target = VGet(0, 0, 0);
	float m_yaw = 0.0f;
	float m_pitch = 0.0f;
	Settings m_cfg;

public:
	Camera() = default;
	explicit Camera(const Settings cfg);

	void InitializeMouseLock();

	void Update(float deltaTime);
	void ApplyToCamera() const;

	void SetTarget(const VECTOR& target);
	void SetAngle(float yaw, float pitch);
	void SetDistance(float distance);

	float GetYaw()const;
	float GetPitch() const;
	float GetDistance() const;
	VECTOR GetForward() const;
	VECTOR GetRight() const;

private:
	void ClampAngle();
};