#include <DxLib.h>
#include "Keyboard.h"

namespace
{
	// 前のフレームのキー押し下げ状態
	bool last_key[256] = {};

	// 現在のフレームのキー押し下げ状態
	bool current_key[256] = {};
}

/// <summary>
/// キーボード入力を扱う名前空間
/// </summary>
namespace Keyboard
{
	void Update()
	{
		for (int key = 0; key < sizeof(current_key) / sizeof(current_key[0]); key++)
		{
			// 前フレームの入力状態をlast_keyへ入れる
			last_key[key] = current_key[key];

			// 現在の入力状態を取得する
			current_key[key] = CheckHitKey(key);
		}
	}

	bool IsPress(int key)
	{
		// 指定したキーが現在のフレームで押されている場合true
		return current_key[key];
	}

	bool IsTrigger(int key)
	{
		bool is_now = (current_key[key]);	// 現在のフレーム
		bool is_last = (last_key[key]);		// 前のフレーム

		// 現在のフレームで押されていて、前回のフレームで押されていない場合true
		if (is_now && !is_last)
		{
			return true;
		}

		return false;
	}

	bool IsRelease(int key)
	{
		bool is_now = (current_key[key]);	// 現在のフレーム
		bool is_last = (last_key[key]);		// 前のフレーム

		// 現在のフレームで押されていなくて、前回のフレームで押されている場合true
		if (!is_now && is_last)
		{
			return true;
		}

		return false;
	}
}