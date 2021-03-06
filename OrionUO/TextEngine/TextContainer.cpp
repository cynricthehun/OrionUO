﻿/***********************************************************************************
**
** TextContainer.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "TextContainer.h"
//----------------------------------------------------------------------------------
CTextContainer g_SystemChat(30);
//----------------------------------------------------------------------------------
CTextContainer::CTextContainer(const int &maxSize)
: m_MaxSize(maxSize), m_Size(0)
{
}
//----------------------------------------------------------------------------------
CTextContainer::~CTextContainer()
{
}
//----------------------------------------------------------------------------------
void CTextContainer::Clear()
{
	WISPFUN_DEBUG("c173_f1");
	CBaseQueue::Clear();

	m_Size = 0;
}
//----------------------------------------------------------------------------------
void CTextContainer::Add(CTextData *obj)
{
	WISPFUN_DEBUG("c173_f2");
	CBaseQueue::Add(obj);

	if (m_Size >= m_MaxSize)
		CBaseQueue::Delete(m_Items);
	else
		m_Size++;
}
//----------------------------------------------------------------------------------
void CTextContainer::Delete(CTextData *obj)
{
	WISPFUN_DEBUG("c173_f3");
	CBaseQueue::Delete(obj);

	m_Size--;
}
//----------------------------------------------------------------------------------
void CTextContainer::DrawSystemChat(const int &x, const int &y, const int &height)
{
	WISPFUN_DEBUG("c173_f4");
	int offset = (y + height) - 41;

	CTextData *td = (CTextData*)g_SystemChat.Last();

	while (td != NULL && offset >= y)
	{
		CGLTextTexture &tth = td->m_Texture;

		offset -= tth.Height;

		if (td->Timer >= g_Ticks)
			tth.Draw(x, offset);

		td = (CTextData*)td->m_Prev;
	}
}
//----------------------------------------------------------------------------------
