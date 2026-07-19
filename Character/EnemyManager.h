#pragma once

#include <string>
#include <vector>
#include "../Math/Vec2.h"

// 敵1体の情報の構造体
struct EnemyData
{
	// ステージ番号
	int m_stage;
	// スポーン座標
	Vec2 m_spawn;
	// 敵サイズ
	float m_size;
	// 素材データ
	std::string m_file_pass;
};

// エネミーデータのvector配列
using EnemyDatas = std::vector<EnemyData>;


/// <summary>
/// エネミーを管理するクラス
/// </summary>
class EnemyManager
{
public:
	EnemyManager();

	~EnemyManager();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	EnemyDatas m_enemies;
};