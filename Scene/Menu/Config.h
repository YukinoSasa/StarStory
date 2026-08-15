#pragma once
#include "../../GameSetting.h"

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
	void Update(GameSetting& game_setting);

	// 描画
	void Draw();

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

	// BGM大きさ仮
	int m_volume_bgm;
};