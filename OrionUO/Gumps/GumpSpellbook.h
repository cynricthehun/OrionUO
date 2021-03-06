﻿/***********************************************************************************
**
** GumpSpellbook.h
**
** Copyright (C) September 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUMPSPELLBOOK_H
#define GUMPSPELLBOOK_H
//----------------------------------------------------------------------------------
#include "Gump.h"
//----------------------------------------------------------------------------------
struct SPELL_REQURIES
{
	uchar ManaCost;
	uchar MinSkill;
};
//----------------------------------------------------------------------------------
struct PALADIN_SPELL_REQURIES
{
	uchar ManaCost;
	uchar MinSkill;
	uchar TithingPoints;
};
//----------------------------------------------------------------------------------
class CGumpSpellbook : public CGump
{
	SETGET(SPELLBOOK_TYPE, BookType);

public:
	static const int SPELLBOOK_1_SPELLS_COUNT = 64;
	static const int SPELLBOOK_2_SPELLS_COUNT = 17;
	static const int SPELLBOOK_3_SPELLS_COUNT = 10;
	static const int SPELLBOOK_4_SPELLS_COUNT = 6;
	static const int SPELLBOOK_5_SPELLS_COUNT = 8;
	static const int SPELLBOOK_6_SPELLS_COUNT = 16;
	static const int SPELLBOOK_7_SPELLS_COUNT = 30;

	static const string m_SpellName1[SPELLBOOK_1_SPELLS_COUNT][2];
	static const string m_SpellName2[SPELLBOOK_2_SPELLS_COUNT][2];
	static const string m_SpellName3[SPELLBOOK_3_SPELLS_COUNT][2];
	static const string m_SpellName4[SPELLBOOK_4_SPELLS_COUNT];
	static const string m_SpellName5[SPELLBOOK_5_SPELLS_COUNT];
	static const string m_SpellName6[SPELLBOOK_6_SPELLS_COUNT][2];
	static const string m_SpellName7[SPELLBOOK_7_SPELLS_COUNT][2];

private:
	static const int ID_GSB_BUTTON_PREV = 1;
	static const int ID_GSB_BUTTON_NEXT = 2;
	static const int ID_GSB_BUTTON_CIRCLE_1_2 = 3;
	static const int ID_GSB_BUTTON_CIRCLE_3_4 = 4;
	static const int ID_GSB_BUTTON_CIRCLE_5_6 = 5;
	static const int ID_GSB_BUTTON_CIRCLE_7_8 = 6;
	static const int ID_GSB_BUTTON_MINIMIZE = 7;
	static const int ID_GSB_LOCK_MOVING = 8;
	static const int ID_GSB_SPELL_ICON_LEFT = 100;
	static const int ID_GSB_SPELL_ICON_RIGHT = 1000;

	static const int MAX_SPELLS_COUNT = 64;

	static const string m_SpellCircleName[8];

	static const string m_SpellReagents1[SPELLBOOK_1_SPELLS_COUNT];
	static const string m_SpellReagents2[SPELLBOOK_2_SPELLS_COUNT];

	static const SPELL_REQURIES m_SpellRequries2[SPELLBOOK_2_SPELLS_COUNT];
	static const PALADIN_SPELL_REQURIES m_SpellRequries3[SPELLBOOK_3_SPELLS_COUNT];
	static const SPELL_REQURIES m_SpellRequries4[SPELLBOOK_4_SPELLS_COUNT];
	static const SPELL_REQURIES m_SpellRequries5[SPELLBOOK_5_SPELLS_COUNT];
	static const SPELL_REQURIES m_SpellRequries6[SPELLBOOK_6_SPELLS_COUNT];
	//static const SPELL_REQURIES m_SpellRequries7[SPELLBOOK_7_SPELLS_COUNT];

	int m_SpellCount;
	uchar m_Spells[MAX_SPELLS_COUNT];
	int m_PageCount;

	CGUIGumppic *m_Body;
	CGUIText *m_TithingPointsText;

	CGUIButton *m_PrevPage;
	CGUIButton *m_NextPage;

	CGUIGumppic *m_LastSpellPointer;
	CGUIGumppic *m_LastSpellBookmark;

	void GetTooltipBookInfo(int &dictionaryPagesCount, int &tooltipOffset);

	void GetSummaryBookInfo(int &maxSpellsCount, int &dictionaryPagesCount, int &spellsOnPage, int &spellIndexOffset, ushort &graphic, ushort &minimizedGraphic, ushort &iconStartGraphic);

	string GetSpellName(const int &offset, string &abbreviature, string &reagents);

	string GetSpellRequries(const int &offset, int &y);

public:
	CGumpSpellbook(uint serial, int x, int y);
	virtual ~CGumpSpellbook();

	void UpdateGraphic(const ushort &parentGraphic);

	virtual void DelayedClick(CRenderObject *obj);

	void ChangePage(int newPage);

	virtual void InitToolTip();

	virtual void PrepareContent();

	virtual void UpdateContent();

	GUMP_BUTTON_EVENT_H;
	GUMP_TEXT_ENTRY_EVENT_H;

	virtual bool OnLeftMouseButtonDoubleClick();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
