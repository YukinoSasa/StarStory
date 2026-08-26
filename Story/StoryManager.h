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

private:
	// テキストボックスのハンドル
	int m_box_handle;

	// ストーリーデータをまとめた配列
	StoryDatas m_story_datas;
};