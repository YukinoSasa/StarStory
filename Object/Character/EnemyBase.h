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

	virtual ~EnemyBase();

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update();

	// 描画
	virtual void Draw(Vec2 camera_pos);

	// 索敵範囲の矩形のゲッタ
	Rect GetSearchRange() const { return m_search_range; }

	// プレイヤーを追跡
	virtual void TrackPlayer(Vec2 player_pos);

	// 初期位置に帰る
	virtual void ReturnToInitPos();

protected:
	//// 分割前の元の画像データ
	//int m_original_handle;

	// 索敵範囲の矩形
	Rect m_search_range;
};