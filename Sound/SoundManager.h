#pragma once
#include "../GameSetting.h"
#include "../Scene/SceneManager.h"

/// <summary>
/// サウンドを管理するクラス
/// </summary>
class SoundManager
{
public:
	SoundManager();

	~SoundManager();

	// 初期化
	void Init(SceneManager::SceneState current_scene);

	// 更新
	void Update(const GameSetting& game_setting, SceneManager::SceneState current_scene);

	enum class SeType
	{
		Enter,
		Cancel,
		Select,
		Item,
	};

	// SEを再生
	void PlaySE(SeType se_type);

private:
	// BGMのハンドル
	int m_title_bgm_handle;
	int m_play_bgm_handle;
	int m_end_bgm_handle;

	// SEのハンドル
	int m_enter_handle;
	int m_cancel_handle;
	int m_select_handle;
	int m_item_handle;

	// 現在のシーン
	SceneManager::SceneState m_current_state;
	// 前回のフレームのシーン
	SceneManager::SceneState m_last_state;
};