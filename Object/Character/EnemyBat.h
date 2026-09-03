#pragma once
#include "EnemyBase.h"

/// <summary>
/// コウモリクラス
/// </summary>
class EnemyBat final : public EnemyBase
{
public:
	EnemyBat(EnemyData enemy_data);

	~EnemyBat();

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw(Vec2 camera_pos) override;

private:
	// 索敵
	void TrackPlayer(Vec2 player_pos) override;

	// 初期座標に帰る
	void ReturnToInitPos() override;

	// 画像データの配列
	int m_handle_array[9];

	// 索敵範囲の画像ハンドル
	int m_search_handle;

	// 初期座標
	Vec2 m_init_pos;

	// 追跡中かどうか
	bool m_is_tracking;
};