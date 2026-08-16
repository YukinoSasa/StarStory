#pragma once
#include "../ObjectBase.h"
#include "GimmickManager.h"

/// <summary>
/// ギミックの基底クラス
/// </summary>
class GimmickBase : public ObjectBase
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

	// ギミックタイプのゲッタ
	int GetGimmickType() const { return m_gimmick_type; }

	// ギミックの座標のゲッタ
	Vec2 GetGimmickPos() const { return m_pos; }

	// ギミックの移動量のゲッタ
	Vec2 GetGimmickMove() const { return m_move; }

	// コリジョン高さのゲッタ
	float GetCollisionHeight() const { return m_collision_height; }

	// ギミックのy座標のセッタ
	void SetGimmickPosY(float pos_y) { m_pos.y = pos_y; }

	// ギミックの移動量のセッタ
	void SetGimmickMove(float move_x, float move_y) { m_move.x = move_x; m_move.y = move_y; }

	// 当たり判定の更新
	void UpdateRect();

	// 押されたら動く
	virtual void MoveByPush(Vec2 move);

protected:
	// ギミックタイプ(0:セーブポイント、1:箱、2:動く床(縦)、3:動く床(横))
	int m_gimmick_type;

	//// 画像のオフセット
	//Vec2 m_handle_offset;
};