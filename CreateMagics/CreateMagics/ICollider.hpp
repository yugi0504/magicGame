#pragma once
#include "DxLib.h"

/// <summary>
/// Collider Interface
/// </summary>
class ICollider
{
public:

	virtual ~ICollider() = default;
	/// <summary>
	/// ���[���h�ϊ��̓���
	/// </summary>
	/// <param name="position">�ʒu</param>
	/// <param name="rotate">��]��</param>
	/// <param name="scale">�g�嗦</param>
	virtual void SetWorld(const VECTOR& position, const VECTOR& rotate, const VECTOR& scale) = 0;
	/// <summary>
	/// ���R���C�_�[�Ƃ̓����蔻��
	/// </summary>
	/// <param name="other">���R���C�_�[</param>
	/// <returns>�Փ˂�����</returns>
	virtual bool Intersects(const ICollider& other) const = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() const = 0;
};