#include "gbafe.h"

struct SSTextDispInfo const sPage0TextInfo[] =
{
    { gStatScreen.text + STATSCREEN_TEXT_SKLLABEL,   gUiTmScratchA + TILEMAP_INDEX(1, 3),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Skl },
    { gStatScreen.text + STATSCREEN_TEXT_SPDLABEL,   gUiTmScratchA + TILEMAP_INDEX(1, 5),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Spd },
    { gStatScreen.text + STATSCREEN_TEXT_LCKLABEL,   gUiTmScratchA + TILEMAP_INDEX(1, 7),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Lck },
    { gStatScreen.text + STATSCREEN_TEXT_DEFLABEL,   gUiTmScratchA + TILEMAP_INDEX(9, 1),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Def },
    { gStatScreen.text + STATSCREEN_TEXT_RESLABEL,   gUiTmScratchA + TILEMAP_INDEX(9, 3), TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Res },
    { gStatScreen.text + STATSCREEN_TEXT_MOVLABEL,   gUiTmScratchA + TILEMAP_INDEX(9, 5),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Mov },
    { gStatScreen.text + STATSCREEN_TEXT_CONLABEL,   gUiTmScratchA + TILEMAP_INDEX(9, 7),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Con },
    { gStatScreen.text + STATSCREEN_TEXT_AIDLABEL,   gUiTmScratchA + TILEMAP_INDEX(17, 1),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Aid },
    { gStatScreen.text + STATSCREEN_TEXT_RESCUENAME, gUiTmScratchA + TILEMAP_INDEX(17, 3),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Trv },
    { gStatScreen.text + STATSCREEN_TEXT_AFFINLABEL, gUiTmScratchA + TILEMAP_INDEX(17, 5),  TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Affin },
    { gStatScreen.text + STATSCREEN_TEXT_STATUS,     gUiTmScratchA + TILEMAP_INDEX(17, 7), TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Cnd },

    { }, // end
};

struct SSTextDispInfo const sPage1TextInfo[] =
{
    { gStatScreen.text + STATSCREEN_TEXT_BSATKLABEL, gUiTmScratchA + TILEMAP_INDEX(17, 2), TEXT_COLOR_SYSTEM_GOLD, 6, &gMid_Atk },
    { gStatScreen.text + STATSCREEN_TEXT_BSHITLABEL, gUiTmScratchA + TILEMAP_INDEX(17, 4), TEXT_COLOR_SYSTEM_GOLD, 6, &gMid_Hit },
    { gStatScreen.text + STATSCREEN_TEXT_BSRANGE,    gUiTmScratchA + TILEMAP_INDEX(17, 6), TEXT_COLOR_SYSTEM_GOLD, 6, &gMid_Rng },
    { gStatScreen.text + STATSCREEN_TEXT_BSCRTLABEL, gUiTmScratchA + TILEMAP_INDEX(23, 2), TEXT_COLOR_SYSTEM_GOLD, 6, &gMid_Crt },
    { gStatScreen.text + STATSCREEN_TEXT_BSAVOLABEL, gUiTmScratchA + TILEMAP_INDEX(23, 4), TEXT_COLOR_SYSTEM_GOLD, 6, &gMid_Avo },

    { }, // end
};

