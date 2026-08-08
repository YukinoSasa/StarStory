#pragma once
#include <memory>
#include "SceneBase.h"

class MenuTitle;

/// <summary>
/// シーンクラスを継承したタイトルシーンクラス
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();

	~SceneTitle() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

private:
	// タイトルメニューのポインタ
	std::shared_ptr<MenuTitle> m_p_menu_title = nullptr;
};