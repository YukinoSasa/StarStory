#pragma once
#include <memory>
#include "../GameSetting.h"

class SceneBase;
class SoundManager;

/// <summary>
/// シーンを管理するクラス
/// </summary>
class SceneManager
{
public:
	SceneManager();

	~SceneManager();

	// 初期化
	void Init();

	// 更新
	void Update(GameSetting& game_setting);

	// 描画
	void Draw();

	// シーンを切り替える
	void ChangeScene(std::unique_ptr<SceneBase> next_scene);

	// シーンが終わったかどうかのゲッタ
	bool GetIsGameEnd() const { return m_is_game_end; }
	
	// シーンの状態を列挙
	enum class SceneState
	{
		Title,
		Play,
		Clear,
		Gameover,
	};

	// 現在のシーンのゲッタ
	SceneState GetCurrentSceneState() const { return m_scene_state; }

private:
	// 現在のシーンを保存する変数
	SceneState m_scene_state;

	// シーン遷移待機時間のカウント
	float m_wait_count;

	// 現在のシーンを表すポインタ
	std::unique_ptr<SceneBase> m_p_current_scene = nullptr;

	// サウンドマネージャーのポインタ
	std::shared_ptr<SoundManager> m_p_sound_manager = nullptr;

	// ゲームを終了するかどうか
	bool m_is_game_end;
};