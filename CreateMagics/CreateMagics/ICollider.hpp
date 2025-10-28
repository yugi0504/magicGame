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
	/// ワールド変換の同期
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="rotate">回転率</param>
	/// <param name="scale">拡大率</param>
	virtual void SetWorld(const VECTOR& position, const VECTOR& rotate, const VECTOR& scale) = 0;
	/// <summary>
	/// 他コライダーとの当たり判定
	/// </summary>
	/// <param name="other">他コライダー</param>
	/// <returns>衝突したか</returns>
	virtual bool Intersects(const ICollider& other) const = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() const = 0;
};