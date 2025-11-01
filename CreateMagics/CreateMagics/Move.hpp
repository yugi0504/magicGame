#pragma once
#include "DxLib.h"
#include "Input.hpp"

class Move
{
private:
	const VECTOR	UP_VECTOR		= VGet(0, 1, 0);	// �Œ�����VECTOR
	const VECTOR	INIT_VECTOR		= VGet(0, 0, 0);	// ����VECTOR

	const float		EPSILON			= 1e-8f;			// �덷

	VECTOR			m_position;							// ���݈ʒu
	float			m_speed;							// �ړ����x
public:

	// �C���X�^���X
	Move();
	Move(const VECTOR& startPos, float speed);

	/// @brief �v���C���[�̈ړ��X�V
	/// @param forward ���K�������J�����O����
	void	PlayerUpdate	(const VECTOR&forward, float deltaTime);

	// ----- �Q�Ɨp�֐� -------
	VECTOR	GetPosition		() const;
	
	// ----- �����ύX�֐� -----
	void	SetPosition		(const VECTOR& position);
	void	SetSpeed		(const float speed);
};