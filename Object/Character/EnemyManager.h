#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../../Math/Vec2.h"

class EnemyBase;

// エネミー1体の情報の構造体
struct EnemyData
{
	// ステージ番号
	int m_stage;
	// 敵タイプ(0:巡回、1:追跡)
	int m_type;
	// スポーン座標
	Vec2 m_spawn_pos;
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
	// 現在のステージのエネミーを生成する
	EnemyManager(int current_stage_num);

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw(Vec2 camera_pos);

	// エネミー配列のゲッタ
	std::vector<std::shared_ptr<EnemyBase>> GetEnemies() const { return m_p_enemies; }

private:
	// エネミーデータをまとめた配列
	EnemyDatas m_enemy_datas;

	// 生成したエネミー自体をまとめた配列
	std::vector<std::shared_ptr<EnemyBase>> m_p_enemies;
};