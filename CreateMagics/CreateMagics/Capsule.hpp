#pragma once
#include "ICollider.hpp"

using namespace std;

class CapsuleCollider : public ICollider
{
private:

	// �v�Z�֘A
	const float EPSILON = 1e-8f;	// �덷�͈́i�����ɂ�����_�j
	const float MIN_VALUE = 0.0f;	// �ŏ��l
	const float MAX_VALUE = 1.0f;	// �ŏ��l

	// �`��֘A
	const int DIVNUM = 32;								// �|���S���ׂ̍���
	const int DEBUG_DIFCOLOR = GetColor(255, 255, 255);	// �f�B�q���[�Y�J���[
	const int DEBUG_SPCCOLOR = GetColor(255, 0, 0);		// �X�y�L�����J���[

	float m_halfHeight;		// �����̍���
	float m_radius;			// ���a

	VECTOR m_p0 = VGet(0, 0, 0);	// ���[�_
	VECTOR m_p1 = VGet(0, 0, 0);	// ��[�_

	float m_worldRadius = 0.5f;
public:

	/// @brief �C���X�^���X
	/// @param halfHeight �����̍���
	/// @param radius ���a
	CapsuleCollider(float halfHeight, float radius);

	/// @brief ���[���h�Ԋ҂̓���
	/// @param position �ʒu
	/// @param rotate ��]��
	/// @param scale �g�嗦
	void SetWorld(const VECTOR& position, const VECTOR& rotate, const VECTOR& scale) override;

	/// @brief �Փ˔���
	/// @param other ���R���C�_�[
	/// @return �Փ˔���
	bool Intersects(const ICollider& other) const override;

	/// @brief �`��
	void Draw() const override;

	// ----- �Q�Ɨp�֐� -----
	VECTOR GetP0() const;		// ���[�_

	VECTOR GetP1() const;		// ��[�_
	
	float GetRadius() const;	// ���a

private:

	// ------ �����֐� -----

	/// @brief ������x�N�g�����I�C���[�p��]����v�Z
	/// @param rotate ��]��
	/// @return ������x�N�g��
	VECTOR CalcUpDirFromEulerXYZ(const VECTOR& rotate);

	/// @brief ��̐����̍ŋߓ_�Ԃ̋���
	/// @param p0 �����̏I�_
	/// @param p1 �����̎n�_
	/// @param q0 ������̐����̏I�_
	/// @param q1 ������̐����̎n�_
	/// @return ��̐����̍ŋߓ_�Ԃ̋���
	float SegmentSegmentDistSq(const VECTOR& p0, const VECTOR& p1, const VECTOR& q0, const VECTOR& q1 ) const;

	/// @brief �̈�v�Z
	/// @param value �Ώےl
	/// @param min �ŏ��l
	/// @param max �ő�l
	/// @return ���ۂ̒l
	float Clamp(float value, float min, float max) const;

};
