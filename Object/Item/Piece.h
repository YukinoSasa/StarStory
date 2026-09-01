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

	// 更新
	void Update();

	// 描画
	void Draw(Vec2 camera_pos);

	// 取得されているかどうかのゲッタ
	bool GetIsCollected() const { return m_is_collect; }

	// 座標のセッタ
	void SetPos(float pos_x, float pos_y) { m_pos.x = pos_x; m_pos.y = pos_y; }

	// 自身が取得されたときに呼ばれる
	void Collect();

private:
	// 画像データの配列
	int m_handle_array[4];

	// 自身が取得されているかどうか
	bool m_is_collect;

	// アニメーションのタイマー
	int m_animation_timer;

	// アニメーションのフレーム
	int m_animation_frame;

	// アニメーション画像の更新
	void UpdateAnimation();
};