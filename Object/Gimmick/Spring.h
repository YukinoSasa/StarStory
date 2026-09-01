#pragma once
#include "GimmickBase.h"

class Player;

/// <summary>
/// ギミックベースクラスを継承したスプリングクラス
/// </summary>
class Spring final : public GimmickBase
{
public:
	Spring(GimmickData gimmick_data);

	~Spring() override;

	// 初期化
	void Init() override;

	// スプリングのジャンプ力のゲッタ
	float GetSpringPower() const { return m_spring_power; }

private:
	// スプリングのジャンプ力
	float m_spring_power;
};