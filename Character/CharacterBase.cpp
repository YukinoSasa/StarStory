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
	m_handle(-1), m_handle_width(-1), m_handle_height(-1), m_is_right(true), m_pos(20, 0), m_move(0, 0), m_is_ground(false), m_rect()
{

}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Init()
{
	GetGraphSize(m_handle, &m_handle_width, &m_handle_height);
}

void CharacterBase::Update()
{
	//// 矩形の端をセット
	//m_Rect.SetEdges(m_Pos.m_x, m_Pos.m_y, static_cast<float>(m_HandleWidth), static_cast<float>(m_HandleHeight));

	Gravity();

	// 当たったマップチップの矩形
	Rect chipRect;
	CheckHitStage(chipRect);

	//// 床に接地した場合、キャラクターのy座標を床に固定
	//if (m_Pos.m_y > K_GROUND)
	//{
	//	m_Pos.m_y = K_GROUND;
	//	m_Move.m_y = 0.0f;

	//	m_IsGround = true;
	//}
}

void CharacterBase::Draw(Vec2 cameraPos)
{
	// キャラクターの左上の座標
	float drawX = m_pos.m_x - static_cast<float>(m_handle_width / 2);
	float drawY = m_pos.m_y - static_cast<float>(m_handle_height / 2);

	// キャラクターの描画位置の計算
	float screenX = drawX - cameraPos.m_x + 960.0f;
	float screenY = drawY - cameraPos.m_y + 540.0f;

	// キャラクターの向きによって画像を反転
	if (m_is_right)
	{
		DrawGraphF(screenX, screenY, m_handle, true);
	}
	else
	{
		DrawTurnGraphF(screenX, screenY, m_handle, true);
	}

#ifdef _DEBUG
	// デバック時のみ矩形を描画
	m_rect.Draw(cameraPos);
#endif
}

void CharacterBase::CheckHitStage(Rect& chipRect)
{
	// 横から当たったかチェック
	m_pos.m_x += m_move.m_x;
	// 横画面外に行けないようにする
	if (m_pos.m_x < 0.0f - static_cast<float>(m_handle_width / 2))
	{
		m_pos.m_x = 0;
	}
	else if (m_pos.m_x + static_cast<float>(m_handle_width / 2) > 1920.0f)
	{
		m_pos.m_x = 1920.0f;
	}

	// 矩形の端をセット
	m_rect.SetEdges(m_pos.m_x - 1.0f, m_pos.m_y - 1.0f, static_cast<float>(m_handle_width), static_cast<float>(m_handle_height));

	if (m_p_stage->IsCollision(m_rect, chipRect))
	{
		if (m_move.m_x > 0.0f)
		{
			m_pos.m_x = chipRect.GetLeftEdge() - m_handle_width / 2;
		}
		else if (m_move.m_x < 0.0f)
		{
			m_pos.m_x = chipRect.GetRightEdge() + m_handle_width / 2;
		}

		m_move.m_x = 0.0f;
	}

	// 縦から当たったかチェック
	m_pos.m_y += m_move.m_y;

	// 矩形の端をセット
	m_rect.SetEdges(m_pos.m_x - 1.0f, m_pos.m_y - 1.0f, static_cast<float>(m_handle_width), static_cast<float>(m_handle_height));

	if (m_p_stage->IsCollision(m_rect, chipRect))
	{
		if (m_move.m_y > 0.0f)
		{
			m_pos.m_y = chipRect.GetTopEdge() - m_handle_height / 2;
			m_move.m_y = 0.0f;
			m_is_ground = true;
		}
		else if (m_move.m_y < 0.0f)
		{
			m_pos.m_y = chipRect.GetBottomEdge() + m_handle_height / 2;
			m_move.m_y *= -1.0f;
		}
	}
}

void CharacterBase::Gravity()
{
	m_move.m_y += K_GRAVITY;
}
