#pragma once
#include <memory>
#include "../Math/Vec2.h"
#include "../Math/Rect.h"

class Stage;

/// <summary>
/// キャラクターの基底クラス
/// </summary>
class CharacterBase
{
public:
	CharacterBase();

	virtual ~CharacterBase();

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update();

	// 描画
	virtual void Draw(Vec2 camera_pos);

	// Rectクラスのゲッタ
	const Rect GetRect() const { return m_rect; }

	// 生きているかどうかのゲッタ
	bool GetIsAlive() const { return m_is_alive; }

	// ステージポインタのセッタ
	void SetStage(std::shared_ptr<Stage> stage) { m_p_stage = stage; }

	// 生きているかどうかのセッタ
	void SetIsAlive(bool is_alive) { m_is_alive = is_alive; }

protected:
	// ステージとの当たり判定
	void CheckHitStage(Rect& chip_rect);

private:
	//// 重力を受ける
	//void Gravity();

protected:
	// 画像を読み込む変数
	int m_handle;

	// 画像の幅を保存する変数
	float m_handle_width;

	// 画像の高さを保存する変数
	float m_handle_height;

	// キャラクターが右向きかどうか
	bool m_is_right;

	// キャラクターの中心座標
	Vec2 m_pos;
	// キャラクターの移動量
	Vec2 m_move;
	// キャラクターの移動量を保存しておく変数
	Vec2 m_last_move;

	// 接地しているかどうか
	bool m_is_ground;

	// 当たり判定用矩形
	Rect m_rect;

	// ステージポインタ
	std::shared_ptr<Stage> m_p_stage = nullptr;

	// 生きているかどうか
	bool m_is_alive;
};