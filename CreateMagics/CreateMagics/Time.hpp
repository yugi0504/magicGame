#pragma once
#include "DxLib.h"

class Time
{
private:
	int m_prevMS = 0;
	float m_delta = 0.0f;

	Time() = default;

public:
	static Time& GetInstance();

	void Update();

	float DeltaTime() const;
};