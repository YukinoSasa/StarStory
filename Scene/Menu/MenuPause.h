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

	// ポーズの状態
	enum class MenuPauseState
	{
		None,
		SelectedReturnToGame,
		SelectedConfig,
		SelectedReturnToTitle,
	};

	// 現在のポーズ状態のゲッタ
	MenuPauseState GetCurrentState() const { return m_current_state; }

	// 選択状態をデフォルトにするセッタ
	void SetSelectedItem();

	// 現在のポーズ状態をデフォルトにするセッタ
	void SetCurrentStateDefault() { m_current_state = MenuPauseState::None; }

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

	// 現在の状態
	MenuPauseState m_current_state;

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
};