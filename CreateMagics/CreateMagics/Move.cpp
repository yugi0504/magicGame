#include "Move.hpp"

Move::Move() :m_position(INIT_VECTOR), m_speed(0.5f){}

Move::Move(const VECTOR& startPos,float speed):m_position(startPos),m_speed(speed){}

void Move::PlayerUpdate(const Camera& cam)
{
	VECTOR forward = cam.GetForward();
	VECTOR right = cam.GetRight();

	VECTOR moveDir = INIT_VECTOR;

	if (Input::GetInstance().IsMoved_W())	moveDir = VAdd(moveDir, forward);
	if (Input::GetInstance().IsMoved_S())	moveDir = VSub(moveDir, forward);
	if (Input::GetInstance().IsMoved_A())	moveDir = VSub(moveDir, right);
	if (Input::GetInstance().IsMoved_D())	moveDir = VAdd(moveDir, right);

	if (VSquareSize(moveDir) > EPSILON)
	{
		moveDir = VNorm(moveDir);
		m_position = VAdd(m_position, VScale(moveDir, m_speed * Time::GetInstance().DeltaTime()));
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