
#include "SceneMain.h"
#include "../Character/Player.h"
#include "BackGround/BackGround.h"
#include "../Stage/Stage.h"

SceneMain::SceneMain()
{
	m_pPlayer = std::make_shared<Player>();
	m_pBackGround = std::make_shared<BackGround>();
	m_pStage = std::make_shared<Stage>();
	m_pPlayer->SetStage(m_pStage);
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
	m_pStage->Draw();
}
