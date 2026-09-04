#pragma once
#include "SceneBase.h"

class StoryManager;

/// <summary>
/// シーンクラスを継承したゲームオーバークラス
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover(GameData& game_data, std::shared_ptr<StoryManager> p_story_manager);

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();
};