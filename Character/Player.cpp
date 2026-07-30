#include <DxLib.h>
#include "Player.h"
#include "../Input/Pad.h"

namespace
{
	// プレイヤーの速度
	constexpr float PLAYER_SPEED = 5.0f;

	// ジャンプ力
	constexpr float PLAYER_JUMP_POWER = 15.0f;
}

Player::Player()
{
	m_handle = LoadGraph("Data/pl_kari.png");
}

Player::~Player()
{
	DeleteGraph(m_handle);
}

void Player::Init()
{
	CharacterBase::Init();
}

void Player::Update()
{
	// プレイヤー死亡の場合以降の処理を行わない
	if (!m_is_alive)
	{
		return;
	}

	Move();
	Jump();

	CharacterBase::Update();
}

void Player::Draw(Vec2 camera_pos)
{
	// プレイヤー死亡の場合以降の処理を行わない
	if (!m_is_alive)
	{
		return;
	}

	CharacterBase::Draw(camera_pos);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "PlayerPos : %f , %f", m_pos.x, m_pos.y);
}

void Player::Move()
{
	// 移動量を計算
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// プレイヤーの向きを変更
		m_is_right = false;

		m_move.x = -PLAYER_SPEED;
	}
	else if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// プレイヤーの向きを変更
		m_is_right = true;

		m_move.x = +PLAYER_SPEED;
	}
	else
	{
		m_move.x = 0.0f;
	}
}

void Player::Jump()
{
	// 空中の場合以降の処理を行わない
	if (!m_is_ground)
	{
		return;
	}

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_move.y -= PLAYER_JUMP_POWER;

		m_is_ground = false;
	}
}