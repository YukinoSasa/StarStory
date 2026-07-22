#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../Math/Vec2.h"

class Enemy;

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
	void Draw(Vec2 camera_pos);

	// エネミー配列のゲッタ
	std::vector<std::shared_ptr<Enemy>> GetEnemies() const { return m_p_enemies; }

private:
	// エネミーデータをまとめた配列
	EnemyDatas m_enemy_datas;

	// エネミー自体をまとめた配列
	std::vector<std::shared_ptr<Enemy>> m_p_enemies;

	// アクティブ状態のエネミーをまとめた配列？
};