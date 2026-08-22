#include "Spring.h"
#include "../Character/Player.h"
#include "../../GameConst.h"

Spring::Spring(GimmickData gimmick_data) :
	GimmickBase(gimmick_data), m_spring_power(14.0f)
{
	m_rect.SetIsObject(true);
}

Spring::~Spring()
{

}

void Spring::Init()
{
	m_collision_width = 64.0f;
	m_collision_height = 51.0f;
}

void Spring::Update(Rect player_rect, Vec2 player_move)
{
	GimmickBase::Update(player_rect, player_move);
}