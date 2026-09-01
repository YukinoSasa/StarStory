#pragma once
#include <memory>
#include "../Math/Rect.h"
#include "../GameData.h"

class Player;
class Stage;
class Box;

/// <summary>
/// コリジョンを管理するクラス
/// </summary>
class CollisionManager
{
public:
	CollisionManager();

	~CollisionManager() = default;

	// 初期化
	void Init();

	// 更新
	void Update();

	// プレイヤーとオブジェクトの横方向衝突判定
	void CheckPlayerCollisionX(
		std::shared_ptr<Player> p_player,
		std::shared_ptr<Stage> p_stage,
		std::shared_ptr<GimmickManager> p_gimmick_manager,
		GameData& game_data);

	// プレイヤーとオブジェクトの縦方向衝突判定
	void CheckPlayerCollisionY(
		std::shared_ptr<Player> p_player,
		std::shared_ptr<Stage> p_stage,
		std::shared_ptr<GimmickManager> p_gimmick_manager,
		GameData& game_data);

	// 箱とステージの縦方向衝突判定
	void CheckBoxCollisionY(
		std::shared_ptr<GimmickManager> p_gimmick_manager,
		std::shared_ptr<Stage> p_stage);

private:
	// ギミックの横方向の衝突判定
	void CheckGimmickX(
		std::shared_ptr<Player> p_player, std::shared_ptr<GimmickBase> p_gimmick, GameData& game_data);

	// ギミックの縦方向の衝突判定
	void CheckGimmickY(
		std::shared_ptr<Player> p_player, std::shared_ptr<GimmickBase> p_gimmick, GameData& game_data);
};