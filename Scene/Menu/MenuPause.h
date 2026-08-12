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

	//// ポーズが閉じられたかどうかのゲッタ
	//bool GetIsClosed() const { return m_is_closed; }

	//void SetIsClosed(bool is_closed) { m_is_closed = is_closed; }

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

	// フォントのハンドル(タイトルサイズフォント)
	int m_font_handle;

	// フォントのハンドル(項目サイズフォント)
	int m_font_item_handle;

	// フォントのハンドル(選択状態)

	//// ポーズが閉じられたかどうか
	//bool m_is_closed;
};