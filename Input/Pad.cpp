#include <DxLib.h>
#include "Pad.h"

namespace
{
	// 前のフレームのパッド押し下げ状態
	int last_pad = 0;

	// 現在のフレームのパッド押し下げ状態
	int current_pad = 0;
}

namespace Pad
{
	void Update()
	{
		// 前フレームの入力状態をlast_padへ入れる
		last_pad = current_pad;

		// 現在の入力状態を取得する
		current_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	bool IsPress(int key)
	{
		// 指定したキーが現在のフレームで押されている場合true
		return (current_pad & key);
	}

	bool IsTrigger(int key)
	{
		bool is_now = (current_pad & key);	// 現在のフレーム
		bool is_last = (last_pad & key);		// 前のフレーム

		// 現在のフレームで押されていて、前回のフレームで押されていない場合true
		if (is_now && !is_last)
		{
			return true;
		}

		return false;
	}

	bool IsRelease(int key)
	{
		bool is_now = (current_pad & key);	// 現在のフレーム
		bool is_last = (last_pad & key);		// 前のフレーム

		// 現在のフレームで押されていなくて、前回のフレームで押されている場合true
		if (!is_now && is_last)
		{
			return true;
		}

		return false;
	}
}
