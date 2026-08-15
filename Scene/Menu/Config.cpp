#include <DxLib.h>
#include "../../GameConst.h"
#include "../../Input/Keyboard.h"
#include "Config.h"

Config::Config()
	:m_handle_width(0.0f), m_handle_height(0.0f), m_volume_bgm(-1)
{
	m_handle_background = LoadGraph("Data/UI/config_background.png");
	m_font_handle = CreateFontToHandle("クラフト明朝", 48, -1);
	m_font_item_handle = CreateFontToHandle("クラフト明朝", 24, -1);
}

Config::~Config()
{
	DeleteGraph(m_handle_background);
	DeleteFontToHandle(m_font_handle);
	DeleteFontToHandle(m_font_item_handle);
}

void Config::Init()
{
	GetGraphSizeF(m_handle_background, &m_handle_width, &m_handle_height);
}

void Config::Update(GameSetting& game_setting)
{
	if (Keyboard::IsTrigger(KEY_INPUT_RIGHT))
	{
		game_setting.m_volume_bgm += 15;

		if (game_setting.m_volume_bgm > 255)
		{
			game_setting.m_volume_bgm = 255;
		}
	}
	else if (Keyboard::IsTrigger(KEY_INPUT_LEFT))
	{
		game_setting.m_volume_bgm -= 15;

		if (game_setting.m_volume_bgm < 0)
		{
			game_setting.m_volume_bgm = 0;
		}
	}

	m_volume_bgm = game_setting.m_volume_bgm;
}

void Config::Draw()
{
	// 描画位置を計算
	float draw_x = (Game::SCREEN_WIDTH - m_handle_width) * 0.5f;
	float draw_y = (Game::SCREEN_HEIGHT - m_handle_height) * 0.5f;

	DrawGraphF(draw_x, draw_y, m_handle_background, true);

	// 文字列のサイズを取得
	int width = GetDrawFormatStringWidthToHandle(m_font_handle, "...せってい...");
	// 文字列の描画座標を計算
	draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
	draw_y += 200.0f;

	DrawFormatStringToHandle(draw_x, draw_y, GetColor(0, 105, 148), m_font_handle, "...せってい...");

	DrawFormatString(0, 0, GetColor(255, 255, 255), "BGM : %d", m_volume_bgm);
}