#include "ObjectBase.h"

ObjectBase::ObjectBase()
	:m_handle(-1), m_handle_width(-1.0f), m_handle_height(-1.0f), 
	m_collision_width(0.0f), m_collision_height(0.0f), m_handle_offset(0.0f, 0.0f),
	m_pos(20.0f, 0.0f), m_move(0.0f, 0.0f), m_rect()
{

}

ObjectBase::~ObjectBase()
{

}