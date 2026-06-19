#include <DxLib.h>
#include "CharacterBase.h"

namespace
{
	// キャラクターが受ける重力
	constexpr float K_GRAVITY = 1.0f;

	// 床のy座標
	constexpr float K_GROUND = 500.0f;
}

CharacterBase::CharacterBase() :
	m_Handle(-1), m_Pos(0, 0), m_Move(0, 0), m_IsGround(false)
{
	
}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Init()
{

}

void CharacterBase::Update()
{
	Gravity();

	// 床に接地した場合、キャラクターのy座標を床に固定
	if (m_Pos.m_y > K_GROUND)
	{
		m_Pos.m_y = K_GROUND;
		m_Move.m_y = 0.0f;

		m_IsGround = true;
	}
}

void CharacterBase::Draw()
{
	DrawGraphF(m_Pos.m_x, m_Pos.m_y, m_Handle, true);
}

void CharacterBase::Gravity()
{
	m_Move.m_y += K_GRAVITY;
}
