#pragma once

#include "GimmickBase.h"

class Player;

/// <summary>
/// ギミックベースクラスを継承したボックスクラス
/// </summary>
class Box : public GimmickBase
{
public:
	Box(GimmickData gimmick_data);

	~Box() override;

	// 初期化
	void Init() override;

	// 更新
	void Update(Rect player_rect, Vec2 player_last_move);

private:
	// ステージとの当たり判定
	void CheckHitStage(Rect& chip_rect);
};