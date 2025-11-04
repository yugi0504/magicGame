#pragma once
#include "DxLib.h"

class ICharacter
{
	virtual ~ICharacter() = default;

	virtual void Update() = 0;

	virtual void Draw() = 0;
};