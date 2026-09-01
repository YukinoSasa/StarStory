#include <DxLib.h>
#include "../../GameConst.h"
#include "../../Stage/Stage.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase()
	:m_is_right(true), m_is_ground(false), m_is_alive(true), m_animation_frame(0), m_animation_timer(0)
{

}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Init()
{
	// 画像サイズを取得し、値を保存
	GetGraphSizeF(m_handle, &m_handle_width, &m_handle_height);
}

void CharacterBase::Update()
{
	Game::Gravity(m_move.y);
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
		DrawTurnGraphF(screen_x, screen_y, m_handle, true);
	}
	else
	{
		DrawGraphF(screen_x, screen_y, m_handle, true);
	}

#ifdef _DEBUG
	// デバック時のみコリジョンの矩形を描画
	m_rect.Draw(camera_pos);
#endif
}