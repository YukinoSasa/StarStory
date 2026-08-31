#include <DxLib.h>
#include "../../GameConst.h"
#include "GimmickBase.h"

GimmickBase::GimmickBase(GimmickData gimmick_data)
{
	m_handle = LoadGraph(gimmick_data.m_file_pass.c_str());
	m_gimmick_type = gimmick_data.m_gimmick_type;
	m_pos = gimmick_data.m_spawn;
	m_handle_width = gimmick_data.m_width;
	m_handle_height = gimmick_data.m_height;
}

GimmickBase::~GimmickBase()
{
	DeleteGraph(m_handle);
}

void GimmickBase::Init()
{
	
}

void GimmickBase::Update(Rect player_rect, Vec2 player_last_move)
{
	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
}

void GimmickBase::Draw(Vec2 camera_pos)
{
	// ギミック画像の左上の座標
	float draw_x = m_pos.x - m_handle_width * 0.5f;
	float draw_y = m_pos.y - m_handle_height * 0.5f;

	// ギミック描画のスクリーン座標
	float screen_x = draw_x - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	float screen_y = draw_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	//DrawGraphF(screen_x, screen_y, m_handle, true);
	DrawGraphF(screen_x + m_handle_offset.x, screen_y + m_handle_offset.y, m_handle, true);

#ifdef _DEBUG
	//m_rect.Draw(camera_pos);
#endif
}

void GimmickBase::UpdateRect()
{
	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
}

void GimmickBase::MoveByPush(Vec2 move)
{

}