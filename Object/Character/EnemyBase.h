#pragma once
#include "CharacterBase.h"
#include "EnemyManager.h"

/// <summary>
/// キャラクタークラスを継承したエネミー基底クラス
/// </summary>
class EnemyBase : public CharacterBase
{
public:
	EnemyBase(EnemyData enemy_data);

	virtual ~EnemyBase() = 0;

	// 更新
	virtual void Update();

	// 描画
	void Draw(Vec2 camera_pos) override;

	// 索敵範囲の矩形のゲッタ
	Rect GetSearchRange() const { return m_search_range; }

	// プレイヤーを追跡
	virtual void TrackPlayer(Vec2 player_pos);

	// 初期座標に帰る
	virtual void ReturnToInitPos();

protected:
	// アニメーションの更新
	virtual void UpdateAnimation();

	// アニメーションの要素数
	int m_animation_elements;

	// アニメーションを更新するフレーム数
	int m_animation_update_frame;

	// 索敵範囲の矩形
	Rect m_search_range;
};