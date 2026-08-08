#include <DxLib.h>
#include "SceneTitle.h"
#include "Menu/MenuTitle.h"

SceneTitle::SceneTitle()
{
	m_p_menu_title = std::make_shared<MenuTitle>();
}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Init()
{

}

void SceneTitle::Update()
{
	m_p_menu_title->Update();

	// ゲーム開始が選択されたときシーン遷移
	if (m_p_menu_title->GetIsNewGame())
	{
		m_is_scene_end = true;
	}
}

void SceneTitle::Draw()
{
	DrawFormatString(200, 200, GetColor(255, 255, 255), "星のものがたり");
	m_p_menu_title->Draw();
}