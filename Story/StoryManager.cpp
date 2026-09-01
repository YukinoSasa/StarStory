#include <DxLib.h>
#include <algorithm>
#include "../GameConst.h"
#include "../csv/LoadCsv.h"
#include "../Input/Keyboard.h"
#include "StoryManager.h"

StoryManager::StoryManager()
	:m_box_width(0.0f), m_box_height(0.0f), m_current_text("null"), m_story_index(0),
	m_is_playing_story(false)
{
	// 画像データの読み込み
	m_box_handle = LoadGraph("Data/UI/textbox.png");
	// ストーリーデータの読み込み
	m_story_datas = LoadStory("csv/Story.csv");
	// フォントハンドルの作成
	m_story_font_handle = CreateFontToHandle("クラフト明朝", 36, -1);
}

StoryManager::~StoryManager()
{
	// 画像データの削除
	DeleteGraph(m_box_handle);
	// フォントの削除
	DeleteFontToHandle(m_story_font_handle);
}

void StoryManager::Init()
{
	GetGraphSizeF(m_box_handle, &m_box_width, &m_box_height);
}

void StoryManager::Update()
{
	if (m_is_playing_story && Keyboard::IsTrigger(KEY_INPUT_RETURN))
	{
		m_story_index++;

		if (m_story_index > m_current_story_list.size() - 1)
		{
			m_is_playing_story = false;

			return;
		}
		
		// 範囲外ではない時次の文を取得
		m_current_text = m_current_story_list[m_story_index].m_text;
	}
}

void StoryManager::Draw()
{
	// テキストボックスの描画座標を計算
	float draw_x = (Game::SCREEN_WIDTH - m_box_width) * 0.5f;
	float draw_y = Game::SCREEN_HEIGHT - m_box_height;
	DrawGraphF(draw_x, draw_y, m_box_handle, true);

	//// テキストの描画座標を計算
	//float draw_text_x = draw_x + 100.0f;
	//float draw_text_y = draw_y + 150.0f;
	//DrawFormatStringToHandle(draw_text_x, draw_text_y, GetColor(0, 105, 148),
	//	m_story_font_handle, m_current_text.c_str());

	DrawFormatStringToHandle(1400, 925, GetColor(0, 105, 148),
		m_story_font_handle, "Enter");

	// 話者によってフォントの色を変更
	switch (m_current_story_list[m_story_index].m_speaker)
	{
	// 主人公の場合
	case 0:
	{
		// [話者]の描画座標を計算
		float draw_speaker_x = draw_x + 100.0f;
		float draw_speaker_y = draw_y + 150.0f;
		DrawFormatStringToHandle(draw_speaker_x, draw_speaker_y, GetColor(0, 105, 148),
			m_story_font_handle, "【あなた】");

		// テキストの描画座標を計算
		float draw_text_x = draw_speaker_x;
		float draw_text_y = draw_speaker_y + 70.0f;
		DrawFormatStringToHandle(draw_text_x, draw_text_y, GetColor(0, 105, 148),
			m_story_font_handle, m_current_text.c_str());

		break;
	}
	// 王様の場合
	case 1:
	{
		// [話者]の描画座標を計算
		float draw_speaker_x = draw_x + 100.0f;
		float draw_speaker_y = draw_y + 150.0f;
		DrawFormatStringToHandle(draw_speaker_x, draw_speaker_y, GetColor(182, 0, 51),
			m_story_font_handle, "【王様】");

		// テキストの描画座標を計算
		float draw_text_x = draw_speaker_x;
		float draw_text_y = draw_speaker_y + 70.0f;
		DrawFormatStringToHandle(draw_text_x, draw_text_y, GetColor(182, 0, 51),
			m_story_font_handle, m_current_text.c_str());

		break;
	}
	}
}

void StoryManager::PlayStory(Story play_story)
{
	if (IsPlayed(play_story))
	{
		return;
	}

	m_is_playing_story = true;

	// 指定されたストーリーを設定する
	switch (play_story)
	{
	case Story::Intro:
	{
		m_current_story_list.clear();

		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_story_id == 0)
			{
				m_current_story_list.push_back(story_text);
			}
		}

		m_story_index = 0;
		m_current_text = m_current_story_list[m_story_index].m_text;

		m_played_story_datas.push_back(Story::Intro);

		break;
	}
	case Story::One:
	{
		m_current_story_list.clear();

		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_story_id == 1)
			{
				m_current_story_list.push_back(story_text);
			}
		}

		m_story_index = 0;
		m_current_text = m_current_story_list[m_story_index].m_text;

		m_played_story_datas.push_back(Story::One);

		break;
	}
	case Story::Two:
	{
		m_current_story_list.clear();

		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_story_id == 2)
			{
				m_current_story_list.push_back(story_text);
			}
		}

		m_story_index = 0;
		m_current_text = m_current_story_list[m_story_index].m_text;

		m_played_story_datas.push_back(Story::Two);

		break;
	}
	case Story::End:
	{
		m_current_story_list.clear();

		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_story_id == 3)
			{
				m_current_story_list.push_back(story_text);
			}


		}

		m_story_index = 0;
		m_current_text = m_current_story_list[m_story_index].m_text;

		m_played_story_datas.push_back(Story::End);

		break;
	}
	}
}

bool StoryManager::IsPlayed(Story play_story)
{
	// プレイ済みのリストに引数のストーリーがあるか検索
	auto it = std::find(m_played_story_datas.begin(), m_played_story_datas.end(), play_story);

	if (it != m_played_story_datas.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}