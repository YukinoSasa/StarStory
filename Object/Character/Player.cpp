#include <DxLib.h>
#include "Player.h"
#include "../../Input/Pad.h"

namespace
{
	// プレイヤーの速度
	constexpr float PLAYER_SPEED = 5.0f;

	// ジャンプ力
	constexpr float PLAYER_JUMP_POWER = 15.0f;
}

Player::Player()
{
	LoadDivGraph("Data/player.png", 42, 8, 6, 24, 24, m_handle_array);
	m_handle = m_handle_array[0];

	m_animation_state = Animation::Idle;
	m_animation_timer = 0;
	m_animation_frame = 0;
}

Player::~Player()
{
	DeleteGraph(m_handle);
	for (int i = 0; i < sizeof(m_handle_array) / sizeof(m_handle_array[0]); i++)
	{
		DeleteGraph(m_handle_array[i]);
	}
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

	m_handle = m_handle_array[m_animation_frame];

	m_animation_timer++;
	if (m_animation_timer >= 5)
	{
		UpdateAnimation();
		m_animation_timer = 0;
	}
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
	DrawFormatString(0, 60, GetColor(255, 255, 255), "m_animation_frame : %d", m_animation_frame);
}

void Player::Move()
{
	// 移動量を計算
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_animation_state = Animation::Walk;

		// プレイヤーの向きを変更
		m_is_right = false;

		m_move.x = -PLAYER_SPEED;
	}
	else if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_animation_state = Animation::Walk;
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
		m_animation_state = Animation::Jamp;
		m_move.y -= PLAYER_JUMP_POWER;

		m_is_ground = false;
	}
}

void Player::UpdateAnimation()
{
	switch (m_animation_state)
	{
	case Animation::Idle:
	{
		break;
	}
	case Animation::Walk:
	{
		m_animation_frame++;
		if (m_animation_frame > 11)
		{
			m_animation_frame = 8;
		}
		break;
	}
	case Animation::Jamp:
	{
		break;
	}
	}
}