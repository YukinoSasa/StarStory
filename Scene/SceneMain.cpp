#include "SceneMain.h"
#include "../Character/Player.h"
#include "BackGround/BackGround.h"
#include "../Stage/Stage.h"
#include "../Character/Camera.h"

SceneMain::SceneMain()
{
	m_p_player = std::make_shared<Player>();
	m_p_background = std::make_shared<BackGround>();
	m_p_stage = std::make_shared<Stage>();
	m_p_camera = std::make_shared<Camera>();
	m_p_player->SetStage(m_p_stage);
	m_p_camera->SetPlayer(m_p_player);
	m_p_stage->SetCamera(m_p_camera);
	
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::Init()
{
	m_p_player->Init();
	m_p_background->Init();
}

void SceneMain::Update()
{
	m_p_player->Update();
	m_p_camera->Update();
}

void SceneMain::Draw()
{
	m_p_background->Draw(m_p_camera->GetCameraPos());
	m_p_player->Draw(m_p_camera->GetCameraPos());
	m_p_stage->Draw(m_p_camera->GetCameraPos());
}
