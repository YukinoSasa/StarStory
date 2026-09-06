#include <DxLib.h>
#include "../../GameConst.h"
#include "../../GameData.h"
#include "../../Input/Keyboard.h"
#include "Player.h"

namespace
{
	// プレイヤーの移動速度
	constexpr float PLAYER_SPEED = 5.0f;

	// ジャンプ力
	constexpr float PLAYER_JUMP_POWER = 11.0f;
}

Player::Player(Vec2 spawn_pos)
	:m_move_by_gimmick(0.0f,0.0f), m_is_on_moving_pratform(false), m_collected_item(0)
{
	LoadDivGraph("Data/player.png", 42, 8, 6, 72, 72, m_handle_array);
	m_glow_small_handle = LoadGraph("Data/glow_small.png");
	m_glow_big_handle = LoadGraph("Data/glow_big.png");
	m_handle = m_handle_array[0];

	// 光描画用のスクリーン作成
	m_glow_screen = MakeScreen(72, 72, true);

	m_pos = spawn_pos;

	m_animation_state = Animation::Idle;
}

Player::~Player()
{
	for (int i = 0; i < sizeof(m_handle_array) / sizeof(m_handle_array[0]); i++)
	{
		DeleteGraph(m_handle_array[i]);
	}

	DeleteGraph(m_glow_small_handle);
	DeleteGraph(m_glow_big_handle);
	DeleteGraph(m_glow_screen);
}

void Player::Init()
{
	CharacterBase::Init();

	m_collision_width = 26.0f;
	m_collision_height = 48.0f;

	m_handle_offset.y = 12.0f;
}

void Player::Update()
{
	m_animation_timer++;

	// アニメーションによって異なるフレーム数で更新
	int animation_update_frame;

	switch (m_animation_state)
	{
	case Animation::Idle:
	{
		animation_update_frame = 15;
		if (m_animation_timer >= animation_update_frame)
		{
			UpdateAnimation();
			m_animation_timer = 0;
		}

		break;
	}
	case Animation::Walk:
	{
		animation_update_frame = 5;
		if (m_animation_timer >= animation_update_frame)
		{
			UpdateAnimation();
			m_animation_timer = 0;
		}

		break;
	}
	case Animation::Jamp:
	{
		UpdateAnimation();

		break;
	}
	case Animation::Dead:
	{
		UpdateAnimation();

		break;
	}
	}

	m_handle = m_handle_array[m_animation_frame];

	// プレイヤー死亡の場合以降の処理を行わない
	if (!m_is_alive)
	{
		m_move = Vec2(0.0f, 0.0f);
		m_animation_state = Animation::Dead;
		return;
	}

	m_animation_state = Animation::Idle;

	Move();
	Jump();

	CharacterBase::Update();
}

