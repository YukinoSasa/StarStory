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
	m_Handle(-1), m_HandleWidth(-1), m_HandleHeight(-1), m_IsRight(true), m_Pos(0, 0), m_Move(0, 0), m_IsGround(false), m_Rect()
{

}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Init()
{
	GetGraphSize(m_Handle, &m_HandleWidth, &m_HandleHeight);
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

	// 矩形の端をセット
	m_Rect.SetEdges(m_Pos.m_x, m_Pos.m_y, static_cast<float>(m_HandleWidth), static_cast<float>(m_HandleHeight));
}

void CharacterBase::Draw()
{
	// 画像描画用の座標
	float drawX = m_Pos.m_x - static_cast<float>(m_HandleWidth / 2);
	float drawY = m_Pos.m_y - static_cast<float>(m_HandleHeight / 2);

	// キャラクターの向きによって画像を反転
	if (m_IsRight)
	{
		DrawGraphF(drawX, drawY, m_Handle, true);
	}
	else
	{
		DrawTurnGraphF(drawX, drawY, m_Handle, true);
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
