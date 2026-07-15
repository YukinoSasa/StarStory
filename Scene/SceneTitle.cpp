#include <DxLib.h>
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{

}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Init()
{

}

void SceneTitle::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_is_scene_end = true;
	}
}

void SceneTitle::Draw()
{
	DrawFormatString(500, 500, GetColor(255, 255, 255), "êØÇÃÇ‡ÇÃÇ™ÇΩÇË");
	DrawFormatString(500, 600, GetColor(255, 255, 255), "Press Enter Key");
}