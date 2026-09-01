#include <DxLib.h>
#include "../../GameConst.h"
#include "../../Stage/Stage.h"
#include "EnemyGhost.h"

namespace
{
	// 移動速度
	float MOVE_SPEED = 1.0f;

	// 床判定用仮想rectのサイズ
	float RECT_SIZE = 32.0f;
}

EnemyGhost::EnemyGhost(EnemyData enemy_data)
	:EnemyBase(enemy_data)
{
	LoadDivGraph(enemy_data.m_file_pass.c_str(), 9, 9, 1, 64, 64, m_handle_array);
}

EnemyGhost::~EnemyGhost()
{
	for (int i = 0; i < sizeof(m_handle_array) / sizeof(m_handle_array[0]); i++)
	{
		DeleteGraph(m_handle_array[i]);
	}
}

void EnemyGhost::Init()
{
	EnemyBase::Init();

	m_collision_width = 46.0f;
	m_collision_height = 50.0f;

	// アニメーション要素数を設定
	m_animation_elements = sizeof(m_handle_array) / sizeof(m_handle_array[0]);
	// アニメーション更新フレーム数を設定
	m_animation_update_frame = 7;

	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
}

void EnemyGhost::Update()
{
	EnemyBase::Update();
	m_handle = m_handle_array[m_animation_frame];

	// マップチップ接触判定の前に接地状態をfalseに更新する
	m_is_ground = false;

	// 敵の進行方向足元に仮想rectを生成
	Rect rect;
	if (m_is_right)
	{
		rect.CalculateEdges(
			m_pos.x + (m_handle_width * 0.5f),
			m_pos.y + (m_handle_height * 0.5f) + (Game::MAPCHIP_SIZE * 0.5f),
			RECT_SIZE, RECT_SIZE);
	}
	else
	{
		rect.CalculateEdges(
			m_pos.x - (m_handle_width * 0.5f),
			m_pos.y + (m_handle_height * 0.5f) + (Game::MAPCHIP_SIZE * 0.5f),
			RECT_SIZE, RECT_SIZE);
	}
	
	// Stageに地形の問い合わせ、前方に床が無かったら向きを変える
	if (!m_p_stage->IsGroundFoward(rect))
	{
		m_is_right = !m_is_right;
	}

	// キャラクターの向きに合わせて進行方向を変更
	if (m_is_right)
	{
		m_move.x = +MOVE_SPEED;
	}
	else if (!m_is_right)
	{
		m_move.x = -MOVE_SPEED;
	}

	// 移動処理、コリジョン矩形の更新
	m_pos.x += m_move.x;
	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
}