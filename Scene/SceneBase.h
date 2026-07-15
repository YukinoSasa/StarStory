#pragma once

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
	virtual void Update();

	// 描画
	virtual void Draw();

	// シーン状態のゲッタ
	bool GetIsSceneEnd() { return m_is_scene_end; }

protected:
	// シーンが終了したかどうか
	bool m_is_scene_end;
};