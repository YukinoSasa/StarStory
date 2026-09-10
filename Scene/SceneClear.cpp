#include <DxLib.h>
#include "../GameConst.h"
#include "../GameData.h"
#include "../Input/Keyboard.h"
#include "../Story/StoryManager.h"
#include "SceneClear.h"

namespace
{
	// ストーリーを開始するフレームカウント
	int intro_count = 0;

	// アニメーションを更新するフレーム
	int animation_update_frame = 15;
}

SceneClear::SceneClear(GameData& game_data, std::shared_ptr<StoryManager> p_story_manager)
	:SceneBase(game_data, p_story_manager), m_animation_timer(0), m_animation_frame(0), m_is_played_story(false)
{
	m_p_story_manager = p_story_manager;

	m_background_handle = LoadGraph("Data/Graph/clear_bg.png");
	m_end_handle = LoadGraph("Data/Graph/end_bg.png");
	LoadDivGraph("Data/Graph/player_story.png", 2, 2, 1, 72, 72, m_player_handle);
	LoadDivGraph("Data/Graph/king.png", 2, 2, 1, 72, 72, m_king_handle);
	m_endfont_handle = CreateFontToHandle("クラフト明朝", 48, -1);
	m_font_handle = CreateFontToHandle("クラフト明朝", 32, -1);

	m_item_result = game_data.m_item_result;
}

SceneClear::~SceneClear()
{
	DeleteGraph(m_background_handle);
	DeleteGraph(m_end_handle);

	for (int i = 0; i < sizeof(m_player_handle) / sizeof(m_player_handle[0]); i++)
	{
		DeleteGraph(m_player_handle[i]);
	}

	for (int i = 0; i < sizeof(m_king_handle) / sizeof(m_king_handle[0]); i++)
	{
		DeleteGraph(m_king_handle[i]);
	}

	DeleteFontToHandle(m_endfont_handle);
	DeleteFontToHandle(m_font_handle);
}

void SceneClear::Init()
{
	m_p_story_manager->Init();
}

void SceneClear::Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager)
{
	// SceneClearに遷移後1フレーム待ってからストーリー再生
	intro_count++;
	if (intro_count > 1)
	{
		m_p_story_manager->PlayStory(StoryManager::Story::End);
		m_is_played_story = true;
	}

	// キャラクターのアニメーション
	m_animation_timer++;
	if (m_animation_timer >= animation_update_frame)
	{
		UpdateAnimation();
		m_animation_timer = 0;
	}

	if (m_p_story_manager->GetIsPlayingStory())
	{
		m_p_story_manager->Update(p_sound_manager);
		return;
	}

	if (!m_p_story_manager->GetIsPlayingStory() && m_is_played_story && Keyboard::IsTrigger(KEY_INPUT_RETURN))
	{
		m_is_scene_end = true;
	}
}

void SceneClear::Draw()
{
	DrawGraphF(0.0f, 0.0f, m_background_handle, true);

	DrawGraphF(300.0f, 500.0f, m_player_handle[m_animation_frame], true);
	DrawGraphF(1500.0f, 500.0f, m_king_handle[m_animation_frame], true);

	if (m_p_story_manager->GetIsPlayingStory())
	{
		m_p_story_manager->Draw();
		return;
	}

	if (m_is_played_story)
	{
		DrawGraphF(0.0f, 0.0f, m_end_handle, true);

		// 文字列のサイズを取得
		int width = GetDrawFormatStringWidthToHandle(m_endfont_handle, "おしまい");
		// 文字列の描画座標を計算
		float draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		float draw_y = Game::SCREEN_HEIGHT * 0.5f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(0, 105, 148), m_endfont_handle, "おしまい");

		// 文字列のサイズを取得
		width = GetDrawFormatStringWidthToHandle(m_font_handle, "Enterでタイトルへ");
		// 文字列の描画座標を計算
		draw_x = (Game::SCREEN_WIDTH - width) * 0.5f;
		draw_y += 70.0f;

		DrawFormatStringToHandle(draw_x, draw_y, GetColor(0, 105, 148), m_font_handle, "Enterでタイトルへ");
	}
}

void SceneClear::UpdateAnimation()
{
	m_animation_frame++;

	if (m_animation_frame > 1)
	{
		m_animation_frame = 0;
	}
}