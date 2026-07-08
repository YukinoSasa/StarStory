#include <DxLib.h>
#include "../GameConst.h"
#include "CharacterBase.h"
#include "../Stage/Stage.h"


namespace
{
	// キャラクターが受ける重力
	constexpr float GRAVITY = 0.3f;
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
	// 画像サイズを取得し、値を保存
	GetGraphSize(m_handle, &m_handle_width, &m_handle_height);
}

void CharacterBase::Update()
{
	Gravity();

	// 当たったマップチップの矩形
	Rect chip_rect;
	CheckHitStage(chip_rect);
}

void CharacterBase::Draw(Vec2 camera_pos)
{
	// キャラクター画像の左上の座標
	float draw_x = m_pos.x - m_handle_width * 0.5f;
	float draw_y = m_pos.y - m_handle_height * 0.5f;

	// キャラクター描画のスクリーン座標
	float screen_x = draw_x - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	float screen_y = draw_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	// キャラクターの向きによって画像を反転
	if (m_is_right)
	{
		DrawGraphF(screen_x, screen_y, m_handle, true);
	}
	else
	{
		DrawTurnGraphF(screen_x, screen_y, m_handle, true);
	}

#ifdef _DEBUG
	// デバック時のみ当たり判定の矩形を描画
	m_rect.Draw(camera_pos);
#endif
}

void CharacterBase::CheckHitStage(Rect& chip_rect)
{
	// 横から当たったかチェック
	m_pos.x += m_move.x;
	// 横画面外に行けないようにする
	if (m_pos.x < 0.0f - static_cast<float>(m_handle_width / 2))
	{
		m_pos.x = 0;
	}
	else if (m_pos.x + static_cast<float>(m_handle_width / 2) > static_cast<float>(Game::SCREEN_WIDTH))
	{
		m_pos.x = static_cast<float>(Game::SCREEN_WIDTH);
	}

	// 矩形の端をセット
	m_rect.CalculateEdges(m_pos.x - 1.0f, m_pos.y - 1.0f, static_cast<float>(m_handle_width), static_cast<float>(m_handle_height));

	if (m_p_stage->IsCollision(m_rect, chip_rect))
	{
		if (!chip_rect.GetIsObject())
		{
			return;
		}

		if (m_move.x > 0.0f)
		{
			m_pos.x = chip_rect.GetLeftEdge() - m_handle_width * 0.5f;
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chip_rect.GetRightEdge() + m_handle_width * 0.5f;
		}

		m_move.x = 0.0f;
	}

	// 縦から当たったかチェック
	m_pos.y += m_move.y;

	// 矩形の端をセット
	m_rect.CalculateEdges(m_pos.x - 1.0f, m_pos.y - 1.0f, static_cast<float>(m_handle_width), static_cast<float>(m_handle_height));

	if (m_p_stage->IsCollision(m_rect, chip_rect))
	{
		if (!chip_rect.GetIsObject())
		{
			return;
		}

		if (m_move.y > 0.0f)
		{
			m_pos.y = chip_rect.GetTopEdge() - m_handle_height * 0.5f;
			m_move.y = 0.0f;
			m_is_ground = true;
		}
		else if (m_move.y < 0.0f)
		{
			m_pos.y = chip_rect.GetBottomEdge() + m_handle_height * 0.5f;
			m_move.y *= -1.0f;
		}
	}
}

void CharacterBase::Gravity()
{
	m_move.y += GRAVITY;
}
