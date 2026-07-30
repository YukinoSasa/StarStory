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
};