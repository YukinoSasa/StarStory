#pragma once
#include "../Story/StoryManager.h"
#include "../GameData.h"
#include "SceneBase.h"

/// <summary>
/// シーンクラスを継承したクリアシーンクラス
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();

	~SceneClear() override;

	// 初期化
	void Init() override;

	// 更新
	void Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager) override;

	// 描画
	void Draw() override;

private:
	// アニメーションの更新
	void UpdateAnimation();

	// 背景画像のハンドル
	int m_background_handle;
	// エンド画像ハンドル
	int m_end_handle;

	// ストーリーマネージャー
	StoryManager m_story_manager;

	// プレイヤーの画像ハンドル
	int m_player_handle[2];

	// 王様の画像ハンドル
	int m_king_handle[2];

	// フォントハンドル
	int m_endfont_handle;
	int m_font_handle;

	// アニメーションタイマー
	int m_animation_timer;

	// 表示する画像
	int m_animation_frame;

	// ストーリーが終わったかどうか
	bool m_is_played_story;
};