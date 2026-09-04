#include "../Sound/SoundManager.h"
#include "../Story/StoryManager.h"
#include "SceneBase.h"

SceneBase::SceneBase(GameData& game_data, std::shared_ptr<StoryManager> p_story_manager)
	:m_is_scene_end(false), m_scene_result(SceneResult::None)
{

}

void SceneBase::Init()
{

}

void SceneBase::Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager)
{

}

void SceneBase::Draw()
{

}