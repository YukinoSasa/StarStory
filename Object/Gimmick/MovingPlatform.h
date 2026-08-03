#pragma once
#include "GimmickBase.h"

/// <summary>
/// ギミックベースクラスを継承した動く床クラス
/// </summary>
class MovingPlatform : public GimmickBase
{
public:
	MovingPlatform(GimmickData gimmick_data);

	~MovingPlatform();

	// 初期化
	void Init() override;

	// 更新
	void Update();
};