void Player::Draw(Vec2 camera_pos)
{
	// キャラクター画像の左上の座標
	float draw_x = m_pos.x - m_handle_width * 0.5f;
	// 画像の下端とコリジョンの下端を合わせる
	float draw_y = m_pos.y - m_handle_height * 0.5f - (m_handle_height - m_collision_height) * 0.5f;

	// キャラクター描画のスクリーン座標
	float screen_x = draw_x - camera_pos.x + Game::SCREEN_HALF_WIDTH;
	float screen_y = draw_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT;

	// キャラクターの向きによって画像を反転
	if (m_is_right)
	{
		if (m_is_alive)
		{
			if (m_collected_item >= GameData::STORY_ONE && m_collected_item < GameData::STORY_TWO && m_is_alive)
			{
				// 描画スクリーンを光用に変更
				SetDrawScreen(m_glow_screen);
				// 前フレームの内容を消す
				ClearDrawScreen();
				// 加算で光を描画
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawGraphF(0, 0, m_glow_small_handle, true);
			}
			else if (m_collected_item >= GameData::STORY_TWO && m_is_alive)
			{
				// 描画スクリーンを光用に変更
				SetDrawScreen(m_glow_screen);
				// 前フレームの内容を消す
				ClearDrawScreen();
				// 加算で光を描画
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawGraphF(0, 0, m_glow_big_handle, true);
			}

			// 描画スクリーンを通常に戻す
			SetDrawScreen(DX_SCREEN_BACK);
			// 光スクリーンの描画
			DrawGraphF(screen_x, screen_y, m_glow_screen, true);

		}

		// ブレンドモードを通常に戻しプレイヤーを描画
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraphF(screen_x, screen_y, m_handle, true);
	}
	else
	{
		if (m_is_alive)
		{
			if (m_collected_item >= GameData::STORY_ONE && m_collected_item < GameData::STORY_TWO && m_is_alive)
			{
				// 描画スクリーンを光用に変更
				SetDrawScreen(m_glow_screen);
				// 前フレームの内容を消す
				ClearDrawScreen();
				// 加算で光を描画
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawGraphF(0, 0, m_glow_small_handle, true);

			}
			else if (m_collected_item >= GameData::STORY_TWO && m_is_alive)
			{
				// 描画スクリーンを光用に変更
				SetDrawScreen(m_glow_screen);
				// 前フレームの内容を消す
				ClearDrawScreen();
				// 加算で光を描画
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawGraphF(0, 0, m_glow_big_handle, true);
			}

			// 描画スクリーンを通常に戻す
			SetDrawScreen(DX_SCREEN_BACK);
			// 光スクリーンの描画
			DrawGraphF(screen_x, screen_y, m_glow_screen, true);

		}
		
		// ブレンドモードを通常に戻しプレイヤーを描画
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawTurnGraphF(screen_x, screen_y, m_handle, true);
	}

#ifdef _DEBUG
	// デバック時のみコリジョンの矩形を描画
	//m_rect.Draw(camera_pos);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "PlayerPos : %f , %f", m_pos.x, m_pos.y);
	//DrawFormatString(1100, 0, GetColor(255, 255, 255), "集めたかけら : %d", m_collected_item);
	//DrawFormatString(0, 90, GetColor(255, 255, 255), "生きているか : %d", m_is_alive);

#endif
}

void Player::Move()
{
	// 移動量を計算
	if (Keyboard::IsPress(KEY_INPUT_LEFT))
	{
		m_animation_state = Animation::Walk;

		// プレイヤーの向きを変更
		m_is_right = false;

		m_move.x = -PLAYER_SPEED;
	}
	else if (Keyboard::IsPress(KEY_INPUT_RIGHT))
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

	// 動く床(横)に乗っている時move.xを加算
	if (m_is_on_moving_pratform)
	{
		m_move.x += m_move_by_gimmick.x;
	}
}

void Player::Jump()
{
	// 空中の場合以降の処理を行わない
	if (!m_is_ground)
	{
		m_animation_state = Animation::Jamp;
		return;
	}

	if (Keyboard::IsTrigger(KEY_INPUT_SPACE))
	{
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
	m_rect.CalculateEdges(m_pos.x, m_pos.y, m_collision_width, m_collision_height);
}

void Player::UpdateAnimation()
{
	switch (m_animation_state)
	{
	case Animation::Idle:
	{
		m_animation_frame++;

		if (m_animation_frame > 1)
		{
			m_animation_frame = 0;
		}

		break;
	}
	case Animation::Walk:
	{
		if (m_animation_frame < 8)
		{
			m_animation_frame = 8;
		}

		m_animation_frame++;

		if (m_animation_frame > 11)
		{
			m_animation_frame = 8;
		}

		break;
	}
	case Animation::Jamp:
	{
		m_animation_frame = 28;
		break;
	}
	case Animation::Dead:
	{
		m_animation_frame = 39;
	}
	}
}

void Player::MoveWithPratform(float move)
{
	m_move_by_gimmick.x = move;
	UpdateRect();
}

void Player::CountItem()
{
	m_collected_item++;
}

void Player::LoseItem()
{
	m_collected_item--;
}