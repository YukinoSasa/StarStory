#include <DxLib.h>
#include "BackGround.h"

BackGround::BackGround()
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

void BackGround::Draw()
{
	DrawGraph(0, 72, m_Handle, true);
}