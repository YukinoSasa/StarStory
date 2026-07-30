#include <DxLib.h>
#include "Enemy.h"
#include "../../GameConst.h"
#include "../../Stage/Stage.h"

namespace
{
	// 移動速度
	float MOVE_SPEED = 2.0f;
	// 床判定用仮想rectクラスのサイズ
	float RECT_SIZE = 32.0f;
}

Enemy::Enemy(EnemyData enemy_data)
{
	m_handle = LoadGraph(enemy_data.m_file_pass.c_str());
	m_pos = enemy_data.m_spawn;
	m_handle_width = enemy_data.m_size;
	m_handle_height = enemy_data.m_size;
}

Enemy::~Enemy()
{
	DeleteGraph(m_handle);
}

void Enemy::Init()
{
	CharacterBase::Init();
}

void Enemy::Update()
{
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

	// m_is_groundかつm_is_rightなら進行方向右
	if (m_is_right)
	{
		m_move.x = +MOVE_SPEED;
	}
	// m_is_groundかつ!m_is_rightなら進行方向左
	else if (!m_is_right)
	{
		m_move.x = -MOVE_SPEED;
	}

	CharacterBase::Update();
}

void Enemy::Draw(Vec2 camera_pos)
{
	CharacterBase::Draw(camera_pos);
}