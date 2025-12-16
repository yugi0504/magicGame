#pragma once
#include "Character.hpp"
#include "bullet.hpp"
#include "Player.hpp"
#include <vector>

using namespace std;

class Enemy : public Character
{
private:
	Player* m_player = nullptr;
	vector<Bullet>* m_bullets = nullptr;

	float m_moveSpeed;
	float m_chaseRange;
	float m_attackRange;
	float m_attackInterval;
	float m_attackTimer;
	

public:

	Enemy();

	void Initialize(
		const VECTOR& startPos, 
		float moveSpeed = 3.0f,
		float chaseRange = 30.0f,
		float attackRange = 15.0f,
		float attackInterval = 2.0f);

	void SetPlayer(Player* player);
	void SetBulletList(vector<Bullet>* bullets);

	void Update(float deltaTime) override;
	void Draw() const override;

	bool IsDead() const;

private:
	
	void UpdateAI(float deltaTime);
	void ShootAtPlayer();

};