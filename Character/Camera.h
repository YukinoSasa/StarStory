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

	~Camera();

	// 初期化
	void Init();

	// 更新
	void Update();

	// プレイヤーのポインタをセット
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	// カメラ座標を取得
	Vec2 GetCameraPos() const { return m_Pos; }

private:
	// カメラ座標をプレイヤー座標に更新
	void UpdateCameraPos();

	// プレイヤーのポインタ
	std::shared_ptr<Player> m_pPlayer = nullptr;

	// カメラの位置
	Vec2 m_Pos;
};