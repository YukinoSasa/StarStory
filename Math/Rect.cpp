#include <DxLib.h>
#include "Rect.h"

Rect::Rect() :
	m_LeftEdge(0.0f), m_RightEdge(0.0f), m_TopEdge(0.0f), m_BottomEdge(0.0f)
{

}

Rect::~Rect()
{

}

void Rect::Draw(Vec2 cameraPos)
{
	DrawBox(static_cast<int>(m_LeftEdge - cameraPos.m_x + 960.0f), static_cast<int>(m_TopEdge - cameraPos.m_y + 540.0f),
		static_cast<int>(m_RightEdge - cameraPos.m_x + 960.0f), static_cast<int>(m_BottomEdge - cameraPos.m_y + 540.0f), GetColor(255, 0, 0), false);
}

bool Rect::IsCollision(const Rect& object)
{
	// 自身の左端xより対象の右端xが小さいときは衝突していない
	if (m_LeftEdge > object.m_RightEdge)
	{
		return false;
	}
	// 自身の右端xより対象の左端xが大きいときは衝突していない
	else if (m_RightEdge < object.m_LeftEdge)
	{
		return false;
	}
	// 自身の上端yより対象の下端yが小さいときは衝突していない
	else if (m_TopEdge > object.m_BottomEdge)
	{
		return false;
	}
	// 自身の下端yより対象の上端yが大きいときは衝突していない
	else if (m_BottomEdge < object.m_TopEdge)
	{
		return false;
	}
	// 上記以外は衝突している
	else
	{
		return true;
	}
}

void Rect::SetEdges(float x, float y, float width, float height)
{
	m_LeftEdge = x - width / 2;
	m_RightEdge = x + width / 2;
	m_TopEdge = y - height / 2;
	m_BottomEdge = y + height / 2;
}