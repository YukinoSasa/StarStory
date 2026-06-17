#pragma once

namespace Pad
{
	// 更新
	void Update();

	// 押されているか
	bool IsPress(int key);

	// 押した瞬間か
	bool IsTrigger(int key);

	// 離した瞬間か
	bool IsRelease(int key);

	// 前フレームのキー
}