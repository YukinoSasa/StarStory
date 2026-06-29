#pragma once
#include <memory>
#include "../Math/Vec2.h"

class Player;

/// <summary>
/// プレイヤーを映すカメラクラス
/// </summary>
class Camera
{
public:
	Camera();

	// 更新
	void Update();

	// カメラ座標のゲッタ
	Vec2 GetCameraPos() const { return m_pos; }

	// プレイヤーポインタのセッタ
	void SetPlayer(std::shared_ptr<Player> p_player) { m_p_player = p_player; }

private:
	// カメラ座標をプレイヤー座標に更新
	void UpdateCameraPos();

	// カメラ座標
	Vec2 m_pos;

	// プレイヤーポインタ
	std::shared_ptr<Player> m_p_player = nullptr;
};