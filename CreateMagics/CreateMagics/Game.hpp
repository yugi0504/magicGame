#pragma once
#include "DxLib.h"
#include <vector>
#include "Camera.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Time.hpp"

using namespace std;

class GameManager 
{
private:

	bool m_isRunning = false;

	Camera m_camera;
	Player m_player;
	vector<Bullet> m_bullets;



public:
	GameManager() = default;

	bool Initialize();
	void Run();
	void Finalize();

private:
	void Update(float deltaTime);
	void Draw();

	void UpdateBullets(float deltaTime);
	void CheckBulletHit();

};