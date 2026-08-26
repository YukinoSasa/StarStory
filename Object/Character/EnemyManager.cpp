#include <DxLib.h>
#include "../../csv/LoadCsv.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Bat.h"

EnemyManager::EnemyManager(int current_stage_num)
{
	// csvを読み込む
	m_enemy_datas = LoadEnemy("csv/Enemy.csv");

	for (auto& enemy_data : m_enemy_datas)
	{
		// 現在のステージのエネミーのみ生成する
		if (enemy_data.m_stage != current_stage_num)
		{
			continue;
		}

		std::shared_ptr<EnemyBase> enemy = nullptr;

		// 各エネミーのポインタを生成する
		switch (enemy_data.m_type)
		{
		// 巡回タイプの敵
		case 0:
		{
			enemy = std::make_shared<Enemy>(enemy_data);
			break;
		}
		// 追跡タイプの敵
		case 1:
		{
			enemy = std::make_shared<Bat>(enemy_data);
			break;
		}
		}

		m_p_enemies.push_back(enemy);
	}
}

void EnemyManager::Init()
{
	for (auto& enemy : m_p_enemies)
	{
		enemy->Init();
	}
	
}

void EnemyManager::Update()
{
	for (auto& enemy : m_p_enemies)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw(Vec2 camera_pos)
{
	//DrawFormatString(0, 30, GetColor(255, 255, 255), m_enemy_datas[0].m_file_pass.c_str());

	for (auto& enemy : m_p_enemies)
	{
		enemy->Draw(camera_pos);
	}
}