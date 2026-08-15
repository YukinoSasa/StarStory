#include <DxLib.h>
#include "../Input/Keyboard.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_title_bgm_handle = LoadSoundMem("Data/Sound/BGM/title.mp3");
	m_play_bgm_handle = LoadSoundMem("Data/Sound/BGM/play.mp3");
	m_current_state = SceneManager::SceneState::Title;
	m_last_state = SceneManager::SceneState::Title;

	m_enter_handle = LoadSoundMem("Data/Sound/SE/enter.mp3");
	m_cancel_handle = LoadSoundMem("Data/Sound/SE/cancel.mp3");
	m_select_handle = LoadSoundMem("Data/Sound/SE/select.mp3");
	m_item_handle = LoadSoundMem("Data/Sound/SE/item.mp3");

}

SoundManager::~SoundManager()
{
	DeleteSoundMem(m_title_bgm_handle);
	DeleteSoundMem(m_play_bgm_handle);
	DeleteSoundMem(m_enter_handle);
	DeleteSoundMem(m_cancel_handle);
	DeleteSoundMem(m_select_handle);
	DeleteSoundMem(m_item_handle);
}

void SoundManager::Init(SceneManager::SceneState current_scene)
{
	// シーンによって再生するBGMを変更
	PlaySoundMem(m_title_bgm_handle, DX_PLAYTYPE_LOOP);

	//switch (current_scene)
	//{
	//case SceneManager::SceneState::Title:
	//{
	//	PlaySoundMem(m_title_bgm_handle, DX_PLAYTYPE_LOOP);
	//	break;
	//}
	//case SceneManager::SceneState::Play:
	//{
	//	PlaySoundMem(m_play_bgm_handle, DX_PLAYTYPE_LOOP);
	//	break;
	//}
	//}
}

void SoundManager::Update(const GameSetting& game_setting, SceneManager::SceneState current_scene)
{
	// シーン情報の更新
	m_last_state = m_current_state;

	m_current_state = current_scene;

	// シーンが変わった際にBGM変更
	if (m_current_state != m_last_state)
	{
		switch (m_current_state)
		{
		case SceneManager::SceneState::Title:
		{
			if (m_last_state == SceneManager::SceneState::Play)
			{
				StopSoundMem(m_play_bgm_handle);
			}

			PlaySoundMem(m_title_bgm_handle, DX_PLAYTYPE_LOOP);
			break;
		}
		case SceneManager::SceneState::Play:
		{
			StopSoundMem(m_title_bgm_handle);
			PlaySoundMem(m_play_bgm_handle, DX_PLAYTYPE_LOOP);
			break;
		}
		}
	}

	// シーンによって調整するBGMを変更
	switch (current_scene)
	{
	case SceneManager::SceneState::Title:
	{
		ChangeVolumeSoundMem(game_setting.m_volume_bgm, m_title_bgm_handle);
		break;
	}
	case SceneManager::SceneState::Play:
	{
		ChangeVolumeSoundMem(game_setting.m_volume_bgm, m_play_bgm_handle);
		break;
	}
	}
}

//void SoundManager::PlaySE()
//{
//	PlaySoundMem(m_item_handle, DX_PLAYTYPE_LOOP);
//}