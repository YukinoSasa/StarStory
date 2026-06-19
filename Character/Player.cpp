#include <DxLib.h>
#include "Player.h"
#include "../Input/Pad.h"

namespace
{
	// プレイヤーの速度
	constexpr float K_SPEED = 2.0f;
}

Player::Player()
{
	m_Handle = LoadGraph("Data/pl_kari.png");
}

Player::~Player()
{
	DeleteGraph(m_Handle);
}

void Player::Init()
{

}

void Player::Update()
{
	Move();

	// プレイヤー座標を更新
	m_Pos += m_Move;
}

void Player::Draw()
{
	DrawGraph(m_Pos.m_x, m_Pos.m_y, m_Handle, true);
}

void Player::Move()
{
	// 移動量を計算
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_Move.m_x -= K_SPEED;
	}
	else if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_Move.m_x += K_SPEED;
	}
	else
	{
		m_Move.m_x = 0.0f;
	}
}