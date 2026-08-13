#pragma once
#include "MenuBase.h"

/// <summary>
/// メニューベースクラスを継承したポーズクラス
/// </summary>
class MenuPause : public MenuBase
{
public:
	MenuPause();

	~MenuPause() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// 選択状態をデフォルトにするセッタ
	void SetSelectedItem();

private:
	// ポーズのメニュー項目
	enum class MenuPauseItem
	{
		ReturnToGame,
		Config,
		ReturnToTitle,
	};

	// 選択状態の項目
	MenuPauseItem m_selected_item;

	// ポーズ背景のハンドル
	int m_handle_background;

	// ポーズ背景の画像のサイズ
	float m_background_width;
	float m_background_height;

	// フォントのハンドル(タイトルサイズフォント)
	int m_font_handle;

	// フォントのハンドル(項目サイズフォント)
	int m_font_item_handle;

	// フォントのハンドル(選択状態)
	int m_font_item_selected_handle;

	//// ポーズが閉じられたかどうか
	//bool m_is_closed;
};