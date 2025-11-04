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

bool CapsuleCollider::ComputePenetrationCapsuleCapsule(const CapsuleCollider& other, VECTOR& outNormal, float& outDepth, VECTOR& outPointA, VECTOR& outPointB) const
{
	float s = MIN_VALUE, t = MIN_VALUE;
	VECTOR cpA, cpB;

	const float distSq = SegmentSegmentClosestPoints(m_p0, m_p1, other.m_p0, other.m_p1, s, t, cpA, cpB);

	const float rSum = m_worldRadius + other.m_worldRadius;

	// 実距離
	float dist = sqrtf(max(distSq, MIN_VALUE));

	if (dist >= rSum)
	{
		// 貫通していない
		outDepth = MIN_VALUE;
		outNormal = VGet(0, 0, 0);
		outPointA = cpA;
		outPointB = cpB;
		return false;
	}

	// 法線方向
	VECTOR n = VSub(cpB, cpA);
	float nLenSq = VSquareSize(n);

	if (nLenSq <= EPSILON)
	{
		VECTOR aAxis = VSub(m_p1, m_p0);
		VECTOR bAxis = VSub(other.m_p1, other.m_p0);

		// 軸の差分方向
		n = VSub(bAxis, aAxis);

		if (VSquareSize(n) <= EPSILON)
		{
			// ｙ軸に退避
			n = VGet(0, 1, 0);
		}

		n = VNorm(n);
		dist = MIN_VALUE;	// ほぼ一致
	}
	else
	{
		n = VScale(n, MAX_VALUE / sqrtf(nLenSq));
	}

	// 重なり量
	const float depth = rSum - dist;

	outNormal = n;		// 単位法線
	outDepth = depth;	// 正の重なり
	outPointA = cpA;
	outPointB = cpB;

	return true;
}

// ----- 参照用関数 -----

VECTOR CapsuleCollider::GetP0() const
{
	return m_p0;
}

VECTOR CapsuleCollider::GetP1() const
{
	return m_p1;
}

float CapsuleCollider::GetRadius() const
{
	return m_worldRadius;
}


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

float CapsuleCollider::SegmentSegmentClosestPoints(const VECTOR& p0, const VECTOR& p1, const VECTOR& q0, const VECTOR& q1, float& outS, float& outT, VECTOR& outClosestP, VECTOR& outClosestQ) const
{
	const VECTOR d1 = VSub(p1, p0);
	const VECTOR d2 = VSub(q1, q0);
	const VECTOR r = VSub(p0, q0);

	const float a = VDot(d1, d1);
	const float e = VDot(d2, d2);
	const float f = VDot(d2, r);

	float s, t;

	if (a <= EPSILON && e <= EPSILON)
	{
		// 両方とも「点」
		outClosestP = p0;
		outClosestQ = q0;
		outS = 0.0f; outT = 0.0f;
		return VSquareSize(VSub(outClosestP, outClosestQ));
	}

	if (a <= EPSILON)
	{
		// pが点
		s = 0.0f;
		t = Clamp(f / e, 0.0f, 1.0f);
	}
	else
	{
		const float c = VDot(d1, r);
		if (e <= EPSILON)
		{
			// qが点
			t = 0.0f;
			s = Clamp(-c / a, 0.0f, 1.0f);
		}
		else
		{
			const float b = VDot(d1, d2);
			const float denom = a * e - b * b;

			if (fabsf(denom) > EPSILON)
			{
				s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else
			{
				// ほぼ平行
				s = 0.0f;
			}

			t = (b * s + f) / e;

			if (t < 0.0f)
			{
				t = 0.0f;
				s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else if (t > 1.0f)
			{
				t = 1.0f;
				s = Clamp((b - c) / a, 0.0f, 1.0f);
			}
		}
	}

	outClosestP = VAdd(p0, VScale(d1, s));
	outClosestQ = VAdd(q0, VScale(d2, t));
	outS = s; outT = t;
	return VSquareSize(VSub(outClosestP, outClosestQ));
}

float CapsuleCollider::Clamp(float value, float min, float max) const
{
	return (value < min ? min : ((value > max) ? max : value));
}