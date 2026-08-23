#pragma once
#include "EnemyManager.h"

/// <summary>
/// コウモリクラス
/// </summary>
class Bat
{
public:
	Bat(EnemyData enemy_data);

	~Bat();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();
};