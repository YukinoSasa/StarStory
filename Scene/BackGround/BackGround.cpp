#include <DxLib.h>
#include "../../GameConst.h"
#include "BackGround.h"

BackGround::BackGround() :
	m_pos(0.0f, 0.0f), m_handle_width(0), m_handle_height(0)
{
	m_bg_handle = LoadGraph("Data/Graph/BG_02.png");
}

BackGround::~BackGround()
{
	DeleteGraph(m_bg_handle);
}

void BackGround::Init()
{
	GetGraphSizeF(m_bg_handle, &m_handle_width, &m_handle_height);
}

void BackGround::Draw(Vec2 camera_pos, float stage_height)
{
	// 地面背景のワールドy座標
	float world_ground_y = stage_height - m_handle_height;
	float screen_y = world_ground_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	// 背景ループ
	for (int i = CalculateBackgroundIndex(camera_pos.y) - 1; i < CalculateBackgroundIndex(camera_pos.y) + 2; i++)
	{
		// 背景のワールドy座標(左上基準)
		float world_y = i * m_handle_height;
		// スクリーン座標の計算
		float screen_x = m_pos.x - camera_pos.x + Game::SCREEN_HALF_WIDTH;
		float screen_y = world_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

		DrawGraphF(screen_x, screen_y, m_bg_handle, true);
	}
}

int BackGround::CalculateBackgroundIndex(float camera_pos_y)
{
	// カメラワールド座標を画像の高さで割る
	return static_cast<int>(camera_pos_y) / m_handle_height;
}