#pragma once
#include "../Math/Vec2.h"

/// <summary>
/// UIを管理するクラス
/// </summary>
class UIManager
{
public:
	UIManager();

	~UIManager();

	// 描画
	void Draw(Vec2 camera_pos, int collect_item);

	// 操作説明のUIを描画
	void DrawGuideUI(Vec2 camera_pos);

private:
	// 集めたアイテムのカウントUIの背景
	int m_collect_bg_handle;

	// UI星のかけらのハンドル
	int m_piece_ui_handle;

	// アイテムカウントのフォント
	int m_collect_font_handle;

	// 移動操作説明のUI
	int m_move_ui_handle;

	// ジャンプ操作説明のUI
	int m_jump_ui_handle;

	// 箱リセット操作説明のUI
	int m_reset_ui_handle;
};