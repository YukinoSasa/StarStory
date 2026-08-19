#include <DxLib.h>
#include "../../GameConst.h"
#include "../../Input/Keyboard.h"
#include "../../Sound/SoundManager.h"
#include "Config.h"

Config::Config()
	:m_handle_width(0.0f), m_handle_height(0.0f), m_is_close_selected(false), m_slider_bgm_pos_x(0.0f), m_slider_se_pos_x(0.0f), m_volume_bgm(-1), m_volume_se(-1)
{
	m_current_state = ConfigState::BGM;
	m_handle_background = LoadGraph("Data/UI/config_background.png");
	m_font_handle = CreateFontToHandle("クラフト明朝", 48, -1);
	m_font_item_handle = CreateFontToHandle("クラフト明朝", 42, -1);
	m_slider_l_handle = LoadGraph("Data/UI/slider_left.png");
	m_slider_m_handle = LoadGraph("Data/UI/slider_mid.png");
	m_slider_r_handle = LoadGraph("Data/UI/slider_right.png");
	m_slider_handle = LoadGraph("Data/UI/handle.png");
	m_slider_selected_handle = LoadGraph("Data/UI/handle_selected.png");
}

Config::~Config()
{
	DeleteGraph(m_handle_background);
	DeleteGraph(m_slider_l_handle);
	DeleteGraph(m_slider_m_handle);
	DeleteGraph(m_slider_r_handle);
	DeleteGraph(m_slider_handle);
	DeleteGraph(m_slider_selected_handle);
	DeleteFontToHandle(m_font_handle);
	DeleteFontToHandle(m_font_item_handle);
}

void Config::Init()
{
	GetGraphSizeF(m_handle_background, &m_handle_width, &m_handle_height);
	// スライダーハンドルの位置を設定
	m_slider_bgm_pos_x = 1248.0f;
	m_slider_se_pos_x = 1248.0f;
}

