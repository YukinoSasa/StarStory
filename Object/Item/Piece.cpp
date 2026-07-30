#include <DxLib.h>
#include "../../GameConst.h"
#include "Piece.h"

Piece::Piece(ItemData item_data)
	:m_is_collect(false)
{
	m_handle = LoadGraph(item_data.m_file_pass.c_str());
	m_pos = item_data.m_spawn;
	m_handle_width = item_data.m_size;
	m_handle_height = item_data.m_size;
}

Piece::~Piece()
{
	DeleteGraph(m_handle);
}

void Piece::Init()
{
	GetGraphSizeF(m_handle, &m_handle_width, &m_handle_height);

	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_handle_width, m_handle_height);
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

	DrawGraphF(screen_x, screen_y, m_handle, true);
}

void Piece::Collect()
{
	m_is_collect = true;
}