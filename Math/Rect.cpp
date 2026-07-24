#include <DxLib.h>
#include "../GameConst.h"
#include "Rect.h"

Rect::Rect() :
	m_left_edge(0.0f), m_right_edge(0.0f), m_top_edge(0.0f), m_bottom_edge(0.0f), m_is_object(true)
{

}

void Rect::Draw(Vec2 camera_pos)
{
	DrawBox(static_cast<int>(m_left_edge - camera_pos.x + Game::SCREEN_HALF_WIDTH),
		static_cast<int>(m_top_edge - camera_pos.y + Game::SCREEN_HALF_HEIGHT),
		static_cast<int>(m_right_edge - camera_pos.x + Game::SCREEN_HALF_WIDTH),
		static_cast<int>(m_bottom_edge - camera_pos.y + Game::SCREEN_HALF_HEIGHT),
		GetColor(255, 0, 0), false);
}

bool Rect::IsCollision(const Rect& object) const
{
	// 自身の左端xより対象の右端xが小さいときは衝突していない
	if (m_left_edge > object.m_right_edge)
	{
		return false;
	}
	// 自身の右端xより対象の左端xが大きいときは衝突していない
	else if (m_right_edge < object.m_left_edge)
	{
		return false;
	}
	// 自身の上端yより対象の下端yが小さいときは衝突していない
	else if (m_top_edge > object.m_bottom_edge)
	{
		return false;
	}
	// 自身の下端yより対象の上端yが大きいときは衝突していない
	else if (m_bottom_edge < object.m_top_edge)
	{
		return false;
	}
	// 上記以外は衝突している
	else
	{
		return true;
	}
}

void Rect::CalculateEdges(float x, float y, float width, float height)
{
	m_left_edge = x - width * 0.5f;
	m_right_edge = x + width * 0.5f;
	m_top_edge = y - height * 0.5f;
	m_bottom_edge = y + height * 0.5f;
}