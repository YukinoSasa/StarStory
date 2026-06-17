#include <DxLib.h>
#include "Pad.h"

namespace
{
	// 前のフレームのパッド押し下げ状態
	int lastPad = 0;

	// 現在のフレームのパッド押し下げ状態
	int currentPad = 0;
}

namespace Pad
{
	void Update()
	{
		// 前フレームの入力状態をlastPadへ入れる
		lastPad = currentPad;

		// 現在の入力状態を取得する
		currentPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	bool IsPress(int key)
	{
		// 現在のフレームで押されている
		return (currentPad & key);
	}

	bool IsTrigger(int key)
	{
		bool isNow = (currentPad & key);	// 現在のフレーム
		bool isLast = (lastPad & key);		// 前のフレーム

		// 現在のフレームで押されていて、前回のフレームで押されていない場合true
		if (isNow && !isLast)
		{
			return true;
		}

		return false;
	}

	bool IsRelease(int key)
	{
		bool isNow = (currentPad & key);	// 現在のフレーム
		bool isLast = (lastPad & key);		// 前のフレーム

		// 現在のフレームで押されていなくて、前回のフレームで押されている場合true
		if (!isNow && isLast)
		{
			return true;
		}

		return false;
	}
}
