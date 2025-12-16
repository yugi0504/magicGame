#include "bullet.hpp"

Bullet::Bullet()
{
	const float halfHeight = 0.05f;
	const float radius = 0.05f;
	m_collider = make_unique<CapsuleCollider>(halfHeight, radius);
}

void Bullet::Spawn(const VECTOR& pos, const VECTOR& dir, float speed, int damage, BulletOwner owner, float lifeTime)
{
	m_position = pos;
	VECTOR d = dir;

	if (VSquareSize(d) > EPSILON)
	{
		d = VNorm(d);
	}
	else
	{
		d = VGet(0, 0, 1);
	}

	m_velocity = VScale(d, speed);
	m_damage = damage;
	m_owner = owner;
	m_lifeTime = lifeTime;
	m_alive = true;

	if (m_collider)
	{
		VECTOR rot = VGet(0, 0, 0);
		VECTOR scale = VGet(1, 1, 1);
		m_collider->SetWorld(m_position, rot, scale);
	}
}

void Bullet::Update(float deltaTime)
{
	if (!m_alive) return;

	m_position = VAdd(m_position, VScale(m_velocity, deltaTime));

	m_lifeTime -= deltaTime;

	if (m_lifeTime = 0.0f)
	{
		m_alive = false;
	}

	if (m_collider)
	{
		VECTOR rot = VGet(0, 0, 0);
		VECTOR scale = VGet(1, 1, 1);
		m_collider->SetWorld(m_position, rot, scale);
	}
}

void Bullet::Draw() const
{
	if (!m_alive) return;

	if (m_collider)
	{
		m_collider->Draw();
	}
}

bool Bullet::IsAlive() const
{
	return m_alive;
}

void Bullet::Kill()
{
	m_alive = false;
}

ICollider* Bullet::GetCollider() const
{
	return m_collider.get();
}

BulletOwner Bullet::GetOwner() const
{
	return m_owner;
}

int Bullet::GetDamage()const
{
	return m_damage;
}

const VECTOR& Bullet::GetPosition() const
{
	return m_position;
}
