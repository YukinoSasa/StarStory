#include <DxLib.h>
#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"

namespace
{
	// ƒV[ƒ“‘JˆÚ‚Ì‘Ò‹@ŠÔ
	float WAIT_TIME = 120.0f;
}

SceneManager::SceneManager() :
	m_wait_count(0.0f)
{
	m_p_current_scene = std::make_unique<SceneTitle>();
	m_scene_state = SceneState::Title;
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
		m_wait_count++;

		if (m_wait_count >= WAIT_TIME)
		{
			switch (m_scene_state)
			{
			case SceneState::Title:
			{
				// Œ»İ‚ÌSceneState‚ªTitle‚Ìê‡APlay‚Ö‘JˆÚ
				std::unique_ptr<SceneMain> p_scene_main = std::make_unique<SceneMain>();
				ChangeScene(std::move(p_scene_main));
				m_scene_state = SceneState::Play;
				m_wait_count = 0.0f;
				break;
			}
			case SceneState::Play:
			{
				// Œ»İ‚ÌSceneState‚ªPlay‚Ìê‡AClear‚Ö‘JˆÚ
				std::unique_ptr<SceneClear> p_scene_clear = std::make_unique<SceneClear>();
				ChangeScene(std::move(p_scene_clear));
				m_scene_state = SceneState::Clear;
				m_wait_count = 0.0f;
				break;
			}
			case SceneState::Clear:
			{
				// Œ»İ‚ÌSceneState‚ªClear‚Ìê‡ATitle‚Ö‘JˆÚ
				std::unique_ptr<SceneTitle> p_scene_title = std::make_unique<SceneTitle>();
				ChangeScene(std::move(p_scene_title));
				m_scene_state = SceneState::Title;
				m_wait_count = 0.0f;
				break;
			}
			}
		}
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