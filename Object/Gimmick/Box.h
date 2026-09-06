#pragma once
#include "GimmickBase.h"

class Player;

/// <summary>
/// ギミックベースクラスを継承したボックスクラス
/// </summary>
class Box final : public GimmickBase
{
public:
	Box(GimmickData gimmick_data);

	~Box() override;

	// 初期化
	void Init() override;

	// 更新
	void Update();

	// 箱の移動
	void MoveByPush(Vec2 move) override;
};