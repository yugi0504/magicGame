#include "Player.hpp"

Player::Player()
{
	m_status.SetMax(100, 50);
}

void Player::Initialize(const VECTOR& startPos, float moveSpeed, float capsuleHalfHeight, float capsuleRadius)
{
	m_move.SetPosition(startPos);
	m_move.SetSpeed(moveSpeed);
	m_moveSpeed = moveSpeed;

	SetPosition(startPos);

	auto cap = make_unique<CapsuleCollider>(capsuleHalfHeight, capsuleRadius);

	SetCollider(move(cap));
}

void Player::Update(float deltaTime)
{
	if (m_camera)
	{
		m_move.PlayerUpdate(*m_camera);
	}

	SetPosition(m_move.GetPosition());

	Character::Update(deltaTime);

	if (m_camera)
	{
		m_camera->SetTarget(GetPosition());
	}

	// ”í’eˆ—‚âUŒ‚ˆ—@’Ç‰Á‚Í‚±‚¿‚ç

}

void Player::Draw() const
{
	Character::Draw();
}

void Player::SetMoveSpeed(float speed)
{
	m_moveSpeed = speed;
	m_move.SetSpeed(speed);
}

float Player::GetMoveSpeed() const
{
	return m_moveSpeed;
}