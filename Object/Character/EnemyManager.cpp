#include <DxLib.h>
#include "EnemyManager.h"
#include "Enemy.h"
#include "../../csv/LoadCsv.h"

EnemyManager::EnemyManager()
{
	// csvを読み込む
	m_enemy_datas = LoadEnemy("csv/Enemy.csv");

	for (auto& enemy_data : m_enemy_datas)
	{
		// 各エネミーのポインタを生成する
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(enemy_data);
		m_p_enemies.push_back(enemy);
	}
}

EnemyManager::~EnemyManager()
{

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