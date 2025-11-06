#include "Status.hpp"

void Status::Update(float deltaTime)
{
	if (m_iframe > 0.0f)
	{
		m_iframe = max(0.0f, m_iframe - deltaTime);
	}
}

bool Status::IsInvincible() const
{
	return m_iframe > 0.0f;
}

void Status::SetIFrame(float second)
{
	m_iframe = second;
}

bool Status::Damage(int value)
{
	if (IsInvincible())
	{
		return false;
	}

	m_hp = max(0, m_hp - value);
	return true;
}

void Status::Heal(int value)
{
	m_hp = min(m_hpMax, m_hp + value);
}

bool Status::UseMP(int value)
{
	if (m_mp < value)
	{
		return false;
	}
	m_mp -= max(0, m_mp - value);
	return true;
}