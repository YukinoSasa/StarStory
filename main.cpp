#include <Dxlib.h>
#include "Scene/SceneMain.h"
#include "Input/Pad.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
#ifndef _DEBUG
	SetOutApplicationLogValidFlag(false);
#endif
	// 画面サイズの変更
	SetGraphMode(1920, 1080, 32);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	
	// ウィンドウモードの変更
	ChangeWindowMode(TRUE);
	

	if (DxLib_Init() == -1)
		return -1;

	// メインシーンのポインタ
	SceneMain* pSceneMain = new SceneMain;

	// メインシーンの初期化
	pSceneMain->Init();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面クリア
		ClearDrawScreen();

		// パッドの入力を更新
		Pad::Update();

		pSceneMain->Update();
		pSceneMain->Draw();

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

	delete pSceneMain;

	DxLib_End();
	return 0;
}