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

	// ギミックの移動量のゲッタ
	Vec2 GetGimmickMove() { return m_move; }

protected:
	// ギミックタイプ(1:箱、2:動く床(縦)、3:動く床(横))
	int m_gimmick_type;
};