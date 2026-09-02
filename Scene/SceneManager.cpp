#include <DxLib.h>
#include "../Sound/SoundManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneManager.h"


namespace
{
	// シーン遷移の待機時間
	float WAIT_TIME = 120.0f;
}

SceneManager::SceneManager() :
	m_wait_count(0.0f), m_is_game_end(false)
{
	m_p_current_scene = std::make_unique<SceneTitle>();
	m_scene_state = SceneState::Title;

	m_p_sound_manager = std::make_shared<SoundManager>();
}

SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	m_p_current_scene->Init();
	m_p_sound_manager->Init(m_scene_state);
}

void SceneManager::Update(GameSetting& game_setting)
{
	m_p_sound_manager->Update(game_setting, m_scene_state);
	m_p_current_scene->Update(game_setting, m_p_sound_manager);

	if (m_p_current_scene->GetIsSceneEnd())
	{
		m_wait_count++;

		if (m_wait_count >= WAIT_TIME)
		{
			switch (m_scene_state)
			{
			case SceneState::Title:
			{
				// 現在のSceneStateがTitleの場合、シーン終了結果がNewGameの場合、Playへ遷移
				switch (m_p_current_scene->GetSceneResult())
				{
				case SceneBase::SceneResult::NewGame:
				{
					std::unique_ptr<SceneMain> p_scene_main = std::make_unique<SceneMain>();
					ChangeScene(std::move(p_scene_main));
					m_scene_state = SceneState::Play;
					m_wait_count = 0.0f;

					break;
				}
				case SceneBase::SceneResult::ExitGame:
				{
					m_is_game_end = true;
					break;
				}
				}

				break;
			}
			case SceneState::Play:
			{
				switch (m_p_current_scene->GetSceneResult())
				{
				// 現在のSceneStateがPlayの場合、シーン終了結果がNoneの場合、Titleへ遷移
				case SceneBase::SceneResult::None:
				{
					std::unique_ptr<SceneTitle> p_scene_title = std::make_unique<SceneTitle>();
					ChangeScene(std::move(p_scene_title));
					m_scene_state = SceneState::Title;
					m_wait_count = 0.0f;
					break;
				}
				// 現在のSceneStateがPlayの場合、シーン終了結果がClearの場合、Clearへ遷移
				case SceneBase::SceneResult::Clear:
				{
					std::unique_ptr<SceneClear> p_scene_clear = std::make_unique<SceneClear>();
					ChangeScene(std::move(p_scene_clear));
					m_scene_state = SceneState::Clear;
					m_wait_count = 0.0f;
					break;
				}
				// 現在のSceneStateがPlayの場合、シーン終了結果がGameoverの場合、Gameoverへ遷移
				case SceneBase::SceneResult::Gameover:
				{
					std::unique_ptr<SceneGameover> p_scene_gameover = std::make_unique<SceneGameover>();
					ChangeScene(std::move(p_scene_gameover));
					m_scene_state = SceneState::Gameover;
					m_wait_count = 0.0f;
					break;
				}
				}
				break;
			}
			case SceneState::Clear:
			{
				// 現在のSceneStateがClearの場合、Titleへ遷移
				std::unique_ptr<SceneTitle> p_scene_title = std::make_unique<SceneTitle>();
				ChangeScene(std::move(p_scene_title));
				m_scene_state = SceneState::Title;
				m_wait_count = 0.0f;
				break;
			}
			case SceneState::Gameover:
			{
				// 現在のSceneStateがGameoverの場合、Titleへ遷移
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