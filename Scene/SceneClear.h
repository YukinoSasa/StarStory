#pragma once

#include "SceneBase.h"

/// <summary>
/// シーンクラスを継承したクリアシーンクラス
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();

	~SceneClear() = default;

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();
};