#pragma once
#include "MenuBase.h"

/// <summary>
/// メニューベースクラスを継承したタイトルメニュークラス
/// </summary>
class MenuTitle : public MenuBase
{
public:
	MenuTitle();

	~MenuTitle() override;

	// 更新
	void Update(std::shared_ptr<SoundManager> p_sound_manager) override;

	// 描画
	void Draw() override;

	// タイトルの状態
	enum class MenuTitleState
	{
		None,
		SelectedNewGame,
		SelectedConfig,
		SelectedExit,
	};

	// 現在の状態のゲッタ
	MenuTitleState GetCurrentState() const { return m_current_state; }

	// 現在の状態をデフォルトにするセッタ
	void SetCurrentStateDefault() { m_current_state = MenuTitleState::None; }

private:
	// タイトルシーンのメニュー項目
	enum class MenuTitleItem
	{
		NewGame,
		Config,
		Exit,
	};

	// 選択状態の項目
	MenuTitleItem m_selected_item;

	// 現在の状態
	MenuTitleState m_current_state;

	// メニュー項目のフォントハンドル
	int m_font_item_handle;

	// 選択状態の項目のフォントハンドル
	int m_font_selected_handle;
};