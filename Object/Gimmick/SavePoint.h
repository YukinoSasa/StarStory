#pragma once
#include "GimmickBase.h"

/// <summary>
/// ギミックベースクラスを継承したセーブポイントクラス
/// </summary>
class SavePoint final : public GimmickBase
{
public:
	SavePoint(GimmickData gimmick_data);

	~SavePoint();

	// 初期化
	void Init() override;
};