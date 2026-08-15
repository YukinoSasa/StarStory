#pragma once
#include <memory>
#include <vector>
#include "SceneBase.h"
#include "../csv/LoadCsv.h"
#include "../Math/Rect.h"
#include "Menu/Config.h"

class Player;
class EnemyManager;
//class Enemy;
class BackGround;
class Stage;
class Camera;
class GimmickManager;
class ItemManager;
class CollisionManager;
class MenuPause;

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
	void Update(GameSetting& game_setting) override;

	// 描画
	void Draw() override;

	// ゴールしたかどうかのゲッタ
	bool GetIsGoal() const { return m_is_goal; }

private:
	// プレイヤーと敵の衝突をチェック
	void HitPlayerEnemy(const Rect& player_rect, const Rect& enemy_rect);

	// プレイヤーとアイテムの衝突をチェック
	void HitPlayerItem(const Rect& player_rect, const Rect& item_rect, std::shared_ptr<Piece> item);

	// プレイヤーのポインタ
	std::shared_ptr<Player> m_p_player = nullptr;

	// エネミーマネージャーのポインタ
	std::shared_ptr<EnemyManager> m_p_enemy_manager = nullptr;

	//std::vector<std::shared_ptr<Piece>> m_p_pieces;

	// 背景のポインタ
	std::shared_ptr<BackGround> m_p_background = nullptr;

	// コリジョンマネージャーのポインタ
	std::shared_ptr<CollisionManager> m_p_collision_manager = nullptr;

	// ステージのポインタ
	std::shared_ptr<Stage> m_p_stage = nullptr;

	// カメラのポインタ
	std::shared_ptr<Camera> m_p_camera = nullptr;

	// ギミックマネージャーのポインタ
	std::shared_ptr<GimmickManager> m_p_gimmick_manager = nullptr;

	// アイテムマネージャーのポインタ
	std::shared_ptr<ItemManager> m_p_item_manager = nullptr;

	// ポーズメニューのポインタ
	std::shared_ptr<MenuPause> m_p_menu_pause = nullptr;

	// 設定
	Config m_config;

	// ポーズ中かどうか
	bool m_is_pause;

	// ゴールしたかどうか
	bool m_is_goal;
};