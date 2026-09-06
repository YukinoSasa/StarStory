#include "Box.h"
#include "../Character/Player.h"
#include "../../GameConst.h"

Box::Box(GimmickData gimmick_data) :
	GimmickBase(gimmick_data)
{

}

Box::~Box()
{

}

void Box::Init()
{
	m_collision_width = 64.0f;
	m_collision_height = 64.0f;
}

void Box::Update()
{
	GimmickBase::Update();

	Game::Gravity(m_move.y);

	m_pos.y += m_move.y;
}

void Box::MoveByPush(Vec2 move)
{
	// âEÇ©ÇÁâüÇ≥ÇÍÇÈèÍçá
	if (move.x < 0)
	{
		m_pos.x += move.x;
	}
	// ç∂Ç©ÇÁâüÇ≥ÇÍÇÈèÍçá
	else if (move.x > 0)
	{
		m_pos.x += move.x;
	}
}