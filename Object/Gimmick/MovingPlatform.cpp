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

	m_move.y = +MOVE_SPEED;
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
	if (m_pos.y <= m_init_pos.y - 50.0f)
	{
		m_move.y = +MOVE_SPEED;
	}
	else if (m_pos.y >= m_init_pos.y + 50.0f)
	{
		m_move.y = -MOVE_SPEED;
	}

	m_pos.y += m_move.y;

	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
}