#pragma once
#include <memory>
#include "../Math/Rect.h"

class Player;
class Stage;

/// <summary>
/// 当たり判定を管理するクラス
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

	// プレイヤーとオブジェクトの衝突判定
	void CheckPlayerCollision(
		std::shared_ptr<Player> p_player,
		std::shared_ptr<Stage> p_stage,
		std::shared_ptr<GimmickManager> p_gimmick_manager);

private:
	// ギミックの横方向の衝突判定
	void CheckGimmickX(
		std::shared_ptr<Player> p_player, std::shared_ptr<GimmickBase> p_gimmick);

	// ギミックの縦方向の衝突判定
	void CheckGimmickY(
		std::shared_ptr<Player> p_player, std::shared_ptr<GimmickBase> p_gimmick);
};