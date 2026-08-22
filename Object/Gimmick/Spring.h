#pragma once

#include "GimmickBase.h"

class Player;

/// <summary>
/// ギミックベースクラスを継承したスプリングクラス
/// </summary>
class Spring : public GimmickBase
{
public:
	Spring(GimmickData gimmick_data);

	~Spring() override;

	// 初期化
	void Init() override;

	// 更新
	void Update(Rect player_rect, Vec2 player_last_move);

	// スプリングのジャンプ力のゲッタ
	float GetSpringPower() const { return m_spring_power; }

private:
	// スプリングのジャンプ力
	float m_spring_power;
};