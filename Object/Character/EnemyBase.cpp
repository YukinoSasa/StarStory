#include <DxLib.h>
#include "../../GameConst.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(EnemyData enemy_data)
	:m_search_range()
{
	//m_original_handle = LoadGraph(enemy_data.m_file_pass.c_str());
	// 敵のタイプcsvにもスクリプトにも追加する！！！１
	m_pos = enemy_data.m_spawn;
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
	// デバック時のみ当たり判定の矩形を描画
	m_rect.Draw(camera_pos);
#endif

}

void EnemyBase::TrackPlayer(Vec2 player_pos)
{

}

void EnemyBase::ReturnToInitPos()
{

}