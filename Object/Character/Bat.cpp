#include <DxLib.h>
#include "Bat.h"

namespace
{
	// 索敵範囲
	float search_range_width = 320.0f;
	float search_range_height = 320.0f;

	// 移動速度
	float MOVE_SPEED = 2.0f;
}

Bat::Bat(EnemyData enemy_data)
	:EnemyBase(enemy_data), m_animation_frame(0), m_animation_timer(0)
{
	LoadDivGraph(enemy_data.m_file_pass.c_str(), 9, 9, 1, 64, 64, m_handle_array);
	//LoadDivGraph("Data/bat_idle", 3, 3, 1, 64, 64, m_idle_handle_array);
	//m_current_state = BatState::Idle;

	// 初期位置を保存
	m_init_pos = m_pos;
}

Bat::~Bat()
{
	for (int i = 0; i < sizeof(m_handle_array) / sizeof(m_handle_array[0]); i++)
	{
		DeleteGraph(m_handle_array[i]);
	}
}

void Bat::Init()
{
	EnemyBase::Init();

	// 当たり判定サイズ
	m_collision_width = 46.0f;
	m_collision_height = 50.0f;

	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);

	m_search_range.CalculateEdges(m_pos.x, m_pos.y, search_range_width, search_range_height);
}

void Bat::Update()
{
	// 索敵範囲にプレイヤーがいるときプレイヤーを追跡する
	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
	m_search_range.CalculateEdges(m_pos.x, m_pos.y, search_range_width, search_range_height);

	m_handle = m_handle_array[m_animation_frame];

	m_animation_timer++;
	if (m_animation_timer >= 5)
	{
		UpdateAnimation();
		m_animation_timer = 0;
	}
}

void Bat::TrackPlayer(Vec2 player_pos)
{
	//// 状態の更新
	//m_current_state = BatState::Track;

	// 敵からプレイヤーの方向ベクトル
	Vec2 direction = player_pos - m_pos;

	// 方向ベクトルを正規化
	direction.Normalize();

	m_move = direction * MOVE_SPEED;

	// キャラクターの向きを設定
	if (m_move.x < 0.0f)
	{
		m_is_right = false;
	}
	else
	{
		m_is_right = true;
	}

	// 追跡
	m_pos += m_move;
}

void Bat::ReturnToInitPos()
{
	// 初期位置との方向ベクトルを計算
	Vec2 direction = m_init_pos - m_pos;

	// 方向ベクトルを正規化
	direction.Normalize();

	m_move = direction * MOVE_SPEED;

	// キャラクターの向きを設定
	if (m_move.x < 0.0f)
	{
		m_is_right = false;
	}
	else
	{
		m_is_right = true;
	}

	m_pos += m_move;
}

void Bat::UpdateAnimation()
{
	//switch (m_current_state)
	//{
	//case BatState::Idle:
	//{
	//	m_animation_frame++;
	//	if (m_animation_frame > 2)
	//	{
	//		m_animation_frame = 0;
	//	}

	//	break;
	//}
	//case BatState::Track:
	//{
	//	m_animation_frame++;
	//	if (m_animation_frame > 8)
	//	{
	//		m_animation_frame = 0;
	//	}

	//	break;
	//}
	//}

	m_animation_frame++;
	if (m_animation_frame > 8)
	{
		m_animation_frame = 0;
	}
}

void Bat::Draw(Vec2 camera_pos)
{
	EnemyBase::Draw(camera_pos);

	m_search_range.Draw(camera_pos);
}