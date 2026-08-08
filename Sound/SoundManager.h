#pragma once

/// <summary>
/// サウンドを管理するクラス
/// </summary>
class SoundManager
{
public:
	SoundManager();

	~SoundManager();

	// 初期化
	void Init();

	// 更新
	void Update();

private:
	// bgmのハンドル
	int m_title_bgm_handle;
};