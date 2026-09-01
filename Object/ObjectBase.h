#pragma once
#include "../Math/Rect.h"
#include "../Math/Vec2.h"

/// <summary>
/// オブジェクトの基底クラス
/// </summary>
class ObjectBase
{
public:
	ObjectBase();

	virtual ~ObjectBase() = 0;

	// コリジョン矩形のゲッタ
	const Rect GetRect() const { return m_rect; }

protected:
	// 画像を読み込む変数
	int m_handle;

	// 画像の幅を保存する変数
	float m_handle_width;

	// 画像の高さを保存する変数
	float m_handle_height;

	// コリジョンの幅を保存する変数
	float m_collision_width;

	// コリジョンの高さを保存する変数
	float m_collision_height;

	// 画像とコリジョンのオフセット
	Vec2 m_handle_offset;

	// オブジェクトの中心座標
	Vec2 m_pos;
	// オブジェクトの移動量
	Vec2 m_move;

	// コリジョン用矩形
	Rect m_rect;
};