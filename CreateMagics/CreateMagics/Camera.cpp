#include "Camera.hpp"

Camera::Camera(const Settings cfg):m_cfg(cfg){}

void Camera::InitializeMouseLock()
{
	if (m_cfg.hideMouse) SetMouseDispFlag(FALSE);
	int w, h;
	GetDrawScreenSize(&w, &h);
	SetMousePoint(w / 2, h / 2);
}

void Camera::Update(float deltaTime)
{
	int w, h;
	int mouseX, mouseY;

	// スクリーンの大きさを取得
	GetDrawScreenSize(&w, &h);
	// マウス位置取得
	GetMousePoint(&mouseX, &mouseY);

	// 画面中央
	int cx = w / 2;
	int cy = h / 2;

	// マウス差分
	int dx = mouseX - cx;
	int dy = mouseY - cy;

	// 画面中央に戻す
	SetMousePoint(cx, cy);

	// 回転速度を反映
	float addYaw   = +m_cfg.mouseSensitivityRadPerPixel * dx * deltaTime;
	float addPitch = -m_cfg.mouseSensitivityRadPerPixel * dy * deltaTime;

	m_yaw   += addYaw;
	m_pitch += addPitch;

	// リミット規制
	ClampAngle();
}

void Camera::ApplyToCamera() const
{
	VECTOR f = GetForward();
	VECTOR camPos = VSub(m_target, VScale(f, m_cfg.distance));
	SetCameraPositionAndTarget_UpVecY(camPos, m_target);
}

void Camera::SetTarget(const VECTOR & target)
{
	m_target = target;
}

void Camera::SetAngle(float yaw, float pitch)
{
	m_yaw   = yaw;
	m_pitch = pitch;
}

void Camera::SetDistance(float distance)
{
	m_cfg.distance = distance;
}

void Camera::SetTarget(const VECTOR& target)
{
	m_target = target;
}

float Camera::GetYaw() const
{
	return m_yaw;
}

float Camera::GetPitch() const
{
	return m_pitch;
}

float Camera::GetDistance() const
{
	return m_cfg.distance;
}

VECTOR Camera::GetForward() const
{
	float cy = cosf(m_yaw);
	float sy = sinf(m_yaw);
	float cp = cosf(m_pitch);
	float sp = sinf(m_pitch);

	VECTOR forward = VGet(sy * cp, sp, cy * cp);
	if (VSquareSize(forward) > EPSILON) return VNorm(forward);
	return VGet(0, 0, 1);
}

VECTOR Camera::GetRight() const
{
	VECTOR forward = GetForward();
	VECTOR right = VCross(VGet(0, 1, 0),forward);

	if (VSquareSize(right) > EPSILON) return VNorm(right);
	return VGet(1, 0, 0);
}

void Camera::ClampAngle()
{
	// ピッチの角度制限
	m_pitch = clamp(m_pitch, -m_cfg.pitchLimit, m_cfg.pitchLimit);

	// ヨーの角度制限
	m_yaw   = clamp(m_yaw, -m_cfg.yawLimit, m_cfg.yawLimit);
}