#pragma once
#include "DxLib.h"
#include "ICollider.hpp"
#include <memory>

using namespace std;

struct WorldTRS
{
	VECTOR position = VGet(0, 0, 0);
	VECTOR rotate = VGet(0, 0, 0);
	VECTOR scale = VGet(1, 1, 1);
};

class Character
{
protected:
	WorldTRS m_trs;
	unique_ptr<ICollider> m_collider;
	Status m_status;
};