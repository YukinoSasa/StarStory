#include <DxLib.h>
#include "../csv/LoadCsv.h"
#include "StoryManager.h"

StoryManager::StoryManager()
{
	// 画像データの読み込み
	m_box_handle = LoadGraph("Data/UI/textbox.png");
	// ストーリーデータの読み込み
	m_story_datas = LoadStory("csv/Story.csv");
}

StoryManager::~StoryManager()
{
	// 画像データの削除
	DeleteGraph(m_box_handle);
}

void StoryManager::Init()
{

}

void StoryManager::Update()
{

}

void StoryManager::Draw()
{
	DrawGraphF(272.0f, 632.0f, m_box_handle, true);
	//DrawString(300.0f, 700.0f, m_story_datas[0].m_text, GetColor(255, 255, 255))
}