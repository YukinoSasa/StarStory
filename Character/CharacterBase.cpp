#include <DxLib.h>
#include "CharacterBase.h"

CharacterBase::CharacterBase() :
	m_Handle(-1)
{
	
}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Init()
{

}

void CharacterBase::Update()
{

}

void CharacterBase::Draw()
{
	DrawGraph(500, 500, m_Handle, true);
}
