#include <DxLib.h>
#include "Player.h"
#include "../Input/Pad.h"

namespace
{
	// プレイヤーの速度
	constexpr float K_SPEED = 1.0f;

	// ジャンプ力
	constexpr float K_JUMP_POWER = 15.0f;

	//// プレイヤーの幅
	//constexpr float K_PLAYER_WIDTH = 32.0f;

	//// プレイヤーの高さ
	//constexpr float K_PLAYER_HEIGHT = 32.0f;
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
	CharacterBase::Init();
}

void Player::Update()
{
	CharacterBase::Update();

	Move();
	Jump();

	//// プレイヤー座標を更新
	//m_Pos += m_Move;

	//// 矩形の端をセット
	//m_Rect.SetEdges(m_Pos.m_x, m_Pos.m_y, K_PLAYER_WIDTH, K_PLAYER_HEIGHT);
}

void Player::Draw()
{
	CharacterBase::Draw();
}

void Player::Move()
{
	// 移動量を計算
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// プレイヤーの向きを変更
		m_IsRight = false;

		m_Move.m_x -= K_SPEED;
	}
	else if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// プレイヤーの向きを変更
		m_IsRight = true;

		m_Move.m_x += K_SPEED;
	}
	else
	{
		m_Move.m_x = 0.0f;
	}
}

void Player::Jump()
{
	// 空中の場合以降の処理を行わない
	if (!m_IsGround)
	{
		return;
	}

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_Move.m_y -= K_JUMP_POWER;

		m_IsGround = false;
	}
}