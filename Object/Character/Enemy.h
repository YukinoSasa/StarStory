#pragma once
#include "CharacterBase.h"
#include "EnemyManager.h"

/// <summary>
/// キャラクタークラスを継承したエネミークラス
/// </summary>
class Enemy : public CharacterBase
{
public:
	Enemy(EnemyData enemy_data);

	~Enemy() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw(Vec2 camera_pos) override;

private:
	void UpdateAnimation();

	// 画像データの配列
	int m_handle_array[9];

	// アニメーションフレーム
	int m_animation_frame;

	// アニメーションタイマー
	int m_animation_timer;
};