#pragma once
#include "DxLib.h"
#include "Input.hpp"

class Move
{
private:
	const VECTOR	UP_VECTOR		= VGet(0, 1, 0);	// 固定上方向VECTOR
	const VECTOR	INIT_VECTOR		= VGet(0, 0, 0);	// 初期VECTOR

	const float		EPSILON			= 1e-8f;			// 誤差

	VECTOR			m_position;							// 現在位置
	float			m_speed;							// 移動速度
public:

	// インスタンス
	Move();
	Move(const VECTOR& startPos, float speed);

	/// @brief プレイヤーの移動更新
	/// @param forward 正規化したカメラ前方向
	void	PlayerUpdate	(const VECTOR&forward, float deltaTime);

	// ----- 参照用関数 -------
	VECTOR	GetPosition		() const;
	
	// ----- 内部変更関数 -----
	void	SetPosition		(const VECTOR& position);
	void	SetSpeed		(const float speed);
};