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
class GimmickManager;
class ItemManager;

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

	// プレイヤーとギミックの衝突をチェック
	void HitPlayerGimmick(const Rect& player_rect, const Rect& gimmick_rect);

	// プレイヤーとアイテムの衝突をチェック
	void HitPlayerItem(const Rect& player_rect, const Rect& item_rect, std::shared_ptr<Piece> item);

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

	// ギミックマネージャーのポインタ
	std::shared_ptr<GimmickManager> m_p_gimmick_manager = nullptr;

	// アイテムマネージャーのポインタ
	std::shared_ptr<ItemManager> m_p_item_manager = nullptr;

	// ゴールしたかどうか
	bool m_is_goal;
};