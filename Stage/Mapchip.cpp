#include <DxLib.h>
#include "../GameConst.h"
#include "Mapchip.h"

Mapchip::Mapchip(float pos_x, float pos_y, int tile, bool is_collision)
	:m_pos(pos_x, pos_y), m_rect(), m_tile(tile), m_is_collision(is_collision)
{
	
}

Mapchip::~Mapchip()
{

}

void Mapchip::Init()
{
	m_rect.CalculateEdges(m_pos.x, m_pos.y, Game::MAPCHIP_SIZE, Game::MAPCHIP_SIZE);
}

void Mapchip::Update()
{

}

void Mapchip::Draw(Vec2 camera_pos, int* handle_array)
{
	// DrawGraphÇÕç∂è„äÓèÄÇ»ÇÃÇ≈íÜêSäÓèÄÇ©ÇÁç∂è„Ç…Ç∏ÇÁÇ∑
	float screen_x = m_pos.x - camera_pos.x + Game::SCREEN_HALF_WIDTH - (Game::MAPCHIP_SIZE * 0.5f);
	float screen_y = m_pos.y - camera_pos.y + Game::SCREEN_HALF_HEIGHT - (Game::MAPCHIP_SIZE * 0.5f);

	DrawExtendGraphF(screen_x, screen_y, screen_x + Game::MAPCHIP_SIZE, screen_y + Game::MAPCHIP_SIZE, handle_array[m_tile], true);

	//m_rect.Draw(camera_pos);
}