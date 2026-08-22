#pragma once
#include "GimmickBase.h"

/// <summary>
/// ギミックベースクラスを継承したセーブポイントクラス
/// </summary>
class SavePoint : public GimmickBase
{
public:
	SavePoint(GimmickData gimmick_data);

	~SavePoint();

	// 初期化
	void Init() override;

	//// 更新
	//void Update(Rect player_rect, Vec2 player_move) override;
};