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
	int m_Handle;

	// •`‰æ‚·‚éˆÊ’u
	Vec2 m_Pos;
};