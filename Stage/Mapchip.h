#pragma once
#include "../Math/Rect.h"
#include "../Math/Vec2.h"

/// <summary>
/// マップチップのクラス
/// </summary>
class Mapchip
{
public:
	Mapchip(float pos_x, float pos_y, int tile, bool is_collision);

	~Mapchip();

	// 初期化
	void Init();

	// 描画
	void Draw(Vec2 camera_pos, int* handle_array);

	// コリジョンを持つかどうかのゲッタ
	bool GetIsCollision() const { return m_is_collision; }

	// コリジョン矩形のゲッタ
	Rect GetRect() const { return m_rect; }

private:
	// 座標
	Vec2 m_pos;

	// コリジョン矩形
	Rect m_rect;

	// 描画するタイル番号
	int m_tile;

	// コリジョンを持つかどうか
	bool m_is_collision;
};