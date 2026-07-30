#pragma once

#include "../Math/Rect.h"
#include "../Math/Vec2.h"
#include "GimmickManager.h"

/// <summary>
/// ギミックの基底クラス
/// </summary>
class GimmickBase
{
public:
	GimmickBase(GimmickData gimmick_data);

	virtual ~GimmickBase();

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update(Rect player_rect, Vec2 player_last_move);

	// 描画
	virtual void Draw(Vec2 camera_pos);

	// 当たり判定矩形のゲッタ
	const Rect GetRect() const { return m_rect; }

protected:
	// 画像を読み込む変数
	int m_handle;

	// 画像の幅を保存する変数
	float m_handle_width;

	// 画像の高さを保存する変数
	float m_handle_height;

	// ギミックの中心座標
	Vec2 m_pos;

	// ギミックの移動量
	Vec2 m_move;

	// 当たり判定用矩形
	Rect m_rect;
};