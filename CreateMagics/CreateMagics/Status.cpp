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

void Status::RecoverMP(int value)
{
	m_mp = min(m_mpMax, m_mp + value);
}

void Status::SetMax(int hpMax, int mpMax)
{
	m_hpMax = hpMax;
	m_mpMax = mpMax;
	m_hp = hpMax;
	m_mp = mpMax;
}

int Status::GetHP() const
{
	return m_hp;
}

int Status::GetMP() const
{
	return m_mp;
}

int Status::GetHPMax() const
{
	return m_hpMax;
}

int Status::GetMPMax() const
{
	return m_mpMax;
}