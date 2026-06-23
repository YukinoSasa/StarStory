#pragma once
#include "Vec2.h"

/// <summary>
/// 当たり判定の矩形クラス
/// </summary>
class Rect
{
public:
	Rect();

	~Rect();

	// 確認用の矩形を描画
	void Draw();

	// 矩形が接しているかどうか
	bool IsCollision(const Rect& object);

	// 各オブジェクトの中心座標(x, y)をもとに端の値をセット
	void SetEdges(float x, float y, float width, float height);

	// 矩形の左端xを取得
	float GetLeftEdge() const { return m_LeftEdge; }

	// 矩形の右端xを取得
	float GetRightEdge() const { return m_RightEdge; }

	// 矩形の上端yを取得
	float GetTopEdge() const { return m_TopEdge; }

	// 矩形の下端yを取得
	float GetBottomEdge() const { return m_BottomEdge; }


private:
	// 矩形の左端x
	float m_LeftEdge;

	// 矩形の右端x
	float m_RightEdge;

	// 矩形の上端y
	float m_TopEdge;

	// 矩形の下端y
	float m_BottomEdge;
};