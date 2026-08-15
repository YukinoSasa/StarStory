#include <DxLib.h>
#include "../../Input/Keyboard.h"
#include "MenuTitle.h"

MenuTitle::MenuTitle()
{
	m_selected_item = MenuTitleItem::NewGame;
	m_current_state = MenuTitleState::None;

	m_font_item_handle = CreateFontToHandle("クラフト明朝", 32, -1);
	m_font_selected_handle = CreateFontToHandle("クラフト明朝", 48, -1);
}

MenuTitle::~MenuTitle()
{
	DeleteFontToHandle(m_font_item_handle);
	DeleteFontToHandle(m_font_selected_handle);
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
			m_current_state = MenuTitleState::SelectedNewGame;
		}
		// 下を押したとき選択状態をロードに変更
		if (Keyboard::IsTrigger(KEY_INPUT_DOWN))
		{
			m_selected_item = MenuTitleItem::Load;
		}
		// 上を押したとき選択状態をゲーム終了に変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuTitleItem::Exit;
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
		}
		// 上を押したとき選択状態をゲーム開始に変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuTitleItem::NewGame;
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
		}
		// 上を押したとき選択状態をロードに変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuTitleItem::Load;
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
		}
		// 上を押したとき選択状態を設定に変更
		if (Keyboard::IsTrigger(KEY_INPUT_UP))
		{
			m_selected_item = MenuTitleItem::Config;
		}

		break;
	}
	}
}

void MenuTitle::Draw()
{
	switch (m_selected_item)
	{
	case MenuTitleItem::NewGame:
	{

		DrawFormatStringToHandle(900, 475, GetColor(0, 0, 255), m_font_selected_handle, "最初からはじめる");
		DrawFormatStringToHandle(900, 550, GetColor(255, 255, 255), m_font_item_handle, "続きからはじめる");
		DrawFormatStringToHandle(900, 625, GetColor(255, 255, 255), m_font_item_handle, "せってい");
		DrawFormatStringToHandle(900, 700, GetColor(255, 255, 255), m_font_item_handle, "ゲームをおわる");

		break;
	}
	case MenuTitleItem::Load:
	{
		DrawFormatStringToHandle(900, 475, GetColor(255, 255, 255), m_font_item_handle, "最初からはじめる");
		DrawFormatStringToHandle(900, 550, GetColor(0, 0, 255), m_font_selected_handle, "続きからはじめる");
		DrawFormatStringToHandle(900, 625, GetColor(255, 255, 255), m_font_item_handle, "せってい");
		DrawFormatStringToHandle(900, 700, GetColor(255, 255, 255), m_font_item_handle, "ゲームをおわる");

		break;
	}
	case MenuTitleItem::Config:
	{
		DrawFormatStringToHandle(900, 475, GetColor(255, 255, 255), m_font_item_handle, "最初からはじめる");
		DrawFormatStringToHandle(900, 550, GetColor(255, 255, 255), m_font_item_handle, "続きからはじめる");
		DrawFormatStringToHandle(900, 625, GetColor(0, 0, 255), m_font_selected_handle, "せってい");
		DrawFormatStringToHandle(900, 700, GetColor(255, 255, 255), m_font_item_handle, "ゲームをおわる");

		break;
	}
	case MenuTitleItem::Exit:
	{
		DrawFormatStringToHandle(900, 475, GetColor(255, 255, 255), m_font_item_handle, "最初からはじめる");
		DrawFormatStringToHandle(900, 550, GetColor(255, 255, 255), m_font_item_handle, "続きからはじめる");
		DrawFormatStringToHandle(900, 625, GetColor(255, 255, 255), m_font_item_handle, "せってい");
		DrawFormatStringToHandle(900, 700, GetColor(0, 0, 255), m_font_selected_handle, "ゲームをおわる");

		break;
	}
	}
}