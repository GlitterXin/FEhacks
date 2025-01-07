#include "gbafe.h"

void DisplayLeftPanel(void)
{
    const char* namestr = GetStringFromIndex(UNIT_NAME_ID(gStatScreen.unit));
    unsigned namexoff = GetStringTextCenteredPos(0x30, namestr);

    BG_Fill(gBG0TilemapBuffer, 0);

    // Generate battle stats for unit for display later
    BattleGenerateUiStats(
        gStatScreen.unit,
        GetUnitEquippedWeaponSlot(gStatScreen.unit));

    // Display character name
    PutDrawText(
        &gStatScreen.text[STATSCREEN_TEXT_CHARANAME],
        gBG0TilemapBuffer + TILEMAP_INDEX(15, 3),
        TEXT_COLOR_SYSTEM_WHITE, namexoff, 0, namestr);

    // Display class name
    PutDrawText(
        &gStatScreen.text[STATSCREEN_TEXT_CLASSNAME],
        gBG0TilemapBuffer + TILEMAP_INDEX(21, 3),
        TEXT_COLOR_SYSTEM_WHITE, 0, 0,
        GetStringFromIndex(gStatScreen.unit->pClassData->nameTextId));

    // Display Lv/E labels
    PutTwoSpecialChar(gBG0TilemapBuffer + TILEMAP_INDEX(13, 6), TEXT_COLOR_SYSTEM_GOLD, TEXT_SPECIAL_LV_A, TEXT_SPECIAL_LV_B);
    PutSpecialChar(gBG0TilemapBuffer + TILEMAP_INDEX(17, 6), TEXT_COLOR_SYSTEM_GOLD, TEXT_SPECIAL_E);

    // Display Hp/'/' labels
    PutTwoSpecialChar(gBG0TilemapBuffer + TILEMAP_INDEX(21, 6), TEXT_COLOR_SYSTEM_GOLD, TEXT_SPECIAL_HP_A, TEXT_SPECIAL_HP_B);
    PutSpecialChar(gBG0TilemapBuffer + TILEMAP_INDEX(25, 6), TEXT_COLOR_SYSTEM_GOLD, TEXT_SPECIAL_SLASH);

    // Display level
    PutNumberOrBlank(gBG0TilemapBuffer + TILEMAP_INDEX(16, 6), TEXT_COLOR_SYSTEM_BLUE,
        gStatScreen.unit->level);

    // Display exp
    PutNumberOrBlank(gBG0TilemapBuffer + TILEMAP_INDEX(19, 6), TEXT_COLOR_SYSTEM_BLUE,
        gStatScreen.unit->exp);

    // Display current hp

    if (GetUnitCurrentHp(gStatScreen.unit) > 99)
    {
        // Display '--' if current hp > 99
        PutTwoSpecialChar(gBG0TilemapBuffer + TILEMAP_INDEX(23, 6), TEXT_COLOR_SYSTEM_BLUE,
            TEXT_SPECIAL_DASH, TEXT_SPECIAL_DASH);
    }
    else
    {
        // Display current hp
        PutNumberOrBlank(gBG0TilemapBuffer + TILEMAP_INDEX(24, 6), TEXT_COLOR_SYSTEM_BLUE,
            GetUnitCurrentHp(gStatScreen.unit));
    }

    // Display max hp

    if (GetUnitMaxHp(gStatScreen.unit) > 99)
    {
        // Display '--' if max hp > 99
        PutTwoSpecialChar(gBG0TilemapBuffer + TILEMAP_INDEX(26, 6), TEXT_COLOR_SYSTEM_BLUE,
            TEXT_SPECIAL_DASH, TEXT_SPECIAL_DASH);
    }
    else
    {
        // Display max hp
        PutNumberOrBlank(gBG0TilemapBuffer + TILEMAP_INDEX(27, 6), TEXT_COLOR_SYSTEM_BLUE,
            GetUnitMaxHp(gStatScreen.unit));
    }
}