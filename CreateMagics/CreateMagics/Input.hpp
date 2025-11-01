#pragma once
#include "DxLib.h"

class Input
{
public :
	static Input& GetInstance();		// シングルトンアクセス

	bool IsMoved_W() const;		// Wキー入力情報
	bool IsMoved_A() const;		// Aキー入力情報
	bool IsMoved_S() const;		// Sキー入力情報
	bool IsMoved_D() const;		// Dキー入力情報
};
