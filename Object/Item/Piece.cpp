#include <DxLib.h>
#include "../../GameConst.h"
#include "Piece.h"

namespace
{
	// アニメーションを更新するフレーム数
	int animation_update_frame = 7;
}

Piece::Piece(ItemData item_data)
	:m_is_collect(false), m_animation_timer(0), m_animation_frame(0)
{
	LoadDivGraph(item_data.m_file_pass.c_str(), 4, 4, 1, 48, 48, m_handle_array);
	m_pos = item_data.m_spawn;
	m_handle_width = item_data.m_size;
	m_handle_height = item_data.m_size;
}

Piece::~Piece()
{
	for (int i = 0; i < sizeof(m_handle_array) / sizeof(m_handle_array[0]); i++)
	{
		DeleteGraph(m_handle_array[i]);
	}
}

void Piece::Init()
{
	GetGraphSizeF(m_handle, &m_handle_width, &m_handle_height);

	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_handle_width, m_handle_height);
}

void Piece::Update()
{
	m_animation_timer++;
	if (m_animation_timer >= animation_update_frame)
	{
		UpdateAnimation();
		m_animation_timer = 0;
	}
}

void Piece::Draw(Vec2 camera_pos)
{
	// 取得された状態の場合描画しない
	if (m_is_collect)
	{
		return;
	}

	// 画像の左上の座標
	float draw_x = m_pos.x - m_handle_width * 0.5f;
	float draw_y = m_pos.y - m_handle_height * 0.5f;

	// 描画のスクリーン座標
	float screen_x = draw_x - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	float screen_y = draw_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	DrawGraphF(screen_x, screen_y, m_handle_array[m_animation_frame], true);
}

void Piece::Collect()
{
	m_is_collect = true;
}

void Piece::UpdateAnimation()
{
	m_animation_frame++;
	if (m_animation_frame > 3)
	{
		m_animation_frame = 0;
	}
}