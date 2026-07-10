#include "SceneMain.h"
#include "../Character/Player.h"
#include "../Character/Enemy.h"
#include "../Item/Piece.h"
#include "BackGround/BackGround.h"
#include "../Stage/Stage.h"
#include "../Character/Camera.h"
#include <DxLib.h>

SceneMain::SceneMain()
{
	m_p_player = std::make_shared<Player>();
	m_p_enemy = std::make_shared<Enemy>();
	//m_p_piece = std::make_shared<Piece>();
	m_p_background = std::make_shared<BackGround>();
	m_p_stage = std::make_shared<Stage>();
	m_p_camera = std::make_shared<Camera>();

	//m_p_pieces.resize(10);
	//for (auto& piece : m_p_pieces)
	//{
	//	piece = std::make_shared<Piece>();
	//}

	m_p_player->SetStage(m_p_stage);
	m_p_enemy->SetStage(m_p_stage);
	//m_p_piece->SetStage(m_p_stage);
	m_p_camera->SetPlayer(m_p_player);
	m_p_stage->SetCamera(m_p_camera);
	
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::Init()
{
	m_p_player->Init();
	m_p_enemy->Init();
	//m_p_piece->Init();
	m_p_background->Init();
	m_p_stage->Init();

	int index = 1;

	//for (auto& piece : m_p_pieces)
	//{
	//	piece->Init();
	//	piece->SetPos(10 * index * 10, 500.0f);

	//	index++;
	//}

}

void SceneMain::Update()
{
	m_p_player->Update();
	m_p_enemy->Update();
	m_p_camera->Update();
}

void SceneMain::Draw()
{
	m_p_background->Draw(m_p_camera->GetCameraPos(), m_p_stage->GetStageHeight());
	m_p_player->Draw(m_p_camera->GetCameraPos());
	m_p_enemy->Draw(m_p_camera->GetCameraPos());
	m_p_stage->Draw(m_p_camera->GetCameraPos());

	//for (auto& piece : m_p_pieces)
	//{
	//	piece->Draw(m_p_camera->GetCameraPos());
	//}
}
