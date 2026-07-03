#pragma once
#include "CharacterBase.h"

/// <summary>
/// キャラクタークラスを継承したプレイヤークラス
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
	void Draw(Vec2 camera_pos) override;

	// プレイヤー座標のゲッタ
	Vec2 GetPlayerPos() const { return m_pos; }

private:
	// 左右の移動量を計算
	void Move();

	// ジャンプ
	void Jump();

	// ゴールしているかどうか
	bool IsGoal();
};