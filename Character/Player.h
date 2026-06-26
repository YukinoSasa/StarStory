#pragma once
#include "CharacterBase.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public CharacterBase
{
public:
	Player();

	~Player() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// プレイヤー座標のゲッタ
	Vec2 GetPlayerPos() const { return m_Pos; }

private:
	// 左右の移動量を計算
	void Move();

	// ジャンプ
	void Jump();
};