#include <DxLib.h>
#include <algorithm>
#include "../csv/LoadCsv.h"
#include "../GameConst.h"
#include "../Input/Keyboard.h"
#include "../Sound/SoundManager.h"
#include "StoryManager.h"

StoryManager::StoryManager(GameData& game_data)
	:m_box_width(0.0f), m_box_height(0.0f), m_current_text("null"), m_story_index(0),
	m_is_playing_story(false), m_game_data(game_data)
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
	m_played_story_datas.clear();
	GetGraphSizeF(m_box_handle, &m_box_width, &m_box_height);
}

void StoryManager::Update(std::shared_ptr<SoundManager> p_sound_manager)
{
	if (m_is_playing_story && Keyboard::IsTrigger(KEY_INPUT_RETURN))
	{
		p_sound_manager->PlaySE(SoundManager::SeType::Story);

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
			m_story_font_handle, m_current_text.c_str(), m_game_data.m_item_result);

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
		// 現在のストーリーリストに追加する
		m_current_story_list.clear();

		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_story_id == 0)
			{
				m_current_story_list.push_back(story_text);
			}
		}

		// 初めの文を現在のテキストに設定
		m_story_index = 0;
		m_current_text = m_current_story_list[m_story_index].m_text;

		m_played_story_datas.push_back(Story::Intro);

		break;
	}
	case Story::One:
	{
		// 現在のストーリーリストに追加する
		m_current_story_list.clear();

		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_story_id == 1)
			{
				m_current_story_list.push_back(story_text);
			}
		}

		// 初めの文を現在のテキストに設定
		m_story_index = 0;
		m_current_text = m_current_story_list[m_story_index].m_text;

		m_played_story_datas.push_back(Story::One);

		break;
	}
	case Story::Two:
	{
		// 現在のストーリーリストに追加する
		m_current_story_list.clear();

		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_story_id == 2)
			{
				m_current_story_list.push_back(story_text);
			}
		}

		// 初めの文を現在のテキストに設定
		m_story_index = 0;
		m_current_text = m_current_story_list[m_story_index].m_text;

		m_played_story_datas.push_back(Story::Two);

		break;
	}
	case Story::End:
	{
		// 現在のストーリーリストに追加する
		m_current_story_list.clear();

		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_story_id == 3 && story_text.m_end_branch == 0)
			{
				m_current_story_list.push_back(story_text);
			}
		}

		AddEndStory(m_current_story_list);

		// 初めの文を現在のテキストに設定
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

StoryManager::EndBranch StoryManager::DecisionEndBranch()
{
	// 星のかけら50個収集の場合
	if (m_game_data.m_item_result == GameData::STAR_MAX)
	{
		return EndBranch::Excellent;
	}
	// 星のかけら35～49個収集の場合
	else if (m_game_data.m_item_result >= GameData::STORY_TWO && m_game_data.m_item_result < GameData::STAR_MAX)
	{
		return EndBranch::Great;
	}
	// 星のかけら10～34個収集の場合
	else if (m_game_data.m_item_result >= GameData::STORY_ONE && m_game_data.m_item_result < GameData::STORY_TWO)
	{
		return EndBranch::Good;
	}
	// 星のかけら0～9個収集の場合
	else
	{
		return EndBranch::Nice;
	}
}

void StoryManager::AddEndStory(StoryDatas& current_story_list)
{
	// エンド分岐に応じたストーリーを分岐前ストーリーリストに追加する
	switch (DecisionEndBranch())
	{
	case EndBranch::Excellent:
	{
		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_end_branch == 1)
			{
				current_story_list.push_back(story_text);
			}
		}

		break;
	}
	case EndBranch::Great:
	{
		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_end_branch == 2)
			{
				current_story_list.push_back(story_text);
			}
		}

		break;
	}
	case EndBranch::Good:
	{
		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_end_branch == 3)
			{
				current_story_list.push_back(story_text);
			}
		}

		break;
	}
	case EndBranch::Nice:
	{
		for (auto& story_text : m_story_datas)
		{
			if (story_text.m_end_branch == 4)
			{
				current_story_list.push_back(story_text);
			}
		}

		break;
	}
	}
}