void Config::Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager)
{
	switch (m_current_state)
	{
	case ConfigState::BGM:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RIGHT))
		{
			game_setting.m_volume_bgm += 15;
			// (1248.f(slider右端) - 800.f(slider左端)) / 17(soundの変化段階)
			m_slider_bgm_pos_x += 26.0f;

			if (game_setting.m_volume_bgm > 255)
			{
				game_setting.m_volume_bgm = 255;
			}

			if (m_slider_bgm_pos_x > 1248.0f)
			{
				m_slider_bgm_pos_x = 1248.0f;
			}
		}
		else if (Keyboard::IsTrigger(KEY_INPUT_LEFT))
		{
			game_setting.m_volume_bgm -= 15;
			m_slider_bgm_pos_x -= 26.0f;

			if (game_setting.m_volume_bgm < 0)
			{
				game_setting.m_volume_bgm = 0;
			}

			if (m_slider_bgm_pos_x < 800.0f)
			{
				m_slider_bgm_pos_x = 800.0f;
			}
		}
		else if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			p_sound_manager->PlaySE(SoundManager::SeType::Select);
			m_current_state = ConfigState::BACK;
		}
		else if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			p_sound_manager->PlaySE(SoundManager::SeType::Select);
			m_current_state = ConfigState::SE;
		}

		break;
	}
	case ConfigState::SE:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RIGHT))
		{
			game_setting.m_volume_se += 15;
			m_slider_se_pos_x += 26.0f;

			if (game_setting.m_volume_se > 255)
			{
				game_setting.m_volume_se = 255;
			}

			if (m_slider_se_pos_x > 1248.0f)
			{
				m_slider_se_pos_x = 1248.0f;
			}

			p_sound_manager->PlaySE(SoundManager::SeType::Item);
		}
		else if (Keyboard::IsTrigger(KEY_INPUT_LEFT))
		{
			game_setting.m_volume_se -= 15;
			m_slider_se_pos_x -= 26.0f;

			if (game_setting.m_volume_se < 0)
			{
				game_setting.m_volume_se = 0;
			}

			if (m_slider_se_pos_x < 800.0f)
			{
				m_slider_se_pos_x = 800.0f;
			}

			p_sound_manager->PlaySE(SoundManager::SeType::Item);
		}
		else if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			p_sound_manager->PlaySE(SoundManager::SeType::Select);
			m_current_state = ConfigState::BGM;
		}
		else if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			p_sound_manager->PlaySE(SoundManager::SeType::Select);
			m_current_state = ConfigState::BACK;
		}

		break;
	}
	case ConfigState::BACK:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RETURN))
		{
			m_is_close_selected = true;
		}
		else if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			p_sound_manager->PlaySE(SoundManager::SeType::Select);
			m_current_state = ConfigState::SE;
		}
		else if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			p_sound_manager->PlaySE(SoundManager::SeType::Select);
			m_current_state = ConfigState::BGM;
		}

		break;
	}
	}

	m_volume_bgm = game_setting.m_volume_bgm;
	m_volume_se = game_setting.m_volume_se;
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

	// 文字列の描画座標を計算
	draw_x = 600.0f;
	draw_y += 100.0f;

	DrawFormatStringToHandle(draw_x, draw_y, GetColor(0, 105, 148), m_font_item_handle, "BGM");

	// 文字列の描画座標を計算
	draw_x = 600.0f;
	draw_y += 100.0f;

	DrawFormatStringToHandle(draw_x, draw_y, GetColor(0, 105, 148), m_font_item_handle, "SE");

	// BGMスライダーの描画座標を計算
	float draw_slider_x = 800.0f;
	float draw_slider_y = 470.0f;
	int draw_index = 8;

	for (int i = 0; i < draw_index; i++)
	{
		if (i == 0)
		{
			DrawGraphF(draw_slider_x + (64.0f * i), draw_slider_y, m_slider_l_handle, true);
		}
		else if (i == draw_index - 1)
		{
			DrawGraphF(draw_slider_x + (64.0f * i), draw_slider_y, m_slider_r_handle, true);
		}
		else
		{
			DrawGraphF(draw_slider_x + (64.0f * i), draw_slider_y, m_slider_m_handle, true);
		}
	}

	// SEスライダーの描画座標を計算
	draw_slider_x = 800.0f;
	draw_slider_y = 570.0f;

	for (int i = 0; i < draw_index; i++)
	{
		if (i == 0)
		{
			DrawGraphF(draw_slider_x + (64.0f * i), draw_slider_y, m_slider_l_handle, true);
		}
		else if (i == draw_index - 1)
		{
			DrawGraphF(draw_slider_x + (64.0f * i), draw_slider_y, m_slider_r_handle, true);
		}
		else
		{
			DrawGraphF(draw_slider_x + (64.0f * i), draw_slider_y, m_slider_m_handle, true);
		}
	}

	switch (m_current_state)
	{
	case ConfigState::BGM:
	{
		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "もどる");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 90.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "もどる");

		// BGMハンドルの描画座標を計算
		//float draw_handle_x = 1248.0f;
		float draw_handle_y = 470.0f;

		DrawGraphF(m_slider_bgm_pos_x, draw_handle_y, m_slider_selected_handle, true);

		// SEハンドルの描画座標を計算
		//draw_handle_x = 900.0f;
		draw_handle_y = 570.0f;

		DrawGraphF(m_slider_se_pos_x, draw_handle_y, m_slider_handle, true);

		break;
	}
	case ConfigState::SE:
	{
		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "もどる");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 90.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(255, 255, 255), m_font_item_handle, "もどる");

		// BGMハンドルの描画座標を計算
		//float draw_handle_x = 900.0f;
		float draw_handle_y = 470.0f;

		DrawGraphF(m_slider_bgm_pos_x, draw_handle_y, m_slider_handle, true);

		// SEハンドルの描画座標を計算
		//draw_handle_x = 900.0f;
		draw_handle_y = 570.0f;

		DrawGraphF(m_slider_se_pos_x, draw_handle_y, m_slider_selected_handle, true);

		break;
	}
	case ConfigState::BACK:
	{
		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_item_handle, "もどる");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 90.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(0, 105, 148), m_font_item_handle, "もどる");

		// BGMハンドルの描画座標を計算
		//float draw_handle_x = 900.0f;
		float draw_handle_y = 470.0f;

		DrawGraphF(m_slider_bgm_pos_x, draw_handle_y, m_slider_handle, true);

		// ハンドルの描画座標を計算
		//draw_handle_x = 900.0f;
		draw_handle_y = 570.0f;

		DrawGraphF(m_slider_se_pos_x, draw_handle_y, m_slider_handle, true);

		break;
	}
	}

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "BGM : %d", m_volume_bgm);
	//DrawFormatString(0, 30, GetColor(255, 255, 255), "SE : %d", m_volume_se);
}