#include "Character.hpp"

void Character::Update(float deltaTime)
{
	m_status.Update(deltaTime);
	if (m_collider)
		m_collider->SetWorld(m_trs.position, m_trs.rotate, m_trs.scale);
}

void Character::Draw() const
{
	if (m_collider)
		m_collider->Draw();
}

bool Character::OnHit(int damage, float invSecond)
{
	bool applied = m_status.Damage(damage);

	if (applied)
		m_status.SetIFrame(invSecond);

	return applied;
}

void Character::SetPosition(const VECTOR& position)
{
	m_trs.position = position;
	if (m_collider)
		m_collider->SetWorld(m_trs.position, m_trs.rotate, m_trs.scale);
}

void Character::SetRotation(const VECTOR& rotation)
{
	m_trs.rotate = rotation;
	if (m_collider)
		m_collider->SetWorld(m_trs.position, m_trs.rotate, m_trs.scale);
}

void Character::SetScale(const VECTOR& scale)
{
	m_trs.scale = scale;
	if (m_collider)
		m_collider->SetWorld(m_trs.position, m_trs.rotate, m_trs.scale);
}

void Character::SetCollider(unique_ptr<ICollider> collider)
{
	m_collider = move(collider);

	if (m_collider)
		m_collider->SetWorld(m_trs.position, m_trs.rotate, m_trs.scale);
}

VECTOR Character::GetPosition() const
{
	return m_trs.position;

}

VECTOR Character::GetRotation() const
{
	return m_trs.rotate;
}

VECTOR Character::GetScale() const
{
	return m_trs.scale;
}

ICollider* Character::GetCollider() const 
{
	return m_collider.get();
}

Status& Character::GetStatus()
{
	return m_status;
}

const Status& Character::GetStatus() const
{
	return m_status;
}