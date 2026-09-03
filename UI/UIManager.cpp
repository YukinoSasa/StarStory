#include <DxLib.h>
#include "../GameConst.h"
#include "UIManager.h"

UIManager::UIManager()
{
	m_collect_bg_handle = LoadGraph("Data/UI/collect_background.png");
	m_piece_ui_handle = LoadGraph("Data/UI/piece_ui.png");
	m_collect_font_handle = CreateFontToHandle("クラフト明朝", 64, -1);

	m_move_ui_handle = LoadGraph("Data/UI/move_ui.png");
	m_jump_ui_handle = LoadGraph("Data/UI/jump_ui.png");
	m_reset_ui_handle = LoadGraph("Data/UI/reset_ui.png");
}

UIManager::~UIManager()
{
	DeleteGraph(m_collect_bg_handle);
	DeleteFontToHandle(m_collect_font_handle);
	DeleteFontToHandle(m_piece_ui_handle);

	DeleteFontToHandle(m_move_ui_handle);
	DeleteFontToHandle(m_jump_ui_handle);
	DeleteFontToHandle(m_reset_ui_handle);
}

void UIManager::Draw(Vec2 camera_pos, int collect_item)
{
	// 画面に固定するUI //
	// 
	// 星のかけらカウントUIの描画
	DrawGraphF(1600.0f, 0.0f, m_collect_bg_handle, true);
	DrawGraphF(1680.0f, 30.0f, m_piece_ui_handle, true);
	DrawFormatStringToHandle(1800.0f, 50.0f, GetColor(0, 105, 148),
		m_collect_font_handle, "%d", collect_item);
}

void UIManager::DrawGuideUI(Vec2 camera_pos)
{
	// MOVE UI
	// スクリーン座標
	float screen_x = 128.0f - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	float screen_y = 3840.0f - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	DrawGraphF(screen_x, screen_y, m_move_ui_handle, true);

	// JUMP UI
	// スクリーン座標
	screen_x = 640.0f - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	screen_y = 3712.0f - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	DrawGraphF(screen_x, screen_y, m_jump_ui_handle, true);

	// RESET UI
	// スクリーン座標
	screen_x = 320.0f - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	screen_y = 300.0f - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	DrawGraphF(screen_x, screen_y, m_reset_ui_handle, true);
}