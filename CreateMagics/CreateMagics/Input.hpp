#pragma once
#include "DxLib.h"

class Input
{
public :
	static Input& GetInstance();		// �V���O���g���A�N�Z�X

	bool IsMoved_W() const;		// W�L�[���͏��
	bool IsMoved_A() const;		// A�L�[���͏��
	bool IsMoved_S() const;		// S�L�[���͏��
	bool IsMoved_D() const;		// D�L�[���͏��
};
