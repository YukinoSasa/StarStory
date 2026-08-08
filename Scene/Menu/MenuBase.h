#pragma once

/// <summary>
/// メニューの基底クラス
/// </summary>
class MenuBase
{
public:
	MenuBase();

	virtual ~MenuBase();

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update();

	// 描画
	virtual void Draw();
};