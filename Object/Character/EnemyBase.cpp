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
	CharacterBase::Draw(camera_pos);

#ifdef _DEBUG
	//// デバック時のみ索敵範囲を描画
	//m_search_range.Draw(camera_pos);
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