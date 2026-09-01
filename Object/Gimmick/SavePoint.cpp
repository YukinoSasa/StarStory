#include "SavePoint.h"

SavePoint::SavePoint(GimmickData gimmick_data)
	:GimmickBase(gimmick_data)
{

}

SavePoint::~SavePoint()
{

}

void SavePoint::Init()
{
	m_collision_width = 96.0f;
	m_collision_height = 96.0f;
}