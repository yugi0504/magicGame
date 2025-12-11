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

	Enemy enemy;
	enemy.Initialize(VGet(0, 0, 50));
	enemy.SetPlayer(&m_player);
	enemy.SetBulletList(&m_bullets);
	m_enemies.push_back(enemy);

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

void GameManager::Draw()
{
	ClearDrawScreen();

	m_player.Draw();
	for (auto& e :m_enemies ) e.Draw();
	for (auto& b : m_bullets) b.Draw();

	ScreenFlip();
}

void GameManager::UpdateBullets(float deltaTime)
{
	for (auto& b : m_bullets)
	{
		if (!b.IsAlive()) continue;
		b.Update(deltaTime);
	}

	m_bullets.erase(
		remove_if(m_bullets.begin(), m_bullets.end(),
			[](const Bullet& b) {return !b.IsAlive(); }),
			m_bullets.end());
}

void GameManager::CheckBulletHit()
{

	for(auto & b:m_bullets)
	{

	}

	for (auto& b : m_bullets)
	{
		if (!b.IsAlive()) continue;

		ICollider* bulletCol = b.GetCollider();

		if (!bulletCol) continue;

		if (b.GetOwner() == BulletOwner::Enemy)
		{
			ICollider* playerCol = m_player.GetCollider();

			if (!playerCol) continue;

			if (!m_player.GetStatus().IsInvincible() && playerCol->Intersects(*bulletCol))
			{
				m_player.OnHit(b.GetDamage(), 0.3f);
				b.Kill();
			}
		}
		else
		{
			for (auto& e : m_enemies)
			{
				ICollider* enemyCol = e.GetCollider();

				if (!enemyCol) continue;

				if (enemyCol->Intersects(*bulletCol))
				{
					e.OnHit(b.GetDamage(), 0.0f);
					b.Kill();
					break;
				}
			}

		}
	}
}