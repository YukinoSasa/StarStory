#include <DxLib.h>
#include "../../GameConst.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(EnemyData enemy_data)
	:m_animation_elements(0), m_animation_update_frame(0), m_search_range()
{
	m_pos = enemy_data.m_spawn_pos;
	m_handle_width = enemy_data.m_size;
	m_handle_height = enemy_data.m_size;
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Init()
{
	CharacterBase::Init();
}

void EnemyBase::Update()
{
	// アニメーションの更新
	m_animation_timer++;

	if (m_animation_timer >= m_animation_update_frame)
	{
		UpdateAnimation();
		m_animation_timer = 0;
	}
}

void EnemyBase::Draw(Vec2 camera_pos)
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

void EnemyBase::TrackPlayer(Vec2 player_pos)
{

}

void EnemyBase::ReturnToInitPos()
{

}

void EnemyBase::UpdateAnimation()
{
	m_animation_frame++;

	if (m_animation_frame > m_animation_elements - 1)
	{
		m_animation_frame = 0;
	}

}