#pragma once

/// <summary>
/// オブジェクトの基底クラス
/// </summary>
class ObjectBase
{
	ObjectBase();

	virtual ~ObjectBase();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();
};