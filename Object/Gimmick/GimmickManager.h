#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../../Math/Rect.h"
#include "../../Math/Vec2.h"

class GimmickBase;

// 1つあたりのギミック情報の構造体
struct GimmickData
{
	// ステージ番号
	int m_stage;
	// ギミックタイプ(1:箱)
	int m_gimmick_type;
	// スポーン座標
	Vec2 m_spawn;
	// サイズ
	float m_size;
	// 素材データ
	std::string m_file_pass;
};

// ギミックデータのvector配列
using GimmickDatas = std::vector<GimmickData>;

/// <summary>
/// ギミックを管理するクラス
/// </summary>
class GimmickManager
{
public:
	GimmickManager();

	~GimmickManager() = default;

	// 初期化
	void Init();

	// 更新
	void Update(Rect player_rect, Vec2 player_last_move);

	// 描画
	void Draw(Vec2 camera_pos);

	// ギミックのゲッタ
	std::vector<std::shared_ptr<GimmickBase>> GetGimmicks() { return m_p_gimmicks; }

private:
	// ギミックデータをまとめた配列
	GimmickDatas m_gimmick_datas;

	// ギミック自体をまとめた配列
	std::vector<std::shared_ptr<GimmickBase>> m_p_gimmicks;
};