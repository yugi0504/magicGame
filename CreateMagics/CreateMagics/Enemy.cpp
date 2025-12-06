#include "Enemy.hpp"

Enemy::Enemy()
{
	m_status.SetMax(50, 0);
}

void Enemy::Initialize(
	const VECTOR& startPos,
	float moveSpeed = 3.0f,
	float chaseRange = 30.0f,
	float attackRange = 15.0f,
	float attackInterval = 2.0f)
{
	SetPosition(startPos);

	m_moveSpeed = moveSpeed;
	m_chaseRange = chaseRange;
	m_attackRange = attackRange;
	m_attackInterval = attackInterval;
	m_attackTimer = 0.0f;

	const float halfHeight = 0.9f;
	const float radius = 0.35f;
	unique_ptr<ICollider> cap = make_unique<CapsuleCollider>(halfHeight, radius);
	SetCollider(move(cap));
}

bool Enemy::IsDead() const
{
	return (m_status.GetHP() <= 0);
}

void Enemy::Update(float deltaTime)
{
	if (IsDead())
	{
		// Ž€–SŽžˆ—

		return;
	}

	UpdateAI(deltaTime);

	Character::Update(deltaTime);
}

void Enemy::Draw() const
{
	if (IsDead())
	{
		// Ž€–SŽžˆ—

		return;
	}

	Character::Draw();
}

void Enemy::UpdateAI(float deltaTime)
{
	if (!m_player) return;

	VECTOR myPos = GetPosition();
	VECTOR plPos = m_player->GetPosition();

	VECTOR diff = VSub(plPos, myPos);
	diff.y = 0.0f;

	float distSq = VSquareSize(diff);
	float chaseR2 = m_chaseRange * m_chaseRange;
	float attackR2 = m_attackRange * m_attackRange;



}