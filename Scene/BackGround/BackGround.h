#pragma once
#include "../../Math/Vec2.h"

class BackGround
{
public:
	BackGround();

	~BackGround();

	// ‰Šú‰»
	void Init();

	// XV
	void Update();

	// •`‰æ
	void Draw(Vec2 cameraPos);

private:
	// ‰æ‘œ‚ğ“Ç‚İ‚Ş•Ï”
	// ’nã”wŒi
	int m_HandleGround;
	// ‹ó”wŒi1
	int m_HandleSky1;

	// •`‰æ‚·‚éˆÊ’u
	Vec2 m_Pos;

	// ‰æ‘œ‚Ì•
	int m_HandleWidth;
	// ‰æ‘œ‚Ì‚‚³
	int m_HandleHeight;
};