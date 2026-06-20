#include <DxLib.h>
#include "Stage.h"

namespace
{
	// 地面ブロックの画像サイズ
	float K_SIZE = 64.0f;
}

Stage::Stage()
{
	m_MapData = LoadMap("csv/Stage1.csv");
	m_Handle1 = LoadGraph("Data/ground_kari.png");
}

Stage::~Stage()
{

}

void Stage::Init()
{

}

void Stage::Update()
{

}

void Stage::Draw()
{
	for (int y = 0; y < (int)m_MapData.size(); y++)
	{
		for (int x = 0; x < (int)m_MapData[y].size(); x++)
		{
			int Tile = m_MapData[y][x];

			switch (Tile)
			{
			case 0:
				break;

			case 1:
				DrawGraph(x * K_SIZE, y * K_SIZE + 100, m_Handle1, true);
			}
		}
	}
}
