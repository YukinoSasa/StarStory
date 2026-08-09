#include <DxLib.h>
#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_title_bgm_handle = LoadSoundMem("Data/Sound/BGM/title.mp3");
}

SoundManager::~SoundManager()
{
	DeleteSoundMem(m_title_bgm_handle);
}

void SoundManager::Init()
{
	PlaySoundMem(m_title_bgm_handle, DX_PLAYTYPE_LOOP);
}

void SoundManager::Update()
{

}