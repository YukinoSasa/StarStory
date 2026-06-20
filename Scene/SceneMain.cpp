
#include "SceneMain.h"
#include "../Character/Player.h"
#include "BackGround/BackGround.h"

SceneMain::SceneMain()
{
	m_pPlayer = std::make_shared<Player>();
	m_pBackGround = std::make_shared<BackGround>();
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::Init()
{
	m_pPlayer->Init();
}

void SceneMain::Update()
{
	m_pPlayer->Update();
}

void SceneMain::Draw()
{
	m_pBackGround->Draw();
	m_pPlayer->Draw();
}
