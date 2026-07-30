#pragma once
#include <memory>
#include <vector>
#include "../ObjectBase.h"
#include "ItemManager.h"

/// <summary>
/// アイテムのピース(かけら)クラス
/// </summary>
class Piece : public ObjectBase
{
public:
	Piece(ItemData item_data);

	~Piece();

	// 初期化
	void Init();

	// 描画
	void Draw(Vec2 camera_pos);

	// 座標のセッタ
	void SetPos(float pos_x, float pos_y) { m_pos.x = pos_x; m_pos.y = pos_y; }

	// 自身が取得されたときに呼ばれる
	void Collect();

private:
	// 自身が取得されているかどうか
	bool m_is_collect;
};