void DisplayPage0(void)
{
    DisplayTexts(sPage0TextInfo);

    // Displaying str/mag label
    if (UnitHasMagicRank(gStatScreen.unit))
    {
        // mag
        PutDrawText(
            &gStatScreen.text[STATSCREEN_TEXT_POWLABEL],
            gUiTmScratchA + TILEMAP_INDEX(1, 1),
            TEXT_COLOR_SYSTEM_GOLD, 0, 0,
            GetStringFromIndex(0x4FF)); // Mag
    }
    else
    {
        // str
        PutDrawText(
            &gStatScreen.text[STATSCREEN_TEXT_POWLABEL],
            gUiTmScratchA + TILEMAP_INDEX(1, 1),
            TEXT_COLOR_SYSTEM_GOLD, 0, 0,
            GetStringFromIndex(0x4FE)); // Str
    }

    // displaying str/mag stat value
    DrawStatWithBar(0, 5, 1,
        gStatScreen.unit->pow,
        GetUnitPower(gStatScreen.unit),
        UNIT_POW_MAX(gStatScreen.unit));

    // displaying skl stat value
    DrawStatWithBar(1, 5, 3,
        gStatScreen.unit->state & US_RESCUING
            ? gStatScreen.unit->skl/2
            : gStatScreen.unit->skl,
        GetUnitSkill(gStatScreen.unit),
        gStatScreen.unit->state & US_RESCUING
            ? UNIT_SKL_MAX(gStatScreen.unit)/2
            : UNIT_SKL_MAX(gStatScreen.unit));

    // displaying spd stat value
    DrawStatWithBar(2, 5, 5,
        gStatScreen.unit->state & US_RESCUING
            ? gStatScreen.unit->spd/2
            : gStatScreen.unit->spd,
        GetUnitSpeed(gStatScreen.unit),
        gStatScreen.unit->state & US_RESCUING
            ? UNIT_SPD_MAX(gStatScreen.unit)/2
            : UNIT_SPD_MAX(gStatScreen.unit));

    // displaying lck stat value
    DrawStatWithBar(3, 5, 7,
        gStatScreen.unit->lck,
        GetUnitLuck(gStatScreen.unit),
        UNIT_LCK_MAX(gStatScreen.unit));

    // displaying def stat value
    DrawStatWithBar(4, 13, 1,
        gStatScreen.unit->def,
        GetUnitDefense(gStatScreen.unit),
        UNIT_DEF_MAX(gStatScreen.unit));

    // displaying res stat value
    DrawStatWithBar(5, 13, 3,
        gStatScreen.unit->res,
        GetUnitResistance(gStatScreen.unit),
        UNIT_RES_MAX(gStatScreen.unit));

    // displaying mov stat value
    DrawStatWithBar(6, 13, 5,
        UNIT_MOV_BASE(gStatScreen.unit),
        UNIT_MOV(gStatScreen.unit),
        UNIT_MOV_MAX(gStatScreen.unit));

    // displaying con stat value
    DrawStatWithBar(7, 13, 7,
        UNIT_CON_BASE(gStatScreen.unit),
        UNIT_CON(gStatScreen.unit),
        UNIT_CON_MAX(gStatScreen.unit));

    // displaying unit aid
    PutNumberOrBlank(gUiTmScratchA + TILEMAP_INDEX(21, 1), TEXT_COLOR_SYSTEM_BLUE,
        GetUnitAid(gStatScreen.unit));

    // displaying unit aid icon
    DrawIcon(gUiTmScratchA + TILEMAP_INDEX(23, 1),
        GetUnitAidIconId(UNIT_CATTRIBUTES(gStatScreen.unit)),
        TILEREF(0, STATSCREEN_BGPAL_EXTICONS));

    // displaying unit rescue name
    Text_InsertDrawString(
        &gStatScreen.text[STATSCREEN_TEXT_RESCUENAME],
        24, TEXT_COLOR_SYSTEM_BLUE,
        GetUnitRescueName(gStatScreen.unit));

    // displaying unit status name and turns

    if (gStatScreen.unit->statusIndex != UNIT_STATUS_RECOVER)
    {
        // display name

        if (gStatScreen.unit->statusIndex == UNIT_STATUS_NONE)
        {
            Text_InsertDrawString(
                &gStatScreen.text[STATSCREEN_TEXT_STATUS],
                24, TEXT_COLOR_SYSTEM_BLUE,
                GetUnitStatusName(gStatScreen.unit));
        }
        else
        {
            Text_InsertDrawString(
                &gStatScreen.text[STATSCREEN_TEXT_STATUS],
                22, TEXT_COLOR_SYSTEM_BLUE,
                GetUnitStatusName(gStatScreen.unit));
        }

        // display turns

        if (gStatScreen.unit->statusIndex != UNIT_STATUS_NONE)
        {
            PutNumberSmall(
                gUiTmScratchA + TILEMAP_INDEX(16, 11),
                0, gStatScreen.unit->statusDuration);
        }
    }
    else
    {
        // I do not understand what this is for

        struct Unit tmp = *gStatScreen.unit;

        tmp.statusIndex = 0;

        if (gStatScreen.unit->statusIndex == UNIT_STATUS_NONE)
        {
            Text_InsertDrawString(
                &gStatScreen.text[STATSCREEN_TEXT_STATUS],
                24, TEXT_COLOR_SYSTEM_BLUE,
                GetUnitStatusName(&tmp));
        }
        else
        {
            Text_InsertDrawString(
                &gStatScreen.text[STATSCREEN_TEXT_STATUS],
                22, TEXT_COLOR_SYSTEM_BLUE,
                GetUnitStatusName(&tmp));
        }
    }

    // display affininity icon

    DrawIcon(
        gUiTmScratchA + TILEMAP_INDEX(20, 5),
        GetUnitAffinityIcon(gStatScreen.unit),
        TILEREF(0, STATSCREEN_BGPAL_EXTICONS));

    //DisplayBwl();
	
}

