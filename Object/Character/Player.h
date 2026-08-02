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

	// プレイヤー幅のゲッタ
	float GetPlayerWidth() const { return m_handle_width; }

	// プレイヤー高さのゲッタ
	float GetPlayerHeight() const { return m_handle_height; }

	// プレイヤーの移動量のゲッタ
	Vec2 GetPlayerLastMove() const { return m_last_move; }

	// プレイヤー座標のセッタ
	void SetPlayerPos(float player_pos_x, float player_pos_y) {
		m_pos.x = player_pos_x; m_pos.y = player_pos_y;
	}

private:
	// 左右の移動量を計算
	void Move();

	// ジャンプ
	void Jump();

	// 画像データ配列
	int m_handle_array[42];

	//// 敵との当たり判定
	//void CheckHitEnemy(Rect& enemy_rect);

	// アニメーションの状態
	enum class Animation
	{
		Idle,
		Walk,
		Jamp,
		Fall,
		Dead,
	};

	// アニメーションの状態を保存する変数
	Animation m_animation_state;

	// アニメーションのタイマー
	int m_animation_timer;

	// アニメーションのフレーム
	int m_animation_frame;

	// アニメーション画像の更新
	void UpdateAnimation();
};