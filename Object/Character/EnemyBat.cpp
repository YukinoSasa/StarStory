#include <DxLib.h>
#include "EnemyBat.h"

namespace
{
	// 移動速度
	float MOVE_SPEED = 1.5f;

	// 索敵範囲
	float SEARCH_RANGE_WIDTH = 450.0f;
	float SEARCH_RANGE_HEIGHT = 450.0f;
}

EnemyBat::EnemyBat(EnemyData enemy_data)
	:EnemyBase(enemy_data), m_is_tracking(false)
{
	LoadDivGraph(enemy_data.m_file_pass.c_str(), 9, 9, 1, 64, 64, m_handle_array);

	// 初期座標を保存
	m_init_pos = m_pos;
}

EnemyBat::~EnemyBat()
{
	for (int i = 0; i < sizeof(m_handle_array) / sizeof(m_handle_array[0]); i++)
	{
		DeleteGraph(m_handle_array[i]);
	}
}

void EnemyBat::Init()
{
	EnemyBase::Init();

	m_collision_width = 30.0f;
	m_collision_height = 30.0f;

	// アニメーション要素数を設定
	m_animation_elements = sizeof(m_handle_array) / sizeof(m_handle_array[0]);
	// アニメーション更新フレーム数を設定
	m_animation_update_frame = 5;

	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);

	m_search_range.CalculateEdges(m_pos.x, m_pos.y, SEARCH_RANGE_WIDTH, SEARCH_RANGE_HEIGHT);
}

void EnemyBat::Update()
{
	EnemyBase::Update();
	m_handle = m_handle_array[m_animation_frame];

	// コリジョン矩形、索敵範囲の更新
	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
	m_search_range.CalculateEdges(m_pos.x, m_pos.y, SEARCH_RANGE_WIDTH, SEARCH_RANGE_HEIGHT);
}

void EnemyBat::TrackPlayer(Vec2 player_pos)
{
	m_is_tracking = true;

	// 敵からプレイヤーの方向ベクトル
	Vec2 direction = player_pos - m_pos;

	// 方向ベクトルを正規化
	direction.Normalize();

	m_move = direction * MOVE_SPEED;

	// キャラクターの向きを変更
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

void EnemyBat::ReturnToInitPos()
{
	if (!m_is_tracking)
	{
		return;
	}

	// 初期座標との方向ベクトルを計算
	Vec2 direction = m_init_pos - m_pos;

	// 初期座標までの距離
	float distance = direction.Length();

	// 移動速度以内まで近づいたら初期座標に戻し、処理を終了
	if (distance <= MOVE_SPEED)
	{
		m_pos = m_init_pos;
		m_move = Vec2(0.0f, 0.0f);
		m_is_tracking = false;

		return;
	}

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