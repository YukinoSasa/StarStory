#pragma once
#include "CharacterBase.h"

/// <summary>
/// キャラクタークラスを継承したプレイヤークラス
/// </summary>
class Player final : public CharacterBase
{
public:
	Player(Vec2 spawn_pos);

	~Player() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw(Vec2 camera_pos) override;

	// プレイヤー座標のゲッタ
	Vec2 GetPlayerPos() const { return m_pos; }

	// プレイヤー幅のゲッタ
	float GetPlayerWidth() const { return m_handle_width; }

	// プレイヤー高さのゲッタ
	float GetPlayerHeight() const { return m_handle_height; }

	// コリジョン幅のゲッタ
	float GetCollisionWidth() const { return m_collision_width; }

	// コリジョン高さのゲッタ
	float GetCollisionHeight() const { return m_collision_height; }

	// プレイヤーの移動量のゲッタ
	Vec2 GetPlayerMove() const { return m_move; }

	// 動く床(横)に乗っているかどうかのゲッタ
	bool GetIsOnMovingPratform() const { return m_is_on_moving_pratform; }

	// 集めたアイテムのゲッタ
	int GetPlayerCollectItem() const { return m_collected_item; }

	// プレイヤー座標のセッタ
	void SetPlayerPosX(float pos_x) { m_pos.x = pos_x; }
	void SetPlayerPosY(float pos_y) { m_pos.y = pos_y; }

	// プレイヤーの移動量のセッタ
	void SetPlayerMoveX(float move_x) { m_move.x = move_x; }
	void SetPlayerMoveY(float move_y) { m_move.y = move_y; }

	// 動く床(横)に乗っているかどうかのセッタ
	void SetIsOnMovingPratform(bool is_on_moveing_pratform) {
		m_is_on_moving_pratform = is_on_moveing_pratform; }

	// 横移動処理
	void MovePlayerX();
	// 上下移動処理
	void MovePlayerY();

	// コリジョンの更新
	void UpdateRect();

	// 床と一緒に移動する
	void MoveWithPratform(float move);

	// アイテム取得時にカウント
	void CountItem();

private:
	// 左右の移動量を計算
	void Move();

	// ジャンプ
	void Jump();

	// 画像データの配列
	int m_handle_array[42];
	// 光の画像ハンドル
	int m_glow_small_handle;
	int m_glow_big_handle;

	// 光の画像の描画先
	int m_glow_screen;

	// ギミックによって動いた移動量
	Vec2 m_move_by_gimmick;

	// 動く床(横)に乗っているかどうか
	bool m_is_on_moving_pratform;

	// 集めたアイテムの数
	int m_collected_item;

	// アニメーションの状態
	enum class Animation
	{
		Idle,
		Walk,
		Jamp,
		Fall,
		Dead,
	};

	// アニメーションの状態を保存する変数
	Animation m_animation_state;

	// アニメーション画像の更新
	void UpdateAnimation();
};