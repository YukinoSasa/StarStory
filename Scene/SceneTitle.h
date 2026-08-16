#pragma once
#include "Menu/Config.h"
#include "SceneBase.h"

class MenuTitle;
class SoundManager;

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
	void Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager) override;

	// 描画
	void Draw() override;

private:
	// タイトルメニューのポインタ
	std::shared_ptr<MenuTitle> m_p_menu_title = nullptr;

	// サウンドマネージャーのポインタ
	std::shared_ptr<SoundManager> m_p_sound_manager = nullptr;

	// 設定
	Config m_config;

	// フォントのハンドル
	int m_font_handle;

	// 背景のハンドル
	int m_bg_handle;
};