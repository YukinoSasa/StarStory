#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "../Object/Character/EnemyManager.h"
#include "../Object/Gimmick/GimmickManager.h"
#include "../Object/Item/ItemManager.h"
#include "../Story/StoryManager.h"

// マップデータのvector配列
using MapData = std::vector<std::vector<int>>;

// csvファイルを読み込みマップデータを返す
MapData LoadMap(const std::string& file_path);

// コリジョンデータのvector配列
using CollisionData = std::vector<int>;

// csvファイルを読み込みマップチップのコリジョンデータを返す
CollisionData LoadCollision(const std::string& file_path);

// csvファイルを読み込みエネミーデータを返す
EnemyDatas LoadEnemy(const std::string& file_path);

// csvファイルを読み込みギミックデータを返す
GimmickDatas LoadGimmick(const std::string& file_path);

// csvファイルを読み込みアイテムデータを返す
ItemDatas LoadItem(const std::string& file_path);

// csvファイルを読み込みストーリーデータを返す
StoryDatas LoadStory(const std::string& file_path);