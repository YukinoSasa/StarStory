#pragma once
#include "GimmickBase.h"

/// <summary>
/// ギミックベースクラスを継承した動く床クラス
/// </summary>
class MovingPlatform final : public GimmickBase
{
public:
	MovingPlatform(GimmickData gimmick_data);

	~MovingPlatform();

	// 初期化
	void Init() override;

	// 更新
	void Update(Rect player_rect, Vec2 player_last_move) override;

private:
	// 床の初期座標を保存する変数
	Vec2 m_init_pos;
};