#pragma once
#include "MenuBase.h"

class MenuTitle : public MenuBase
{
public:
	MenuTitle();

	~MenuTitle() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// ゲームが開始されたかどうかのゲッタ
	bool GetIsNewGame() { return m_is_newgame; }

private:
	// タイトルシーンのメニュー項目
	enum class MenuTitleItem
	{
		NewGame,
		Load,
		Config,
		Exit,
	};

	// 選択状態の項目
	MenuTitleItem m_selected_item;

	// ゲーム開始が押されたかどうか
	bool m_is_newgame;

	// 選択項目を指す●のy座標
	float m_item_y;
};