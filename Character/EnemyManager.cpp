#include "EnemyManager.h"
#include "../csv/LoadCsv.h"

EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Init()
{
	// csv‚ğ“Ç‚İ‚Ş
	m_enemies = LoadEnemy("csv/Enemy.csv");

}

void EnemyManager::Update()
{

}

void EnemyManager::Draw()
{

}