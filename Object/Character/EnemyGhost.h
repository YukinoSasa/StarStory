#pragma once
#include "EnemyBase.h"

/// <summary>
/// ゴーストクラス
/// </summary>
class EnemyGhost final : public EnemyBase
{
public:
	EnemyGhost(EnemyData enemy_data);

	~EnemyGhost() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

private:
	// 画像データの配列
	int m_handle_array[9];
};