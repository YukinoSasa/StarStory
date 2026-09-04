#include <DxLib.h>
#include "../Input/Keyboard.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	// BGMデータ読み込み
	m_title_bgm_handle = LoadSoundMem("Data/Sound/BGM/title.mp3");
	m_play_bgm_handle = LoadSoundMem("Data/Sound/BGM/play.mp3");
	m_end_bgm_handle = LoadSoundMem("Data/Sound/BGM/end.mp3");

	m_current_state = SceneManager::SceneState::Title;
	m_last_state = SceneManager::SceneState::Title;

	// SEデータ読み込み
	m_enter_handle = LoadSoundMem("Data/Sound/SE/enter.mp3");
	m_cancel_handle = LoadSoundMem("Data/Sound/SE/cancel.mp3");
	m_select_handle = LoadSoundMem("Data/Sound/SE/select.mp3");
	m_item_handle = LoadSoundMem("Data/Sound/SE/item.mp3");
	m_story_handle = LoadSoundMem("Data/Sound/SE/story.mp3");
	m_death_handle = LoadSoundMem("Data/Sound/SE/death.mp3");
}

SoundManager::~SoundManager()
{
	DeleteSoundMem(m_title_bgm_handle);
	DeleteSoundMem(m_play_bgm_handle);
	DeleteSoundMem(m_end_bgm_handle);
	DeleteSoundMem(m_enter_handle);
	DeleteSoundMem(m_cancel_handle);
	DeleteSoundMem(m_select_handle);
	DeleteSoundMem(m_item_handle);
	DeleteSoundMem(m_story_handle);
	DeleteSoundMem(m_death_handle);
}

void SoundManager::Init(SceneManager::SceneState current_scene)
{
	// 最初のBGMはタイトル用を再生
	PlaySoundMem(m_title_bgm_handle, DX_PLAYTYPE_LOOP);
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
			else if (m_last_state == SceneManager::SceneState::Clear)
			{
				StopSoundMem(m_end_bgm_handle);
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
		case SceneManager::SceneState::Clear:
		{
			StopSoundMem(m_play_bgm_handle);
			PlaySoundMem(m_end_bgm_handle, DX_PLAYTYPE_LOOP);
			break;
		}
		}
	}

	// BGMの音量調整(シーンによって調整するBGMを変更)
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
	case SceneManager::SceneState::Clear:
	{
		ChangeVolumeSoundMem(game_setting.m_volume_bgm, m_end_bgm_handle);
		break;
	}
	}

	// SEの音量調整
	ChangeVolumeSoundMem(game_setting.m_volume_se, m_enter_handle);
	ChangeVolumeSoundMem(game_setting.m_volume_se, m_cancel_handle);
	ChangeVolumeSoundMem(game_setting.m_volume_se, m_select_handle);
	ChangeVolumeSoundMem(game_setting.m_volume_se, m_item_handle);
	ChangeVolumeSoundMem(game_setting.m_volume_se, m_story_handle);
	ChangeVolumeSoundMem(game_setting.m_volume_se, m_death_handle);
}

void SoundManager::PlaySE(SeType se_type)
{
	// 呼び出し側で指定したSEを再生
	switch (se_type)
	{
	case SeType::Enter:
	{
		PlaySoundMem(m_enter_handle, DX_PLAYTYPE_BACK);
		break;
	}
	case SeType::Cancel:
	{
		PlaySoundMem(m_cancel_handle, DX_PLAYTYPE_BACK);
		break;
	}
	case SeType::Select:
	{
		PlaySoundMem(m_select_handle, DX_PLAYTYPE_BACK);
		break;
	}
	case SeType::Item:
	{
		PlaySoundMem(m_item_handle, DX_PLAYTYPE_BACK);
		break;
	}
	case SeType::Story:
	{
		PlaySoundMem(m_story_handle, DX_PLAYTYPE_BACK);
		break;
	}
	case SeType::Death:
	{
		PlaySoundMem(m_death_handle, DX_PLAYTYPE_BACK);
		break;
	}
	}
}