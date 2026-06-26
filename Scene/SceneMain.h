#pragma once
#include <memory>
#include "SceneBase.h"
#include "../csv/LoadCsv.h"

class Player;
class BackGround;
class Stage;
class Camera;

/// <summary>
/// メインシーンクラス
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
	std::shared_ptr<Player> m_pPlayer = nullptr;

	// 背景のポインタ
	std::shared_ptr<BackGround> m_pBackGround = nullptr;

	// ステージのポインタ
	std::shared_ptr<Stage> m_pStage = nullptr;

	// カメラのポインタ
	std::shared_ptr<Camera> m_pCamera = nullptr;
};