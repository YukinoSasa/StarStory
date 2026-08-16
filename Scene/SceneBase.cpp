#include "../Sound/SoundManager.h"
#include "SceneBase.h"

SceneBase::SceneBase() :
	m_is_scene_end(false), m_scene_result(SceneResult::None)
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