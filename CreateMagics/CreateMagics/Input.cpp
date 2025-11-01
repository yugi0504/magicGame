#include "Input.hpp"

Input& Input::GetInstance()
{
	static Input inst;
	return inst;
}

bool Input::IsMoved_W() const
{
	return CheckHitKey(KEY_INPUT_W);
}

bool Input::IsMoved_A() const
{
	return CheckHitKey(KEY_INPUT_A);
}

bool Input::IsMoved_S() const
{
	return CheckHitKey(KEY_INPUT_S);
}

bool Input::IsMoved_D() const
{
	return CheckHitKey(KEY_INPUT_D);
}