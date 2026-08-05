#include "MovingPlatform.h"

namespace
{
	// ìÆÇ≠ë¨Ç≥
	float MOVE_SPEED = 1.0f;
}

MovingPlatform::MovingPlatform(GimmickData gimmick_data)
	:GimmickBase(gimmick_data)
{
	// èâä˙à íuÇï€ë∂
	m_init_pos = m_pos;

	// ècÇ…ìÆÇ≠è∞
	if (m_gimmick_type == 2)
	{
		m_move.x = 0.0f;
		m_move.y = +MOVE_SPEED;
	}
	// â°Ç…ìÆÇ≠è∞
	else if (m_gimmick_type == 3)
	{
		m_move.x = +MOVE_SPEED;
		m_move.y = 0.0f;
	}
}

MovingPlatform::~MovingPlatform()
{

}

void MovingPlatform::Init()
{
	m_collision_width = 320.0f;
	m_collision_height = 24.0f;
}

void MovingPlatform::Update(Rect player_rect, Vec2 player_last_move)
{
	switch (m_gimmick_type)
	{
	// ècà⁄ìÆÇÃè∞
	case 2:
	{
		if (m_pos.y <= m_init_pos.y - 100.0f)
		{
			m_move.y = +MOVE_SPEED;
		}
		else if (m_pos.y >= m_init_pos.y + 100.0f)
		{
			m_move.y = -MOVE_SPEED;
		}

		m_pos.y += m_move.y;

		break;
	}
	// â°à⁄ìÆÇÃè∞
	case 3:
	{
		if (m_pos.x <= m_init_pos.x - 200.0f)
		{
			m_move.x = +MOVE_SPEED;
		}
		else if (m_pos.x >= m_init_pos.x + 200.0f)
		{
			m_move.x = -MOVE_SPEED;
		}

		m_pos.x += m_move.x;

		break;
	}
	}

	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
}