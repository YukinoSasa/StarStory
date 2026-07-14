#include <DxLib.h>
#include "Enemy.h"

namespace
{
	float MOVE_SPEED = 0.01f;
}

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

	if (m_is_ground)
	{
		m_move.x += MOVE_SPEED;

		m_pos.x += m_move.x;
	}
}

void Enemy::Draw(Vec2 camera_pos)
{
	CharacterBase::Draw(camera_pos);
}