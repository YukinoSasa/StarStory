#include <DxLib.h>
#include "BackGround.h"

BackGround::BackGround() :
	m_Pos(0.0f, 0.0f)
{
	m_Handle = LoadGraph("Data/BG_01.png");
}

BackGround::~BackGround()
{
	DeleteGraph(m_Handle);
}

void BackGround::Init()
{
	
}

void BackGround::Update()
{

}

void BackGround::Draw(Vec2 cameraPos)
{
	// スクリーン座標の計算
	float screenX = m_Pos.m_x - cameraPos.m_x + 960;
	float screenY = m_Pos.m_y - cameraPos.m_y + 540;
	DrawGraph(screenX, screenY, m_Handle, true);

	//int w, h;
	//GetDrawScreenSize(&w, &h);

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "Screen : %d x %d", w, h);
}