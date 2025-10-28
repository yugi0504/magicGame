#pragma once
#include "ICollider.hpp"

class CapsuleCollider : public ICollider
{
private:

	float m_halfHeight;		// �����̍���
	float m_radius;			// ���a

	VECTOR m_p0 = VGet(0, 0, 0);	// �_
	VECTOR m_p1 = VGet(0, 0, 0);	// �_
public:
	void SetWorld(const VECTOR& position, const VECTOR& rotate, const VECTOR& scale) override;
	bool Intersects(const ICollider& other) const override;
};
