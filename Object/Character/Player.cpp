#include <DxLib.h>
#include "../../GameConst.h"
#include "../../Input/Pad.h"
#include "Player.h"

namespace
{
	// プレイヤーの速度
	constexpr float PLAYER_SPEED = 5.0f;

	// ジャンプ力
	constexpr float PLAYER_JUMP_POWER = 12.0f;
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

	m_handle_width *= 3.0f;
	m_handle_height *= 3.0f;

	m_collision_width = 26.0f;
	m_collision_height = 48.0f;
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

	//CharacterBase::Draw(camera_pos);

	//	// 画像サイズ * 拡大率
	//float graph_width = m_handle_width * 3.0f;
	//float graph_height = m_handle_height * 3.0f;

	// キャラクター画像の左上の座標
	float draw_x = m_pos.x - m_handle_width * 0.5f;
	float draw_y = m_pos.y - m_handle_height * 0.5f;

	// キャラクター描画のスクリーン座標
	float screen_x = draw_x - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	float screen_y = draw_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	// キャラクターの向きによって画像を反転
	// 当たり判定矩形に合うように高さ調整
	if (m_is_right)
	{
		DrawExtendGraphF(
			screen_x , screen_y - 12.0f,
			screen_x + m_handle_width, screen_y + m_handle_height - 12.0f,
			m_handle, true);
	}
	else
	{
		DrawExtendGraphF(
			screen_x + m_handle_width, screen_y - 12.0f,
			screen_x , screen_y + m_handle_height - 12.0f,
			m_handle, true);
	}

#ifdef _DEBUG
	// デバック時のみ当たり判定の矩形を描画
	m_rect.Draw(camera_pos);
#endif

	DrawFormatString(0, 30, GetColor(255, 255, 255), "PlayerPos : %f , %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "m_is_ground : %d", m_is_ground);
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

void Player::MovePlayerX()
{
	m_pos.x += m_move.x;
	UpdateRect();
}

void Player::MovePlayerY()
{
	m_pos.y += m_move.y;
	UpdateRect();
}

void Player::UpdateRect()
{
	m_rect.CalculateEdges(m_pos.x - 1.0f, m_pos.y - 1.0f, m_collision_width, m_collision_height);
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

void Player::MoveWithPratform(float move)
{
	m_pos.x += move;
	UpdateRect();
}