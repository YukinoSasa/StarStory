#pragma once
#include <memory>
#include <vector>
#include "SceneBase.h"
#include "../csv/LoadCsv.h"
#include "../Math/Rect.h"

class Player;
class EnemyManager;
//class Enemy;
class BackGround;
class Stage;
class Camera;

/// <summary>
/// シーンクラスを継承したメインシーンクラス
/// </summary>
class SceneMain : public SceneBase
{
public:
	SceneMain();

	~SceneMain() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// ゴールしたかどうかのゲッタ
	bool GetIsGoal() const { return m_is_goal; }

private:
	// プレイヤーと敵の衝突をチェック
	void HitPlayerEnemy(const Rect& player_rect, const Rect& enemy_rect);

	// プレイヤーのポインタ
	std::shared_ptr<Player> m_p_player = nullptr;

	// エネミーマネージャーのポインタ
	std::shared_ptr<EnemyManager> m_p_enemy_manager = nullptr;

	//std::vector<std::shared_ptr<Piece>> m_p_pieces;

	// 背景のポインタ
	std::shared_ptr<BackGround> m_p_background = nullptr;

	// ステージのポインタ
	std::shared_ptr<Stage> m_p_stage = nullptr;

	// カメラのポインタ
	std::shared_ptr<Camera> m_p_camera = nullptr;

	// ゴールしたかどうか
	bool m_is_goal;
};