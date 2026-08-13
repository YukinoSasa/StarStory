#include <DxLib.h>
#include "../../Input/Keyboard.h"
#include "MenuTitle.h"

namespace
{
	// メニュー項目のy座標の差
	float Y_DIFF = 30.0f;
}

MenuTitle::MenuTitle()
	:m_is_newgame(false),m_item_y(300.0f)
{
	m_selected_item = MenuTitleItem::NewGame;
	m_current_state = MenuTitleState::None;
}

MenuTitle::~MenuTitle()
{

}

void MenuTitle::Init()
{
}

void MenuTitle::Update()
{
	switch (m_selected_item)
	{
	case MenuTitleItem::NewGame:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RETURN))
		{
			m_is_newgame = true;
			m_current_state = MenuTitleState::SelectedNewGame;
		}
		// 下を押したとき選択状態をロードに変更
		if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			m_selected_item = MenuTitleItem::Load;
			m_item_y += Y_DIFF;
		}
		// 上を押したとき選択状態をゲーム終了に変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuTitleItem::Exit;
			m_item_y = 390.0f;
		}

		break;
	}
	case MenuTitleItem::Load:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RETURN))
		{
			// メインシーンへ遷移し、保存された箇所からスタートする
			m_current_state = MenuTitleState::SelectedLoad;
		}
		// 下を押したとき選択状態を設定に変更
		if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			m_selected_item = MenuTitleItem::Config;
			m_item_y += Y_DIFF;
		}
		// 上を押したとき選択状態をゲーム開始に変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuTitleItem::NewGame;
			m_item_y -= Y_DIFF;
		}

		break;
	}
	case MenuTitleItem::Config:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RETURN))
		{
			// 音量設定など
			m_current_state = MenuTitleState::SelectedConfig;
		}
		// 下を押したとき選択状態をゲーム終了に変更
		if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			m_selected_item = MenuTitleItem::Exit;
			m_item_y += Y_DIFF;
		}
		// 上を押したとき選択状態をロードに変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuTitleItem::Load;
			m_item_y -= Y_DIFF;
		}

		break;
	}
	case MenuTitleItem::Exit:
	{
		if (Keyboard::IsTrigger(KEY_INPUT_RETURN))
		{
			// ゲーム終了
			m_current_state = MenuTitleState::SelectedExit;
		}
		// 下を押したとき選択状態をゲーム開始に変更
		if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			m_selected_item = MenuTitleItem::NewGame;
			m_item_y = 300.0f;
		}
		// 上を押したとき選択状態を設定に変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuTitleItem::Config;
			m_item_y -= Y_DIFF;
		}

		break;
	}
	}
}

void MenuTitle::Draw()
{
	DrawFormatString(500, 300, GetColor(255, 255, 255), "New Game");
	DrawFormatString(500, 330, GetColor(255, 255, 255), "Load");
	DrawFormatString(500, 360, GetColor(255, 255, 255), "Config");
	DrawFormatString(500, 390, GetColor(255, 255, 255), "Exit");
	DrawFormatString(500, 420, GetColor(255, 255, 255), "m_is_newgame : %d", m_is_newgame);
	DrawCircleAA(450.0f, m_item_y, 10.0f, 32, GetColor(255, 255, 255), 1);
}