void DisplayPage1(void)
{

    int i, item;
    const char* str;
/*
    Decompress(
        gUnknown_08A02204,
        gGenericBuffer);

    CallARM_FillTileRect(
        gUiTmScratchC + TILEMAP_INDEX(16, 2),
        gGenericBuffer, TILEREF(0x40, STATSCREEN_BGPAL_3));
*/
    DisplayTexts(sPage1TextInfo);

    if (!UNIT_IS_GORGON_EGG(gStatScreen.unit))
    {
        for (i = 0; (i < UNIT_ITEM_COUNT) && (item = gStatScreen.unit->items[i]); ++i)
        {
            int color;

            if ((gStatScreen.unit->state & US_DROP_ITEM) && (i == GetUnitItemCount(gStatScreen.unit) - 1))
                color = TEXT_COLOR_SYSTEM_GREEN;
            else
                color = IsItemDisplayUsable(gStatScreen.unit, item)
                    ? TEXT_COLOR_SYSTEM_WHITE
                    : TEXT_COLOR_SYSTEM_GRAY;

            DrawItemStatScreenLine(
                &gStatScreen.text[STATSCREEN_TEXT_ITEM0 + i],
                item, color,
                gUiTmScratchA + TILEMAP_INDEX(1, i*2));
        }
    }

    i = GetUnitEquippedWeaponSlot(gStatScreen.unit);
    item = 0;

    if (gStatScreen.unit->pClassData->number != CLASS_GORGONEGG)
    {
        if ((gStatScreen.unit->pClassData->number != CLASS_GORGONEGG2) && (i >= 0))
        {
            PutSpecialChar(
                gUiTmScratchA + TILEMAP_INDEX(16, i*2),
                TEXT_COLOR_SYSTEM_WHITE, TEXT_SPECIAL_35);

            CallARM_FillTileRect(
                gUiTmScratchC + TILEMAP_INDEX(1, 1 + i*2),
                gUnknown_08A02250, TILEREF(0x40, STATSCREEN_BGPAL_3));

            item = gStatScreen.unit->items[i];
        }
    }

    if (!UNIT_IS_GORGON_EGG(gStatScreen.unit))
    {
        PutNumberOrBlank(
            gUiTmScratchA + TILEMAP_INDEX(22,  2),
            TEXT_COLOR_SYSTEM_BLUE, gBattleActor.battleAttack);

        PutNumberOrBlank(
            gUiTmScratchA + TILEMAP_INDEX(22,  4),
            TEXT_COLOR_SYSTEM_BLUE, gBattleActor.battleHitRate);

        PutNumberOrBlank(
            gUiTmScratchA + TILEMAP_INDEX(28, 2),
            TEXT_COLOR_SYSTEM_BLUE, gBattleActor.battleCritRate);

        PutNumberOrBlank(
            gUiTmScratchA + TILEMAP_INDEX(28, 4),
            TEXT_COLOR_SYSTEM_BLUE, gBattleActor.battleAvoidRate);
    }
    else
    {
        PutNumberOrBlank(
            gUiTmScratchA + TILEMAP_INDEX(22,  2),
            TEXT_COLOR_SYSTEM_BLUE, 0xFF);

        PutNumberOrBlank(
            gUiTmScratchA + TILEMAP_INDEX(22,  4),
            TEXT_COLOR_SYSTEM_BLUE, 0xFF);

        PutNumberOrBlank(
            gUiTmScratchA + TILEMAP_INDEX(28, 2),
            TEXT_COLOR_SYSTEM_BLUE, 0xFF);

        PutNumberOrBlank(
            gUiTmScratchA + TILEMAP_INDEX(28, 4),
            TEXT_COLOR_SYSTEM_BLUE, gBattleActor.battleAvoidRate);

        item = 0;
    }

    // TODO: macro, maybe?

    str = GetItemDisplayRangeString(item);
    Text_InsertDrawString(
        &gStatScreen.text[STATSCREEN_TEXT_BSRANGE],
        47 - GetStringTextLen(str),
        TEXT_COLOR_SYSTEM_BLUE, str);

    for (i = 0; i < 8; ++i)
    {
        gUiTmScratchA[TILEMAP_INDEX(17 + i, 0)] = TILEREF(0x60 + i, STATSCREEN_BGPAL_7);
        gUiTmScratchA[TILEMAP_INDEX(17 + i, 1)] = TILEREF(0x68 + i, STATSCREEN_BGPAL_7);
    }

}

