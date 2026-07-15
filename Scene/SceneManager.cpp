#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneMain.h"

SceneManager::SceneManager()
{
	m_p_current_scene = std::make_unique<SceneTitle>();
}

void SceneManager::Init()
{
	m_p_current_scene->Init();
}

void SceneManager::Update()
{
	m_p_current_scene->Update();

	if (m_p_current_scene->GetIsSceneEnd())
	{
		std::unique_ptr<SceneMain> p_scene_main = std::make_unique<SceneMain>();
		ChangeScene(std::move(p_scene_main));
	}
}

void SceneManager::Draw()
{
	m_p_current_scene->Draw();
}

void SceneManager::ChangeScene(std::unique_ptr<SceneBase> next_scene)
{
	if (!m_p_current_scene)
	{
		return;
	}

	m_p_current_scene = std::move(next_scene);
	m_p_current_scene->Init();
}