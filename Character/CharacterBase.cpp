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
	m_Handle(-1), m_IsRight(true), m_Pos(0, 0), m_Move(0, 0), m_IsGround(false), m_Rect()
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
	// キャラクターの向きによって画像を反転
	if (m_IsRight)
	{
		DrawGraphF(m_Pos.m_x, m_Pos.m_y, m_Handle, true);
	}
	else
	{
		DrawTurnGraphF(m_Pos.m_x, m_Pos.m_y, m_Handle, true);
	}

#ifdef _DEBUG
	// デバック時のみ矩形を描画
	m_Rect.Draw();
#endif
}

void CharacterBase::Gravity()
{
	m_Move.m_y += K_GRAVITY;
}
