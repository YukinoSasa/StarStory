#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(GimmickData gimmick_data)
	:GimmickBase(gimmick_data)
{

}

MovingPlatform::~MovingPlatform()
{

}

void MovingPlatform::Init()
{
	m_collision_width = 320.0f;
	m_collision_height = 24.0f;
}

void MovingPlatform::Update()
{

}