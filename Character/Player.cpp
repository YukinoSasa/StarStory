#include <DxLib.h>
#include "Player.h"

Player::Player()
{
	m_Handle = LoadGraph("Data/pl_kari.png");
}

Player::~Player()
{
	DeleteGraph(m_Handle);
}

void Player::Init()
{

}

void Player::Update()
{

}

void Player::Draw()
{
	CharacterBase::Draw();
}