#include <DxLib.h>
#include "BackGround.h"

BackGround::BackGround() :
	m_Pos(0.0f, 0.0f), m_HandleWidth(0), m_HandleHeight(0)
{
	m_HandleGround = LoadGraph("Data/BG_01.png");
	m_HandleSky1 = LoadGraph("Data/BG_02.png");
}

BackGround::~BackGround()
{
	DeleteGraph(m_HandleGround);
	DeleteGraph(m_HandleSky1);
}

void BackGround::Init()
{
	GetGraphSize(m_HandleGround, &m_HandleWidth, &m_HandleHeight);
}

void BackGround::Update()
{

}

void BackGround::Draw(Vec2 cameraPos)
{
	// 背景ループ


	// スクリーン座標の計算
	float screenX = m_Pos.m_x - cameraPos.m_x + 960;
	float screenY = m_Pos.m_y - cameraPos.m_y + 540;
	DrawGraph(screenX, screenY, m_HandleGround, true);

	//int w, h;
	//GetDrawScreenSize(&w, &h);

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "Screen : %d x %d", w, h);
}