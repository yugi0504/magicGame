#include "Capsule.hpp"

CapsuleCollider::CapsuleCollider(float halfHeight, float radius)
	:m_halfHeight(halfHeight),m_radius(radius){ }

void CapsuleCollider::SetWorld(const VECTOR& position, const VECTOR& rotate, const VECTOR& scale)
{

	// 軸方向を取得
	const VECTOR up = CalcUpDirFromEulerXYZ(rotate);

	// ワールド軸長
	const float halfLenWorld = m_halfHeight * fabs(scale.y);

	// 半径のスケール
	const float radiusScale = max(fabs(scale.x), fabs(scale.z));
	m_worldRadius = m_radius * radiusScale;

	// 端点を計算
	m_p0 = VSub(position, VScale(up, halfLenWorld));
	m_p1 = VAdd(position, VScale(up, halfLenWorld));
}

bool CapsuleCollider::Intersects(const ICollider& other) const
{

	const auto* cap = dynamic_cast<const CapsuleCollider*>(&other);
	if (!cap) return false;

	const float distSq = SegmentSegmentDistSq(m_p0, m_p1, cap->m_p0, cap->m_p1);

	const float r = m_worldRadius + cap->m_worldRadius;

	return distSq <= (r * r);
}

void CapsuleCollider::Draw() const
{
	DrawCapsule3D(m_p0, m_p1, m_worldRadius, DIVNUM, DEBUG_DIFCOLOR, DEBUG_SPCCOLOR,FALSE);
}

// ----- 参照用関数 -----


// ----- 内部関数 -----

VECTOR CapsuleCollider::CalcUpDirFromEulerXYZ(const VECTOR& rotate)
{
	MATRIX rx = MGetRotX(rotate.x);
	MATRIX ry = MGetRotY(rotate.y);
	MATRIX rz = MGetRotZ(rotate.z);

	MATRIX m = MMult(rx, MMult(ry, rz));

	VECTOR upLocal = VGet(0, 1, 0);
	VECTOR upWorld = VTransform(upLocal, m);

	if (VSquareSize(upWorld) > EPSILON)	upWorld = VNorm(upWorld);
	else							upWorld = upLocal;

	return upWorld;
}

float CapsuleCollider::SegmentSegmentDistSq(const VECTOR& p0, const VECTOR& p1, const VECTOR& q0, const VECTOR& q1) const
{
	const VECTOR d1 = VSub(p1, p0);
	const VECTOR d2 = VSub(q1, q0);
	const VECTOR r  = VSub(p0, q0);

	const float a = VDot(d1, d1);
	const float e = VDot(d2, d2);
	const float f = VDot(d2, r);

	float s, t;

	// 両方が点の場合
	if (a <= EPSILON && e <= EPSILON)
	{
		return VSquareSize(VSub(p0, q0));
	}

	// pが点の場合
	if (a <= EPSILON)
	{
		s = MIN_VALUE;
		t = Clamp(f / e, MIN_VALUE, MAX_VALUE);
	}
	else
	{
		const float c = VDot(d1, r);

		// qが点の場合
		if (e <= EPSILON)
		{
			t = MIN_VALUE;
			s = Clamp(-c / a, MIN_VALUE, MAX_VALUE);
		}
		else
		{
			const float b = VDot(d1, d2);
			const float demon = a * e - b * b;

			if (demon != MIN_VALUE)
			{
				s = Clamp((b * f - c * e) / demon, MIN_VALUE, MAX_VALUE);
			}
			else
			{
				// 平行
				s = MIN_VALUE;
			}

			t = (b * s + f) / e;
			if (t < MIN_VALUE)
			{
				t = MIN_VALUE;
				s = Clamp(-c / a, MIN_VALUE, MAX_VALUE);
			}
			else if (t > MAX_VALUE)
			{
				t = MAX_VALUE;
				s = Clamp((b - c) / a, MIN_VALUE, MAX_VALUE);
			}
		}
	}

	VECTOR closestP = VAdd(p0, VScale(d1, s));
	VECTOR closestQ = VAdd(q0, VScale(d2, t));
	return VSquareSize(VSub(closestP, closestQ));
}

float CapsuleCollider::Clamp(float value, float min, float max) const
{
	return (value < min ? min : ((value > max) ? max : value));
}