#include <Dxlib.h>
#include <memory>
#include "GameConst.h"
#include "GameSetting.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneMain.h"
//#include "Sound/SoundManager.h"
#include "Input/Keyboard.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
#ifndef _DEBUG
	SetOutApplicationLogValidFlag(false);
#endif
	// 画面サイズの変更
	SetGraphMode(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, 32);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	
	//	デバッグ中はウィンドウモード、リリース版はフルスクリーン
#ifdef _DEBUG
	ChangeWindowMode(FALSE);
#else
	ChangeWindowMode(FALSE);
#endif

	if (DxLib_Init() == -1)
		return -1;

	// シーンマネージャーのポインタ
	std::unique_ptr<SceneManager> p_scene_manager = std::make_unique<SceneManager>();

	//// サウンドマネージャーのポインタ
	//std::unique_ptr<SoundManager> p_sound_manager = std::make_unique<SoundManager>();

	GameSetting game_setting;

	// シーン、サウンドの初期化
	p_scene_manager->Init();
	//p_sound_manager->Init(p_scene_manager->GetCurrentSceneState());

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面クリア
		ClearDrawScreen();

		// キーボードの入力を更新
		Keyboard::Update();

		p_scene_manager->Update(game_setting);
		//p_sound_manager->Update(game_setting, p_scene_manager->GetCurrentSceneState());

		p_scene_manager->Draw();

		// 表画面と裏画面の入れ替え
		ScreenFlip();

		// FPSを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}

#ifdef _DEBUG
		// 0キー、またはタイトルメニューの終了でゲーム終了
		if (CheckHitKey(KEY_INPUT_0) || p_scene_manager->GetIsGameEnd())
		{
			break;
		}
#else
		// タイトルメニューの終了でゲーム終了
		if (p_scene_manager->GetIsGameEnd())
		{
			break;
		}
#endif

	}

	DxLib_End();
	return 0;
}