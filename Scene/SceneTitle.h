#pragma once

#include "SceneBase.h"

/// <summary>
/// シーンクラスを継承したタイトルシーンクラス
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();

	~SceneTitle() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;
};