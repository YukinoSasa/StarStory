#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../../Math/Vec2.h"

class Piece;

// アイテム1個の情報の構造体
struct ItemData
{
	// ステージ番号
	int m_stage;
	// スポーン座標
	Vec2 m_spawn;
	// サイズ
	float m_size;
	// 素材データ
	std::string m_file_pass;
};

// アイテムデータのvector配列
using ItemDatas = std::vector<ItemData>;

/// <summary>
/// アイテムを管理するクラス
/// </summary>
class ItemManager
{
public:
	ItemManager(int current_stage_num);

	~ItemManager() = default;

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw(Vec2 camera_pos);

	// アイテム配列のゲッタ
	std::vector<std::shared_ptr<Piece>> GetItems() const { return m_p_items; }

	// 自身が取得されたときに呼ばれる
	void Collect();

private:
	// アイテムデータをまとめた配列
	ItemDatas m_item_datas;

	// アイテム自体をまとめた配列
	std::vector<std::shared_ptr<Piece>> m_p_items;
};