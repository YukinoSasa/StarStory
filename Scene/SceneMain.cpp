
#include "SceneMain.h"
#include "../Character/Player.h"

SceneMain::SceneMain()
{
	m_pPlayer = std::make_shared<Player>();
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
	m_pPlayer->Draw();
}
