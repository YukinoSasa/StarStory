#include <DxLib.h>
#include "Enemy.h"
#include "../../GameConst.h"
#include "../../Stage/Stage.h"

namespace
{
	// 移動速度
	float MOVE_SPEED = 1.0f;
	// 床判定用仮想rectクラスのサイズ
	float RECT_SIZE = 32.0f;
}

Enemy::Enemy(EnemyData enemy_data)
	:EnemyBase(enemy_data), m_animation_frame(0), m_animation_timer(0)
{
	LoadDivGraph(enemy_data.m_file_pass.c_str(), 9, 9, 1, 64, 64, m_handle_array);
	//m_pos = enemy_data.m_spawn;
	//m_handle_width = enemy_data.m_size;
	//m_handle_height = enemy_data.m_size;
}

Enemy::~Enemy()
{
	for (int i = 0; i < sizeof(m_handle_array) / sizeof(m_handle_array[0]); i++)
	{
		DeleteGraph(m_handle_array[i]);
	}
}

void Enemy::Init()
{
	EnemyBase::Init();

	// 当たり判定サイズ
	m_collision_width = 46.0f;
	m_collision_height = 50.0f;

	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
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

	m_pos.x += m_move.x;
	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
	//CharacterBase::Update();

	m_handle = m_handle_array[m_animation_frame];

	m_animation_timer++;
	if (m_animation_timer >= 7)
	{
		UpdateAnimation();
		m_animation_timer = 0;
	}

}

void Enemy::Draw(Vec2 camera_pos)
{
	//CharacterBase::Draw(camera_pos);

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
	// デバック時のみ当たり判定の矩形を描画
	m_rect.Draw(camera_pos);
#endif
}

void Enemy::UpdateAnimation()
{
	m_animation_frame++;
	if (m_animation_frame > 8)
	{
		m_animation_frame = 0;
	}
}
