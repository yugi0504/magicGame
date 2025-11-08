#pragma once
#include "DxLib.h"
#include "ICollider.hpp"
#include "Status.hpp"
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

public:
	virtual ~Character() = default;

	virtual void Update(float deltaTime);

	virtual void Draw() const;

	virtual bool OnHit(int damage, float invSecond = 0.2f);

	void SetPosition(const VECTOR& position);
	void SetRotation(const VECTOR& rotation);
	void SetScale(const VECTOR& scale);
	void SetCollider(unique_ptr<ICollider> collider);

	VECTOR GetPosition() const;
	VECTOR GetRotation() const;
	VECTOR GetScale() const;

	ICollider* GetCollider() const;

	Status& GetStatus();
	const Status& GetStatus() const;
};