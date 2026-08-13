#include <DxLib.h>
#include "../../GameConst.h"
#include "../../Input/Keyboard.h"
#include "MenuPause.h"

MenuPause::MenuPause()
	:m_background_width(0.0f), m_background_height(0.0f), m_is_selected_title(false)
{
	m_selected_item = MenuPauseItem::ReturnToGame;
	m_handle_background = LoadGraph("Data/UI/menu_background.png");
	m_font_handle = CreateFontToHandle("クラフト明朝", 48, -1);
	m_font_item_handle = CreateFontToHandle("クラフト明朝", 24, -1);
	m_font_item_selected_handle = CreateFontToHandle("クラフト明朝", 36, -1);
}

MenuPause::~MenuPause()
{
	DeleteGraph(m_handle_background);
}

void MenuPause::Init()
{
	GetGraphSizeF(m_handle_background, &m_background_width, &m_background_height);
}

void MenuPause::Update()
{
	switch (m_selected_item)
	{
	case MenuPauseItem::ReturnToGame:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RETURN))
		{
			//m_is_newgame = true;
		}
		// 下を押したとき選択状態を設定に変更
		if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			m_selected_item = MenuPauseItem::Config;
		}
		// 上を押したとき選択状態をタイトルへに変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuPauseItem::ReturnToTitle;
		}

		break;
	}
	case MenuPauseItem::Config:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RETURN))
		{
			// 設定を開く
		}
		// 下を押したとき選択状態をタイトルへに変更
		if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			m_selected_item = MenuPauseItem::ReturnToTitle;
		}
		// 上を押したとき選択状態をゲームへもどるに変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuPauseItem::ReturnToGame;
		}

		break;
	}
	case MenuPauseItem::ReturnToTitle:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RETURN))
		{
			// 内容を保存しタイトルシーンへ遷移
			m_is_selected_title = true;
		}
		// 下を押したとき選択状態をゲームへ戻るに変更
		if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			m_selected_item = MenuPauseItem::ReturnToGame;
		}
		// 上を押したとき選択状態を設定に変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuPauseItem::Config;
		}

		break;
	}
	}
}

void MenuPause::Draw()
{
	// ポーズ背景の描画座標を計算
	float draw_x = (Game::SCREEN_WIDTH - m_background_width) * 0.5f;
	float draw_y = (Game::SCREEN_HEIGHT - m_background_height) * 0.5f;

	DrawGraphF(draw_x, draw_y, m_handle_background, true);

	// 文字列のサイズを取得
	int width = GetDrawFormatStringWidthToHandle(m_font_handle, "...ポーズ中...");
	// 文字列の描画座標を計算
	draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
	draw_y += 100.0f;

	DrawFormatStringToHandle(draw_x, draw_y, GetColor(0, 105, 148), m_font_handle, "...ポーズ中...");

	switch (m_selected_item)
	{
	case MenuPauseItem::ReturnToGame:
	{
		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_selected_handle, "ゲームへもどる");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 125.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 0, 0), m_font_item_selected_handle, "ゲームへもどる");

		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "せってい");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 80.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "せってい");

		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "タイトルへ");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 80.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "タイトルへ");

		break;
	}
	case MenuPauseItem::Config:
	{
		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "ゲームへもどる");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 125.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "ゲームへもどる");

		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_selected_handle, "せってい");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 80.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 0, 0), m_font_item_selected_handle, "せってい");

		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "タイトルへ");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 80.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "タイトルへ");

		break;
	}
	case MenuPauseItem::ReturnToTitle:
	{
		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "ゲームへもどる");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 125.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "ゲームへもどる");

		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "せってい");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 80.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "せってい");

		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_selected_handle, "タイトルへ");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 80.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 0, 0), m_font_item_selected_handle, "タイトルへ");

		break;
	}
	}
	
	//// 文字列のサイズを取得
	//width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "ゲームへもどる");
	//// 文字列の描画座標を計算
	//draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
	//draw_y += 125.0f;

	//DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "ゲームにもどる");

	//// 文字列のサイズを取得
	//width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "せってい");
	//// 文字列の描画座標を計算
	//draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
	//draw_y += 80.0f;

	//DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "せってい");

	//// 文字列のサイズを取得
	//width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "タイトルへ");
	//// 文字列の描画座標を計算
	//draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
	//draw_y += 80.0f;

	//DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "タイトルへ");
}

void MenuPause::SetSelectedItem()
{
	m_selected_item = MenuPauseItem::ReturnToGame;
}