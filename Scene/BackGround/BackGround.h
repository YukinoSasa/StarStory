#pragma once
#include "../../Math/Vec2.h"

/// <summary>
/// ”wŒi‰æ‘œ‚ğŠÇ—‚·‚éƒNƒ‰ƒX
/// </summary>
class BackGround
{
public:
	BackGround();

	~BackGround();

	// ‰Šú‰»
	void Init();

	// •`‰æ
	void Draw(Vec2 camera_pos);

private:
	// ‰æ‘œ‚ğ“Ç‚İ‚Ş•Ï”
	// ’nã”wŒi
	int m_handle_ground;
	// ‹ó”wŒi1
	int m_handle_sky1;

	// •`‰æ‚·‚éˆÊ’u
	Vec2 m_pos;

	// ‰æ‘œ‚Ì•
	int m_handle_width;
	// ‰æ‘œ‚Ì‚‚³
	int m_handle_height;
};