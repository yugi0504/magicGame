#pragma once
#include <memory>
#include "Character.hpp"
#include "Capsule.hpp"
#include "Camera.hpp"
#include "Move.hpp"

class Player : public Character
{
private:
	Move m_move;
	float m_moveSpeed;
	Camera* m_camera = nullptr;

public :

	Player();

	void Initialize(const VECTOR& starPos, float moveSpeed = 5.0f, float capsuleHalfHeight = 0.9f, float capsuleRadius = 0.35f);

	void Update(float deltaTime);

	void Draw() const;

	void AttachCamera(Camera* cam);

	void SetMoveSpeed(float speed);
	float GetMoveSpeed() const;

};