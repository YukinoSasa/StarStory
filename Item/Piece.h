#pragma once
#include <memory>
#include "../Math/Vec2.h"
#include "../Math/Rect.h"

class Stage;

/// <summary>
/// アイテムのピース(かけら)クラス
/// </summary>
class Piece
{
public:
	Piece();

	~Piece();

	// 初期化
	void Init();

	// 描画
	void Draw(Vec2 camera_pos);

	// 矩形のゲッタ
	Rect GetRect() const { return m_rect; }

	// 座標のセッタ
	void SetPos(float pos_x, float pos_y) { m_pos.x = pos_x; m_pos.y = pos_y; }

	// 自身が取得されたときに呼ばれる
	void Collect();

private:
	// 画像を読み込む変数
	int m_handle;

	// 画像の幅を保存する変数
	float m_handle_width;

	// 画像の高さを保存する変数
	float m_handle_height;

	// アイテムの中心座標
	Vec2 m_pos;

	// 当たり判定用矩形
	Rect m_rect;

	// 自身が取得されているかどうか
	bool m_is_collect;
};