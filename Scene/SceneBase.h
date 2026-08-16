#pragma once
#include <memory>
#include "../GameSetting.h"

class SoundManager;

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase
{
public:
	SceneBase();

	virtual ~SceneBase() = default;

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager);

	// 描画
	virtual void Draw();

	// シーン状態のゲッタ
	bool GetIsSceneEnd() { return m_is_scene_end; }

	// シーン終了時の結果
	enum class SceneResult
	{
		None,
		NewGame,
		LoadGame,
		ExitGame,
		Clear,
		Gameover,
	};

protected:
	//// シーン終了時の結果
	//enum class SceneResult
	//{
	//	None,
	//	Clear,
	//	Gameover,
	//};

	// シーンが終了したかどうか
	bool m_is_scene_end;

	// シーンの終了結果を保存する変数
	SceneResult m_scene_result;

public:
	// シーンの終了状態のゲッタ
	SceneResult GetSceneResult() { return m_scene_result; }

};