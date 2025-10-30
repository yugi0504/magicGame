#pragma once
#include "ICollider.hpp"

using namespace std;

class CapsuleCollider : public ICollider
{
private:

	// 計算関連
	const float EPSILON = 1e-8f;	// 誤差範囲（線分における点）
	const float MIN_VALUE = 0.0f;	// 最小値
	const float MAX_VALUE = 1.0f;	// 最小値

	// 描画関連
	const int DIVNUM = 32;								// ポリゴンの細かさ
	const int DEBUG_DIFCOLOR = GetColor(255, 255, 255);	// ディヒューズカラー
	const int DEBUG_SPCCOLOR = GetColor(255, 0, 0);		// スペキュラカラー

	float m_halfHeight;		// 半分の高さ
	float m_radius;			// 半径

	VECTOR m_p0 = VGet(0, 0, 0);	// 下端点
	VECTOR m_p1 = VGet(0, 0, 0);	// 上端点

	float m_worldRadius = 0.5f;
public:

	/// @brief インスタンス
	/// @param halfHeight 半分の高さ
	/// @param radius 半径
	CapsuleCollider(float halfHeight, float radius);

	/// @brief ワールド返還の同期
	/// @param position 位置
	/// @param rotate 回転率
	/// @param scale 拡大率
	void SetWorld(const VECTOR& position, const VECTOR& rotate, const VECTOR& scale) override;

	/// @brief 衝突判定
	/// @param other 他コライダー
	/// @return 衝突判定
	bool Intersects(const ICollider& other) const override;

	/// @brief 描画
	void Draw() const override;

	// ----- 参照用関数 -----
	VECTOR GetP0() const;		// 下端点

	VECTOR GetP1() const;		// 上端点
	
	float GetRadius() const;	// 半径

private:

	// ------ 内部関数 -----

	/// @brief 上方向ベクトルをオイラー角回転から計算
	/// @param rotate 回転率
	/// @return 上方向ベクトル
	VECTOR CalcUpDirFromEulerXYZ(const VECTOR& rotate);

	/// @brief 二つの線分の最近点間の距離
	/// @param p0 線分の終点
	/// @param p1 線分の始点
	/// @param q0 もう一つの線分の終点
	/// @param q1 もう一つの線分の始点
	/// @return 二つの線分の最近点間の距離
	float SegmentSegmentDistSq(const VECTOR& p0, const VECTOR& p1, const VECTOR& q0, const VECTOR& q1 ) const;

	/// @brief 領域計算
	/// @param value 対象値
	/// @param min 最小値
	/// @param max 最大値
	/// @return 実際の値
	float Clamp(float value, float min, float max) const;

};