void DisplayPage2(void)
{
/*
    if (UnitHasMagicRank(gStatScreen.unit))
    {
        // NOTE: this was likely present in the J version
        // DisplayTexts(sPage2TextInfo_Magical);

        DisplayWeaponExp(0, 1, 1, ITYPE_ANIMA);
        DisplayWeaponExp(1, 1, 3, ITYPE_LIGHT);
        DisplayWeaponExp(2, 1, 5, ITYPE_DARK);
        DisplayWeaponExp(3, 1, 7, ITYPE_STAFF);
    }
    else
    {
        // NOTE: this was likely present in the J version
        // DisplayTexts(sPage2TextInfo_Physical);

        DisplayWeaponExp(0, 1, 1, ITYPE_SWORD);
        DisplayWeaponExp(1, 1, 3, ITYPE_LANCE);
        DisplayWeaponExp(2, 1, 5, ITYPE_AXE);
        DisplayWeaponExp(3, 1, 7, ITYPE_BOW);
    }
*/
        DisplayWeaponExp(0, 1, 1, ITYPE_ANIMA);
        DisplayWeaponExp(1, 1, 3, ITYPE_LIGHT);
        DisplayWeaponExp(2, 1, 5, ITYPE_DARK);
        DisplayWeaponExp(3, 1, 7, ITYPE_STAFF);
        DisplayWeaponExp(0, 8, 1, ITYPE_SWORD);
        DisplayWeaponExp(1, 8, 3, ITYPE_LANCE);
        DisplayWeaponExp(2, 8, 5, ITYPE_AXE);
        DisplayWeaponExp(3, 8, 7, ITYPE_BOW);
		
		DisplaySupportList();

}

void DisplaySupportList(void)
{
    int yTile = 0, lineNum = 0;

    int textColor = GetUnitTotalSupportLevel(gStatScreen.unit) == MAX_SIMULTANEOUS_SUPPORT_COUNT
        ? TEXT_COLOR_SYSTEM_GREEN
        : TEXT_COLOR_SYSTEM_WHITE;

    int supportAmt = GetUnitSupporterCount(gStatScreen.unit);
    int supportId  = 0;

    while (supportId < supportAmt)
    {
        int level = GetUnitSupportLevel(gStatScreen.unit, supportId);

        if (level != 0)
        {
            int rankColor;

            u8 pid = GetUnitSupporterCharacter(gStatScreen.unit, supportId);

            DrawIcon(
                gUiTmScratchA + TILEMAP_INDEX(15, yTile),
                GetCharacterAffinityIcon(pid),
                TILEREF(0, STATSCREEN_BGPAL_EXTICONS));

            PutDrawText(&gStatScreen.text[STATSCREEN_TEXT_SUPPORT0 + lineNum],
                gUiTmScratchA + TILEMAP_INDEX(17, yTile),
                textColor, 0, 0,
                GetStringFromIndex(GetCharacterData(pid)->nameTextId));

            rankColor = TEXT_COLOR_SYSTEM_BLUE;

            if (level == 3)
                rankColor = TEXT_COLOR_SYSTEM_GREEN;

            if (textColor == TEXT_COLOR_SYSTEM_GREEN)
                rankColor = TEXT_COLOR_SYSTEM_GREEN;

            PutSpecialChar(gUiTmScratchA + TILEMAP_INDEX(22, yTile),
                rankColor, GetSupportLevelUiChar(level));

            yTile += 2;
            lineNum++;
        }

        supportId++;
    }
}