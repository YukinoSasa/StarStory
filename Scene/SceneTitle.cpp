#include <DxLib.h>
#include "../Input/Keyboard.h"
#include "../Sound/SoundManager.h"
#include "Menu/MenuTitle.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle(GameData& game_data, std::shared_ptr<StoryManager> p_story_manager)
	:SceneBase(game_data, p_story_manager)
{
	m_p_menu_title = std::make_shared<MenuTitle>();
	m_font_handle = CreateFontToHandle("クラフト明朝", 64, -1);
	m_bg_handle = LoadGraph("Data/title_bg.png");
}

SceneTitle::~SceneTitle()
{
	DeleteFontToHandle(m_font_handle);
	DeleteGraph(m_bg_handle);
}

void SceneTitle::Init()
{
	m_config.Init();
}

void SceneTitle::Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager)
{
	// 設定を開いているとき以外はタイトルメニューをUpdate
	if (m_p_menu_title->GetCurrentState() != MenuTitle::MenuTitleState::SelectedConfig)
	{
		m_p_menu_title->Update(p_sound_manager);
	}

	// ゲーム開始が選択されたときシーン遷移
	if (m_p_menu_title->GetCurrentState() == MenuTitle::MenuTitleState::SelectedNewGame)
	{
		m_scene_result = SceneBase::SceneResult::NewGame;
		m_is_scene_end = true;

		return;
	}

	// 設定が選択されたとき設定を開く
	if (m_p_menu_title->GetCurrentState() == MenuTitle::MenuTitleState::SelectedConfig)
	{
		if (Keyboard::IsTrigger(KEY_INPUT_ESCAPE) || m_config.GetIsCloseSelected())
		{
			m_config.SetIsCloseSelectedFalse();
			p_sound_manager->PlaySE(SoundManager::SeType::Cancel);
			m_config.SetConfigStateDefault();
			m_p_menu_title->SetCurrentStateDefault();

			return;
		}

		m_config.Update(game_setting, p_sound_manager);
	}

	// ゲーム終了が選択されたとき終了フラグを立てる
	if (m_p_menu_title->GetCurrentState() == MenuTitle::MenuTitleState::SelectedExit)
	{
		m_scene_result = SceneBase::SceneResult::ExitGame;
		m_is_scene_end = true;
	}
}

void SceneTitle::Draw()
{
	if (m_p_menu_title->GetCurrentState() == MenuTitle::MenuTitleState::SelectedConfig)
	{
		DrawGraph(0, 0, m_bg_handle, true);
		m_config.Draw();
	}
	else
	{
		DrawGraph(0, 0, m_bg_handle, true);
		DrawFormatStringToHandle(200, 200, GetColor(255, 255, 255), m_font_handle, "星のものがたり");
		m_p_menu_title->Draw();
	}
}