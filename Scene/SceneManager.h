#pragma once

#include <memory>

class SceneBase;

/// <summary>
/// シーンを管理するクラス
/// </summary>
class SceneManager
{
public:
	SceneManager();

	~SceneManager() = default;

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();

	// シーンを切り替える
	void ChangeScene(std::unique_ptr<SceneBase> next_scene);

private:
	// シーンの状態を列挙
	enum class SceneState
	{
		Title,
		Play,
		Clear,
	};

	// 現在のシーンを保存する変数
	SceneState m_scene_state;

	// シーン遷移待機時間のカウント
	float m_wait_count;

	// 現在のシーンを表すポインタ
	std::unique_ptr<SceneBase> m_p_current_scene = nullptr;
};