#pragma once
#include "Vec2.h"

/// <summary>
/// コリジョンの矩形クラス
/// </summary>
class Rect
{
public:
	Rect();

	// 確認用の矩形を描画
	void Draw(Vec2 camera_pos);

	// 矩形が接しているかどうか
	bool IsCollision(const Rect& object) const;

	bool IsCollisionX(const Rect& object) const;
	bool IsCollisionY(const Rect& object) const;

	// 各オブジェクトの中心座標(x, y)をもとに端の値を計算
	void CalculateEdges(float x, float y, float width, float height);

	// 矩形の左端xのゲッタ
	float GetLeftEdge() const { return m_left_edge; }

	// 矩形の右端xのゲッタ
	float GetRightEdge() const { return m_right_edge; }

	// 矩形の上端yのゲッタ
	float GetTopEdge() const { return m_top_edge; }

	// 矩形の下端yのゲッタ
	float GetBottomEdge() const { return m_bottom_edge; }

private:
	// 矩形の左端x
	float m_left_edge;

	// 矩形の右端x
	float m_right_edge;

	// 矩形の上端y
	float m_top_edge;

	// 矩形の下端y
	float m_bottom_edge;
};