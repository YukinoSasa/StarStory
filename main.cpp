#include <Dxlib.h>
#include "GameConst.h"
#include "Scene/SceneMain.h"
#include "Input/Pad.h"

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
	ChangeWindowMode(TRUE);
#else
	ChangeWindowMode(FALSE);
#endif
	

	if (DxLib_Init() == -1)
		return -1;

	// メインシーンのポインタ
	SceneMain* p_scene_main = new SceneMain;

	// メインシーンの初期化
	p_scene_main->Init();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面クリア
		ClearDrawScreen();

		// パッドの入力を更新
		Pad::Update();

		p_scene_main->Update();
		p_scene_main->Draw();

		// 表画面と裏画面の入れ替え
		ScreenFlip();

		// FPSを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}

		// Escapeキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	delete p_scene_main;

	DxLib_End();
	return 0;
}