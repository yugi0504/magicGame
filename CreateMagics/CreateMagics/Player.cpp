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
	
}