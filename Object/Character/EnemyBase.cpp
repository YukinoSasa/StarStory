#include <DxLib.h>
#include "EnemyBase.h"

EnemyBase::EnemyBase(EnemyData enemy_data)
{
	//m_original_handle = LoadGraph(enemy_data.m_file_pass.c_str());
	// 敵のタイプcsvにもスクリプトにも追加する！！！１
	m_pos = enemy_data.m_spawn;
	m_handle_width = enemy_data.m_size;
	m_handle_height = enemy_data.m_size;
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Init()
{
	CharacterBase::Init();
}

void EnemyBase::Update()
{

}

void EnemyBase::Draw()
{

}