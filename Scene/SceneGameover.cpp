#include <DxLib.h>
#include "SceneGameover.h"

SceneGameover::SceneGameover()
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