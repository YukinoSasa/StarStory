#pragma once
#include <memory>
#include "SceneBase.h"
#include "../csv/LoadCsv.h"

class Player;
class Enemy;
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

private:
	// プレイヤーのポインタ
	std::shared_ptr<Player> m_p_player = nullptr;

	// エネミーのポインタ
	std::shared_ptr<Enemy> m_p_enemy = nullptr;

	// 背景のポインタ
	std::shared_ptr<BackGround> m_p_background = nullptr;

	// ステージのポインタ
	std::shared_ptr<Stage> m_p_stage = nullptr;

	// カメラのポインタ
	std::shared_ptr<Camera> m_p_camera = nullptr;
};