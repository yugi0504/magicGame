#pragma once
#include "DxLib.h"
#include "ICollider.hpp"
#include "Capsule.hpp"
#include "BulletOwner.hpp"
#include <memory>

using namespace std;


class Bullet
{
public:


private:

	static constexpr float EPSILON = 1e-8f;

	VECTOR	m_position	= VGet(0, 0, 0);	// 位置
	VECTOR	m_velocity	= VGet(0, 0, 0);	// 速度
	BulletOwner	m_owner		= BulletOwner::Player;	// 所有者
	int		m_damage	= 0;				// ダメージ量
	bool	m_alive		= false;			// 生存フラグ
	float	m_lifeTime	= 0.0f;				// 寿命（秒）
	unique_ptr<ICollider> m_collider;		// 当たり判定

public:

	Bullet();
	~Bullet() = default;

	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;

	Bullet(Bullet&&) noexcept = default;
	Bullet& operator=(Bullet&&) noexcept = default;

	//
	void Spawn(const VECTOR& pos, const VECTOR& dir, float speed, int damage, BulletOwner owner, float lifeTime = 5.0f);

	void Update(float deltaTime);

	void Draw() const;

	bool IsAlive() const;
	void Kill();

	ICollider* GetCollider() const;
	BulletOwner GetOwner() const;
	int GetDamage() const;
	const VECTOR& GetPosition() const;
};