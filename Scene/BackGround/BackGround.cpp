#include <DxLib.h>
#include "../../GameConst.h"
#include "BackGround.h"

BackGround::BackGround() :
	m_pos(0.0f, 0.0f), m_handle_width(0), m_handle_height(0)
{
	m_handle_ground = LoadGraph("Data/BG_01.png");
	m_handle_sky1 = LoadGraph("Data/BG_02.png");
}

BackGround::~BackGround()
{
	DeleteGraph(m_handle_ground);
	DeleteGraph(m_handle_sky1);
}

void BackGround::Init()
{
	GetGraphSize(m_handle_ground, &m_handle_width, &m_handle_height);
}

void BackGround::Draw(Vec2 camera_pos)
{
	// 背景ループ


	// スクリーン座標の計算
	float screen_x = m_pos.x - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	float screen_y = m_pos.y - camera_pos.y + Game::SCREEN_HALF_HEIGHT;
	DrawGraph(screen_x, screen_y, m_handle_ground, true);

	//int w, h;
	//GetDrawScreenSize(&w, &h);

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "Screen : %d x %d", w, h);
}