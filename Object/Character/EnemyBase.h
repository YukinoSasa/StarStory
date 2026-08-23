#pragma once
#include "CharacterBase.h"
#include "EnemyManager.h"

/// <summary>
/// キャラクタークラスを継承したエネミー基底クラス
/// </summary>
class EnemyBase : public CharacterBase
{
public:
	EnemyBase(EnemyData enemy_data);

	virtual ~EnemyBase();

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update();

	// 描画
	virtual void Draw();

protected:
	//// 分割前の元の画像データ
	//int m_original_handle;
};