#include "Box.h"
#include "../Character/Player.h"
#include "../../GameConst.h"

Box::Box(GimmickData gimmick_data) :
	GimmickBase(gimmick_data)
{
	m_rect.SetIsObject(true);
}

Box::~Box()
{

}

void Box::Init()
{

}

void Box::Update(Rect player_rect, Vec2 player_last_move)
{
	GimmickBase::Update(player_rect, player_last_move);

	Game::Gravity(m_move.y);

	m_pos.y += m_move.y;

	// プレイヤーと接触しているかどうか
	if (m_rect.IsCollision(player_rect))
	{
		// 右から押される場合
		if (player_last_move.x < 0)
		{
			m_pos.x += player_last_move.x;
		}
		// 左から押される場合
		if (player_last_move.x > 0)
		{
			m_pos.x += player_last_move.x;
		}
	}
}