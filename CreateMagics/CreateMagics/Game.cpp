#include "Game.hpp"

bool GameManager::Initialize()
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	
	if (DxLib_Init() == -1) return false;

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	Camera::Settings camCfg;
	m_camera.SetSettings(camCfg);
	m_camera.InitializeMouseLock();
	m_camera.SetTarget(VGet(0, 0, 0));

	m_player.Initialize(VGet(0, 0, 0));
	m_player.AttachCamera(&m_camera);

	m_bullets.clear();

	m_isRunning = true;
	return true;
}

void GameManager::Run()
{
	while (m_isRunning && ProcessMessage() != 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 0)
	{
		Time::GetInstance().Update();
		float deltaTime = Time::GetInstance().DeltaTime();

		Update(deltaTime);
		Draw();
	}
}

void GameManager::Finalize()
{
	DxLib_End();
}

void GameManager::Update(float deltaTime)
{
	m_camera.Update(deltaTime);

	m_player.Update(deltaTime);

	UpdateBullets(deltaTime);
	CheckBulletHit();

	m_camera.SetTarget(m_player.GetPosition());
	m_camera.ApplyToCamera();
}