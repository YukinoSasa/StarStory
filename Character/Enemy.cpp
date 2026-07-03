#include <DxLib.h>
#include "Enemy.h"

Enemy::Enemy()
{
	m_handle = LoadGraph("Data/enemy_kari.png");
}

Enemy::~Enemy()
{
	DeleteGraph(m_handle);
}

void Enemy::Init()
{
	CharacterBase::Init();
}

void Enemy::Update()
{
	CharacterBase::Update();
}

void Enemy::Draw(Vec2 camera_pos)
{
	CharacterBase::Draw(camera_pos);
}