#pragma once
#include <string>
#include <vector>

// ストーリー情報の構造体
struct StoryData
{
	// ストーリーid
	int m_story_id;
	// 話者(0:プレイヤー)
	int m_speaker;
	// 文章
	std::string m_text;
};

// ストーリー情報をまとめた配列
using StoryDatas = std::vector<StoryData>;

/// <summary>
/// ストーリーを管理するクラス
/// </summary>
class StoryManager
{
public:
	StoryManager();

	~StoryManager();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();

	// ストーリー中かどうかのゲッタ
	bool GetIsPlayingStory() const { return m_is_playing_story; }

	// ストーリーの列挙
	enum class Story
	{
		Intro,
		One,
		Two,
		End,
	};

	// ストーリーを開始
	void PlayStory(Story play_story);

private:
	// テキストボックスのハンドル
	int m_box_handle;

	// テキストボックスのサイズ
	float m_box_width;
	float m_box_height;

	// ストーリーデータをまとめた配列
	StoryDatas m_story_datas;

	// 表示するストーリーテキスト
	std::string m_current_text;

	// 現在のストーリーのリスト
	StoryDatas m_current_story_list;

	// ストーリーインデックス(何文目か)
	int m_story_index;

	// ストーリーフォントのハンドル
	int m_story_font_handle;

	// ストーリー中かどうか
	bool m_is_playing_story;
};