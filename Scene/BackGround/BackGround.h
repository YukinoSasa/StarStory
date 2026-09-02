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
	void Draw(Vec2 camera_pos, float stage_height);

private:
	// ƒJƒƒ‰‚ÌÀ•W‚ğ‚à‚Æ‚É•`‰æ‚Ìfor•¶‚Ìi‚Ì’l‚ğŒvZ‚·‚é
	int CalculateBackgroundIndex(float camera_pos_y);

	//// ’nã”wŒi
	//int m_handle_ground;
	// ”wŒi‰æ‘œ‚Ìƒnƒ“ƒhƒ‹
	int m_bg_handle;

	// •`‰æ‚·‚éÀ•W
	Vec2 m_pos;

	// ‰æ‘œ‚Ì•
	float m_handle_width;
	// ‰æ‘œ‚Ì‚‚³
	float m_handle_height;
};