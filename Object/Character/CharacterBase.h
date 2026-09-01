#pragma once
#include <memory>
#include "../ObjectBase.h"

class Stage;

/// <summary>
/// キャラクターの基底クラス
/// </summary>
class CharacterBase : public ObjectBase
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

	// 生きているかどうかのゲッタ
	bool GetIsAlive() const { return m_is_alive; }

	bool GetIsGround() const { return m_is_ground; }

	// ステージポインタのセッタ
	void SetStage(std::shared_ptr<Stage> stage) { m_p_stage = stage; }

	// 生きているかどうかのセッタ
	void SetIsAlive(bool is_alive) { m_is_alive = is_alive; }

	// 接地しているかどうかのセッタ
	void SetIsGround(bool is_ground) { m_is_ground = is_ground; }

protected:
	// キャラクターが右向きかどうか
	bool m_is_right;

	// 接地しているかどうか
	bool m_is_ground;

	// ステージポインタ
	std::shared_ptr<Stage> m_p_stage = nullptr;

	// 生きているかどうか
	bool m_is_alive;

	// 現在のフレームで表示するアニメーションのフレーム番号
	int m_animation_frame;

	// アニメーションタイマー
	int m_animation_timer;
};