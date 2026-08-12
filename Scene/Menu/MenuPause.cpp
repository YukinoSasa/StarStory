#include <DxLib.h>
#include "../../Input/Keyboard.h"
#include "MenuPause.h"

MenuPause::MenuPause()
{
	m_selected_item = MenuPauseItem::ReturnToGame;
	m_handle_background = LoadGraph("Data/UI/menu_background.png");
	m_font_handle = CreateFontToHandle("クラフト明朝", 48, -1);
	m_font_item_handle = CreateFontToHandle("クラフト明朝", 24, -1);
}

MenuPause::~MenuPause()
{
	DeleteGraph(m_handle_background);
}

void MenuPause::Init()
{

}

void MenuPause::Update()
{
	//if (!m_is_closed && Keyboard::IsTrigger(KEY_INPUT_ESCAPE))
	//{
	//	m_is_closed = true;
	//}
}

void MenuPause::Draw()
{
	DrawGraph(632, 268, m_handle_background, true);
	DrawFormatStringToHandle(800, 400, GetColor(0, 105, 148), m_font_handle, "ポーズ中...");

}