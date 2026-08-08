#include <DxLib.h>
#include "../Sound/SoundManager.h"
#include "Menu/MenuTitle.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	m_p_menu_title = std::make_shared<MenuTitle>();
	m_p_sound_manager = std::make_shared<SoundManager>();
}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Init()
{
	m_p_sound_manager->Init();
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