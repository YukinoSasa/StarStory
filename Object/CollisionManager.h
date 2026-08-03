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
	void CheckPlayerCollision(std::shared_ptr<Player> p_player);

private:
	// プレイヤーポインタ
	std::shared_ptr<Player> m_p_stage = nullptr;

	// ステージポインタ
	std::shared_ptr<Stage> m_p_stage = nullptr;
};