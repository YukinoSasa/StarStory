#include <DxLib.h>
#include "../Story/StoryManager.h"
#include "SceneGameover.h"

SceneGameover::SceneGameover(GameData& game_data, std::shared_ptr<StoryManager> p_story_manager)
	:SceneBase(game_data, p_story_manager)
{

}

void SceneGameover::Init()
{

}

void SceneGameover::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_is_scene_end = true;
	}
}

void SceneGameover::Draw()
{
	DrawFormatString(500, 500, GetColor(255, 255, 255), "Gameover...");
	DrawFormatString(500, 600, GetColor(255, 255, 255), "Enter : Return to Title");
}