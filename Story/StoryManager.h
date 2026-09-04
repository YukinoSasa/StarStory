#pragma once
#include <string>
#include <vector>
#include "../GameData.h"

// ストーリー情報の構造体
struct StoryData
{
	// ストーリーid
	int m_story_id;
	// 話者(0:プレイヤー)
	int m_speaker;
	// エンド分岐
	int m_end_branch;
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
	StoryManager(GameData& game_data);

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
	// ストーリーが再生済みかどうか
	bool IsPlayed(Story play_story);

	// エンド分岐
	enum class EndBranch
	{
		// 星のかけら50個収集
		Excellent,
		// 星のかけら35～49個収集
		Great,
		// 星のかけら10～34個収集
		Good,
		// 星のかけら0～9個収集
		Nice,
	};

	// 再生するエンドストーリーを決める
	EndBranch DecisionEndBranch();

	// エンドシーンのストーリーを追加
	void AddEndStory(StoryDatas& current_story_list);

	// テキストボックスのハンドル
	int m_box_handle;

	// テキストボックスのサイズ
	float m_box_width;
	float m_box_height;

	// ストーリーデータをまとめた配列
	StoryDatas m_story_datas;

	// 再生済みのストーリーをまとめる配列
	std::vector<Story> m_played_story_datas;

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

	// ゲームデータの参照
	GameData& m_game_data;
};