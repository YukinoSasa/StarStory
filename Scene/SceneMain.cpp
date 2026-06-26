
#include "SceneMain.h"
#include "../Character/Player.h"
#include "BackGround/BackGround.h"
#include "../Stage/Stage.h"
#include "../Character/Camera.h"

SceneMain::SceneMain()
{
	m_pPlayer = std::make_shared<Player>();
	m_pBackGround = std::make_shared<BackGround>();
	m_pStage = std::make_shared<Stage>();
	m_pCamera = std::make_shared<Camera>();
	m_pPlayer->SetStage(m_pStage);
	m_pCamera->SetPlayer(m_pPlayer);
	m_pStage->SetCamera(m_pCamera);
	
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
	m_pCamera->Update();
}

void SceneMain::Draw()
{
	m_pBackGround->Draw(m_pCamera->GetCameraPos());
	m_pPlayer->Draw(m_pCamera->GetCameraPos());
	m_pStage->Draw();
}
