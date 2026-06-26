#include <DxLib.h>
#include "CharacterBase.h"
#include "../Stage/Stage.h"


namespace
{
	// キャラクターが受ける重力
	constexpr float K_GRAVITY = 1.0f;

	// 床のy座標
	constexpr float K_GROUND = 800.0f;
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
	//// 矩形の端をセット
	//m_Rect.SetEdges(m_Pos.m_x, m_Pos.m_y, static_cast<float>(m_HandleWidth), static_cast<float>(m_HandleHeight));

	Gravity();

	// 当たったマップチップの矩形
	Rect chipRect;
	CheckHitMap(chipRect);

	// 床に接地した場合、キャラクターのy座標を床に固定
	if (m_Pos.m_y > K_GROUND)
	{
		m_Pos.m_y = K_GROUND;
		m_Move.m_y = 0.0f;

		m_IsGround = true;
	}
}

void CharacterBase::Draw(Vec2 cameraPos)
{
	// キャラクターの中心座標
	float drawX = m_Pos.m_x - static_cast<float>(m_HandleWidth / 2);
	float drawY = m_Pos.m_y - static_cast<float>(m_HandleHeight / 2);

	// キャラクターの描画位置の計算
	float screenX = drawX - cameraPos.m_x + 960.0f;
	float screenY = drawY - cameraPos.m_y + 540.0f;

	// キャラクターの向きによって画像を反転
	if (m_IsRight)
	{
		DrawGraphF(screenX, screenY, m_Handle, true);
	}
	else
	{
		DrawTurnGraphF(screenX, screenY, m_Handle, true);
	}

#ifdef _DEBUG
	// デバック時のみ矩形を描画
	m_Rect.Draw();
#endif
}

void CharacterBase::CheckHitMap(Rect& chipRect)
{
	// 横から当たったかチェック
	m_Pos.m_x += m_Move.m_x;

	// 矩形の端をセット
	m_Rect.SetEdges(m_Pos.m_x - 1.0f, m_Pos.m_y - 1.0f, static_cast<float>(m_HandleWidth), static_cast<float>(m_HandleHeight));

	if (m_pStage->IsCollision(m_Rect, chipRect))
	{
		if (m_Move.m_x > 0.0f)
		{
			m_Pos.m_x = chipRect.GetLeftEdge() - m_HandleWidth / 2;
		}
		else if (m_Move.m_x < 0.0f)
		{
			m_Pos.m_x = chipRect.GetRightEdge() + m_HandleWidth / 2;
		}

		m_Move.m_x = 0.0f;
	}

	// 縦から当たったかチェック
	m_Pos.m_y += m_Move.m_y;

	// 矩形の端をセット
	m_Rect.SetEdges(m_Pos.m_x - 1.0f, m_Pos.m_y - 1.0f, static_cast<float>(m_HandleWidth), static_cast<float>(m_HandleHeight));

	if (m_pStage->IsCollision(m_Rect, chipRect))
	{
		if (m_Move.m_y > 0.0f)
		{
			m_Pos.m_y = chipRect.GetTopEdge() - m_HandleHeight / 2;
			m_Move.m_y = 0.0f;
			m_IsGround = true;
		}
		else if (m_Move.m_y < 0.0f)
		{
			m_Pos.m_y = chipRect.GetBottomEdge() + m_HandleHeight / 2;
			m_Move.m_y *= -1.0f;
		}
	}
}

void CharacterBase::Gravity()
{
	m_Move.m_y += K_GRAVITY;
}
