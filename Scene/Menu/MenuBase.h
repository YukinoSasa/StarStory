#pragma once
#include <memory>

class SoundManager;

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
	virtual void Update(std::shared_ptr<SoundManager> p_sound_manager);

	// 描画
	virtual void Draw();
};