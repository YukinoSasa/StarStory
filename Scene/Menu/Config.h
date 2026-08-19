#pragma once
#include <memory>
#include "../../GameSetting.h"

class SoundManager;

/// <summary>
/// 音量設定を行う設定クラス
/// </summary>
class Config
{
public:
	Config();

	~Config();

	//初期化
	void Init();

	// 更新
	void Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager);

	// 描画
	void Draw();

	// 戻るが選択されたかどうかのゲッタ
	bool GetIsCloseSelected() const { return m_is_close_selected; }

	// 戻るが選択されたかどうかをfalseにするセッタ
	void SetIsCloseSelectedFalse() { m_is_close_selected = false; }


private:
	// コンフィグ画面の状態の列挙
	enum class ConfigState
	{
		BGM,
		SE,
		BACK,
	};

	// 現在の状態
	ConfigState m_current_state;

public:
	// 選択中の項目をデフォルトに戻すセッタ
	void SetConfigStateDefault() { m_current_state = ConfigState::BGM; }

private:
	// ポーズ背景のハンドル
	int m_handle_background;

	// 背景画像のサイズ
	float m_handle_width;
	float m_handle_height;

	// フォントのハンドル(タイトルサイズフォント)
	int m_font_handle;

	// フォントのハンドル(項目サイズフォント)
	int m_font_item_handle;
	
	// 設定を閉じるが選択されたかどうか
	bool m_is_close_selected;

	// スライダーのハンドル
	int m_slider_l_handle;
	int m_slider_m_handle;
	int m_slider_r_handle;

	// スライダーハンドルのハンドル
	int m_slider_handle;
	int m_slider_selected_handle;

	// スライダーハンドルの位置
	float m_slider_bgm_pos_x;
	float m_slider_se_pos_x;

	// BGM大きさ仮
	int m_volume_bgm;
	int m_volume_se;
};