#pragma once
#include "EnemyManager.h"
#include "EnemyBase.h"

/// <summary>
/// コウモリクラス
/// </summary>
class Bat : public EnemyBase
{
public:
	Bat(EnemyData enemy_data);

	~Bat();

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw(Vec2 camera_pos) override;

private:
	// 索敵
	void TrackPlayer(Vec2 player_pos) override;

	// 初期位置に帰る
	void ReturnToInitPos() override;

	void UpdateAnimation();

	//// コウモリの状態の列挙
	//enum class BatState
	//{
	//	Idle,
	//	Track,
	//};

	//// 現在の状態
	//BatState m_current_state;

	//// プレイヤーを追跡中かどうか
	//bool m_is_tracking;

	// 画像データの配列
	int m_handle_array[9];
	//int m_idle_handle_array[3];

	// 初期位置
	Vec2 m_init_pos;

	// アニメーションフレーム
	int m_animation_frame;

	// アニメーションタイマー
	int m_animation_timer;
};