#pragma once
#include <algorithm>

using namespace std;

class Status
{
	int m_hp = 100, m_hpMax = 100;
	int m_mp = 50 , m_mpMax = 50;
	float m_iframe = 0.0f;

public:

	void Update(float deltaTime);
	bool IsInvincible() const;
	void SetIFrame(float second);

	bool Damage(int value);
	void Heal(int value);
	bool UseMP(int value);
	void RecoverMP(int value);

	void SetMax(int hpMax, int mpMax);

	int GetHP() const;
	int GetMP() const;
	int GetHPMax() const;
	int GetMPMax() const;

};