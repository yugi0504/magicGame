#include "Move.hpp"

Move::Move() :m_position(INIT_VECTOR), m_speed(0.5f){}

Move::Move(const VECTOR& startPos,float speed):m_position(startPos),m_speed(speed){}

void Move::PlayerUpdate(const VECTOR&forward, float deltaTime)
{
	VECTOR right = VCross(UP_VECTOR, forward);
	right = VNorm(right);

	VECTOR moveDir = INIT_VECTOR;

	if (Input::GetInstance().IsMoved_W())	moveDir = VAdd(moveDir, forward);
	if (Input::GetInstance().IsMoved_S())	moveDir = VSub(moveDir, forward);
	if (Input::GetInstance().IsMoved_A())	moveDir = VSub(moveDir, right);
	if (Input::GetInstance().IsMoved_D())	moveDir = VAdd(moveDir, right);

	if (VSquareSize(moveDir) > EPSILON)
	{
		moveDir = VNorm(moveDir);
		m_position = VAdd(m_position, VScale(moveDir, m_speed * deltaTime));
	}
}

VECTOR Move::GetPosition() const
{
	return m_position;
}

void Move::SetPosition(const VECTOR& position)
{
	m_position = position;
}

void Move::SetSpeed(const float speed)
{
	m_speed = speed;
}