#pragma once
#include "SceneBase.h"

/// <summary>
/// シーンクラスを継承したゲームオーバークラス
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover();

	~SceneGameover() = default;

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();
};