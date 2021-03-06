﻿/***********************************************************************************
**
** GumpGeneric.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GumpGeneric.h"
#include "../Managers/ConfigManager.h"
#include "../Managers/FontsManager.h"
#include "../TextEngine/GameConsole.h"
#include "../Network/Packets.h"
//----------------------------------------------------------------------------------
CGumpGeneric::CGumpGeneric(uint serial, short x, short y, uint id)
: CGump(GT_GENERIC, serial, x, y)
{
	m_Page = 1;
	m_ID = id;
}
//----------------------------------------------------------------------------------
CGumpGeneric::~CGumpGeneric()
{
}
//----------------------------------------------------------------------------------
void CGumpGeneric::AddText(const int &index, const wstring &text, CBaseGUI *start, const bool &backbroundCanBeColored)
{
	WISPFUN_DEBUG("c96_f1");
	if (start == NULL)
		start = (CBaseGUI*)m_Items;

	QFOR(item, start, CBaseGUI*)
	{
		switch (item->Type)
		{
			case GOT_TEXT:
			{
				CGUIGenericText *gt = (CGUIGenericText*)item;

				if (gt->TextID == index)
					gt->CreateTexture(text);

				break;
			}
			case GOT_TEXTENTRY:
			{
				CGUIGenericTextEntry *gte = (CGUIGenericTextEntry*)item;

				if (gte->TextID == index)
					gte->m_Entry.SetText(text);

				break;
			}
			case GOT_HTMLTEXT:
			{
				CGUIHTMLText *gt = (CGUIHTMLText*)item;

				if (gt->TextID == index)
				{
					gt->Text = text;
					gt->CreateTexture(backbroundCanBeColored);
				}

				break;
			}
			case GOT_HTMLGUMP:
			{
				CGUIHTMLGump *ghtml = (CGUIHTMLGump*)item;

				if (ghtml->Serial == index + 1)
				{
					AddText(index, text, (CBaseGUI*)item->m_Items, !ghtml->HaveBackground);
					ghtml->CalculateDataSize();
				}

				break;
			}
			default:
				break;
		}
	}
}
//----------------------------------------------------------------------------------
void CGumpGeneric::SendGumpResponse(int index)
{
	WISPFUN_DEBUG("c96_f2");
	//Ответ на гамп
	CPacketGumpResponse(this, index).Send();

	//Удаляем использованный гамп
	m_RemoveMark = true;
}
//----------------------------------------------------------------------------------
void CGumpGeneric::GUMP_BUTTON_EVENT_C
{
	WISPFUN_DEBUG("c96_f3");
	SendGumpResponse(serial);
}
//----------------------------------------------------------------------------------
void CGumpGeneric::GUMP_DIRECT_HTML_LINK_EVENT_C
{
	WISPFUN_DEBUG("c96_f4");
	g_FontManager.GoToWebLink(link);
}
//----------------------------------------------------------------------------------
void CGumpGeneric::OnCharPress(const WPARAM &wParam, const LPARAM &lParam)
{
	WISPFUN_DEBUG("c96_f5");
	g_EntryPointer->Insert(wParam);
	m_WantRedraw = true;
}
//----------------------------------------------------------------------------------
void CGumpGeneric::OnKeyDown(const WPARAM &wParam, const LPARAM &lParam)
{
	WISPFUN_DEBUG("c96_f6");
	if (wParam == VK_RETURN)
	{
		if (g_ConfigManager.ConsoleNeedEnter)
			g_EntryPointer = NULL;
		else
			g_EntryPointer = &g_GameConsole;

		m_WantRedraw = true;
	}
	else
		g_EntryPointer->OnKey(this, wParam);
}
//----------------------------------------------------------------------------------
