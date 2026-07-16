#include <DxLib.h>
#include "SceneClear.h"

SceneClear::SceneClear()
{

}

void SceneClear::Init()
{

}

void SceneClear::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_is_scene_end = true;
	}
}

void SceneClear::Draw()
{
	DrawFormatString(500, 500, GetColor(255, 255, 255), "GAME CLEAR!!!");
	DrawFormatString(500, 600, GetColor(255, 255, 255), "Enter : Return to Title");
}