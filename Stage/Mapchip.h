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

	// 更新
	void Update();

	// 描画
	void Draw(Vec2 camera_pos, int* handle_array);

	// コリジョンを持つかどうかのゲッタ
	bool GetIsCollision() const { return m_is_collision; }

	// 当たり判定矩形のゲッタ
	Rect GetRect() const { return m_rect; }

private:
	// 座標
	Vec2 m_pos;

	// 当たり判定矩形
	Rect m_rect;

	//// マップチップの画像データ配列
	//int m_handle_array[190];

	// 描画するタイル番号
	int m_tile;

	// 当たり判定を持つかどうか
	bool m_is_collision;
};