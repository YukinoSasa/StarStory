#pragma once

/// <summary>
/// シーンのベースクラス
/// </summary>
class SceneBase
{
public:
	SceneBase();

	virtual ~SceneBase();

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update();

	// 描画
	virtual void Draw();
};