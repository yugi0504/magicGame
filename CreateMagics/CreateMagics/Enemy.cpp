#include "Enemy.hpp"

Enemy::Enemy()
{
	m_status.SetMax(50, 0);
}

void Enemy::Initialize(
	const VECTOR& startPos,
	float moveSpeed,
	float chaseRange,
	float attackRange,
	float attackInterval)
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

	VECTOR dir;

	if (distSq > 1e-8f)
	{
		dir = VNorm(diff);
	}
	else
	{
		dir = VGet(0, 0, 0);
	}

	if (distSq > attackR2 && distSq < chaseR2)
	{
		VECTOR move = VScale(dir, m_moveSpeed * deltaTime);
		myPos = VAdd(myPos, move);
		SetPosition(myPos);
	}
	else
	{
		// ‹ß‹——£”»’è

	}


	m_attackTimer -= deltaTime;
	if (m_attackTimer <= 0.0f)
	{
		if (distSq <= attackR2)
		{
			ShootAtPlayer();
		}
		m_attackTimer = m_attackInterval;
	}


}

void Enemy::ShootAtPlayer()
{
	if (!m_player || !m_bullets) return;

	VECTOR myPos = GetPosition();
	VECTOR plPos = m_player->GetPosition();

	VECTOR dir = VSub(plPos, myPos);

	if (VSquareSize(dir) <= 1e-8f)
	{
		dir = VGet(0, 0, 1);
	}
	else
	{
		dir = VNorm(dir);
	}

	Bullet b;

	b.Spawn(myPos, dir, 15.0f, 3, BulletOwner::Enemy, 5.0f);

	m_bullets->push_back(b);
}