#include "gbafe.h"

#define _DECL_INFO const struct HelpBoxInfo const

void HbPopulate_SSWExp(struct HelpBoxProc* proc)
{
    u16 rankMsgLut[8] =
    {
        0x561, 0x562, 0x563, 0x564, 0x565, 0x566, 0x567, 0x568
    };

    int itemKind = proc->info->mid;
/*
    if (UnitHasMagicRank(gStatScreen.unit))
        itemKind += 4;
*/
    proc->mid = rankMsgLut[itemKind];
}

void HbRedirect_SSSupports(struct HelpBoxProc* proc)
{
    if (GetUnitTotalSupportLevel(gStatScreen.unit) == 0)
    {
        if (proc->moveKey == DPAD_RIGHT)
            TryRelocateHbRight(proc);
        else
            TryRelocateHbLeft(proc);
    }
}

/* Page 0 (Core stats & status) */
extern _DECL_INFO New_sHelpInfo_Char;
extern _DECL_INFO New_sHelpInfo_Class;
extern _DECL_INFO New_sHelpInfo_Level;
extern _DECL_INFO New_sHelpInfo_Exp;
extern _DECL_INFO New_sHelpInfo_HP;
extern _DECL_INFO New_gHelpInfo_Ss0Pow;
extern _DECL_INFO New_sHelpInfo_Ss0Skl;
extern _DECL_INFO New_sHelpInfo_Ss0Spd;
extern _DECL_INFO New_sHelpInfo_Ss0Lck;
extern _DECL_INFO New_sHelpInfo_Ss0Def;
extern _DECL_INFO New_sHelpInfo_Ss0Res;
extern _DECL_INFO New_sHelpInfo_Ss0Mov;
extern _DECL_INFO New_sHelpInfo_Ss0Con;
extern _DECL_INFO New_sHelpInfo_Ss0Aid;
extern _DECL_INFO New_sHelpInfo_Ss0Traveler;
extern _DECL_INFO New_sHelpInfo_Ss0Affinity;
extern _DECL_INFO New_sHelpInfo_Ss0Status;

_DECL_INFO New_sHelpInfo_Char =
{
    NULL, &New_sHelpInfo_Level, NULL, &New_sHelpInfo_Class,
    125, 24, 0, NULL, HbPopulate_SSCharacter,
};

_DECL_INFO New_sHelpInfo_Class =
{
    NULL, &New_sHelpInfo_Level, &New_sHelpInfo_Char, NULL,
    160, 24, 0x6E8, NULL, HbPopulate_SSClass,
};

_DECL_INFO New_sHelpInfo_Level =
{
    &New_sHelpInfo_Char, &New_gHelpInfo_Ss0Pow, NULL, &New_sHelpInfo_Exp,
    100, 48, 0x542, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Exp =
{
    &New_sHelpInfo_Char, &New_gHelpInfo_Ss0Pow, &New_sHelpInfo_Level, &New_sHelpInfo_HP,
    130, 48, 0x543, NULL, NULL
};

_DECL_INFO New_sHelpInfo_HP =
{
    &New_sHelpInfo_Char, &New_gHelpInfo_Ss0Pow, &New_sHelpInfo_Exp, NULL,
    160, 48, 0x544, NULL, NULL
};

_DECL_INFO New_gHelpInfo_Ss0Pow =
{
    &New_sHelpInfo_Level, &New_sHelpInfo_Ss0Skl, NULL, &New_sHelpInfo_Ss0Def,
    2, 88, 0x546, NULL, HbPopulate_SSPower,
};

_DECL_INFO New_sHelpInfo_Ss0Skl =
{
    &New_gHelpInfo_Ss0Pow, &New_sHelpInfo_Ss0Spd, NULL, &New_sHelpInfo_Ss0Res,
    2, 104, 0x548, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Spd =
{
    &New_sHelpInfo_Ss0Skl, &New_sHelpInfo_Ss0Lck, NULL, &New_sHelpInfo_Ss0Mov,
    2, 120, 0x549, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Lck =
{
    &New_sHelpInfo_Ss0Spd, NULL, NULL, &New_sHelpInfo_Ss0Con,
    2, 136, 0x54A, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Def =
{
    &New_sHelpInfo_Level, &New_sHelpInfo_Ss0Res, &New_gHelpInfo_Ss0Pow, &New_sHelpInfo_Ss0Aid,
    66, 88, 0x54B, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Res =
{
    &New_sHelpInfo_Ss0Def, &New_sHelpInfo_Ss0Mov, &New_sHelpInfo_Ss0Skl, &New_sHelpInfo_Ss0Traveler,
    66, 104, 0x54C, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Mov =
{
    &New_sHelpInfo_Ss0Res, &New_sHelpInfo_Ss0Con, &New_sHelpInfo_Ss0Spd, &New_sHelpInfo_Ss0Affinity,
    66, 120, 0x54D, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Con =
{
    &New_sHelpInfo_Ss0Mov, NULL, &New_sHelpInfo_Ss0Lck, &New_sHelpInfo_Ss0Status,
    66, 136, 0x54E, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Aid =
{
    &New_sHelpInfo_Level, &New_sHelpInfo_Ss0Traveler, &New_sHelpInfo_Ss0Def, NULL,
    130, 88, 0x54F, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Traveler =
{
    &New_sHelpInfo_Ss0Aid, &New_sHelpInfo_Ss0Affinity, &New_sHelpInfo_Ss0Res, NULL,
    130, 104, 0x550, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Affinity =
{
    &New_sHelpInfo_Ss0Traveler, &New_sHelpInfo_Ss0Status, &New_sHelpInfo_Ss0Mov, NULL,
    130, 120, 0x551, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss0Status =
{
    &New_sHelpInfo_Ss0Affinity, NULL, &New_sHelpInfo_Ss0Con, NULL,
    130, 136, 0, NULL, HbPopulate_SSStatus,
};

/* Page 1 (Items & battle stats) */
extern _DECL_INFO New_gHelpInfo_Ss1Char;
extern _DECL_INFO New_sHelpInfo_Ss1Class;
extern _DECL_INFO New_sHelpInfo_Ss1Level;
extern _DECL_INFO New_sHelpInfo_Ss1Exp;
extern _DECL_INFO New_sHelpInfo_Ss1HP;
extern _DECL_INFO New_gHelpInfo_Ss1Item0;
extern _DECL_INFO New_gHelpInfo_Ss1Item1;
extern _DECL_INFO New_gHelpInfo_Ss1Item2;
extern _DECL_INFO New_gHelpInfo_Ss1Item3;
extern _DECL_INFO New_gHelpInfo_Ss1Item4;

extern _DECL_INFO New_sHelpInfo_Ss1Atk;
extern _DECL_INFO New_sHelpInfo_Ss1Hit;
extern _DECL_INFO New_sHelpInfo_Ss1Rng;
extern _DECL_INFO New_sHelpInfo_Ss1Crit;
extern _DECL_INFO New_sHelpInfo_Ss1Avoid;

_DECL_INFO New_gHelpInfo_Ss1Char =
{
    NULL, &New_sHelpInfo_Ss1Level, NULL, &New_sHelpInfo_Ss1Class,
    125, 24, 0, NULL, HbPopulate_SSCharacter,
};

_DECL_INFO New_sHelpInfo_Ss1Class =
{
    NULL, &New_sHelpInfo_Ss1Level, &New_gHelpInfo_Ss1Char, NULL,
    160, 24, 0x6E8, NULL, HbPopulate_SSClass,
};

_DECL_INFO New_sHelpInfo_Ss1Level =
{
    &New_gHelpInfo_Ss1Char, &New_gHelpInfo_Ss1Item0, NULL, &New_sHelpInfo_Ss1Exp,
    100, 48, 0x542, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss1Exp =
{
    &New_gHelpInfo_Ss1Char, &New_gHelpInfo_Ss1Item0, &New_sHelpInfo_Ss1Level, &New_sHelpInfo_Ss1HP,
    130, 48, 0x543, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss1HP =
{
    &New_gHelpInfo_Ss1Char, &New_gHelpInfo_Ss1Item0, &New_sHelpInfo_Ss1Exp, NULL,
    160, 48, 0x544, NULL, NULL
};

_DECL_INFO New_gHelpInfo_Ss1Item0 =
{
    &New_sHelpInfo_Ss1Level, &New_gHelpInfo_Ss1Item1, NULL, &New_sHelpInfo_Ss1Atk,
    4, 80, 0, HbRedirect_SSItem, HbPopulate_SSItem,
};

_DECL_INFO New_gHelpInfo_Ss1Item1 =
{
    &New_gHelpInfo_Ss1Item0, &New_gHelpInfo_Ss1Item2, NULL, &New_sHelpInfo_Ss1Atk,
    4, 96, 1, HbRedirect_SSItem, HbPopulate_SSItem,
};

_DECL_INFO New_gHelpInfo_Ss1Item2 =
{
    &New_gHelpInfo_Ss1Item1, &New_gHelpInfo_Ss1Item3, NULL, &New_sHelpInfo_Ss1Atk,
    4, 112, 2, HbRedirect_SSItem, HbPopulate_SSItem,
};

_DECL_INFO New_gHelpInfo_Ss1Item3 =
{
    &New_gHelpInfo_Ss1Item2, &New_gHelpInfo_Ss1Item4, NULL, &New_sHelpInfo_Ss1Atk,
    4, 128, 3, HbRedirect_SSItem, HbPopulate_SSItem,
};

_DECL_INFO New_gHelpInfo_Ss1Item4 =
{
    &New_gHelpInfo_Ss1Item3, NULL, NULL, &New_sHelpInfo_Ss1Atk,
    4, 144, 4, HbRedirect_SSItem, HbPopulate_SSItem,
};

_DECL_INFO New_sHelpInfo_Ss1Atk =
{
    &New_sHelpInfo_Ss1Level, &New_sHelpInfo_Ss1Hit, &New_gHelpInfo_Ss1Item0, &New_sHelpInfo_Ss1Crit,
    135, 96, 0x55C, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss1Hit =
{
    &New_sHelpInfo_Ss1Atk, &New_sHelpInfo_Ss1Rng, &New_gHelpInfo_Ss1Item0, &New_sHelpInfo_Ss1Avoid,
    135, 112, 0x55D, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss1Rng =
{
    &New_sHelpInfo_Ss1Hit, NULL, &New_gHelpInfo_Ss1Item0, &New_sHelpInfo_Ss1Avoid,
    135, 128, 0x55E, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss1Crit =
{
    &New_sHelpInfo_Ss1Level, &New_sHelpInfo_Ss1Avoid, &New_sHelpInfo_Ss1Atk, NULL,
    185, 96, 0x55F, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss1Avoid =
{
    &New_sHelpInfo_Ss1Crit, &New_sHelpInfo_Ss1Rng, &New_sHelpInfo_Ss1Hit, NULL,
    185, 112, 0x560, NULL, NULL
};

/* Page 2 (Weapon ranks & supports) */
extern _DECL_INFO New_sHelpInfo_Ss2Char;
extern _DECL_INFO New_sHelpInfo_Ss2Class;
extern _DECL_INFO New_sHelpInfo_Ss2Level;
extern _DECL_INFO New_sHelpInfo_Ss2Exp;
extern _DECL_INFO New_sHelpInfo_Ss2HP;
extern _DECL_INFO gHelpInfo_Ss2AnimaRank;
extern _DECL_INFO gHelpInfo_Ss2LightRank;
extern _DECL_INFO gHelpInfo_Ss2DarkRank;
extern _DECL_INFO gHelpInfo_Ss2StaffRank;
extern _DECL_INFO gHelpInfo_Ss2SwordRank;
extern _DECL_INFO gHelpInfo_Ss2LanceRank;
extern _DECL_INFO gHelpInfo_Ss2AxeRank;
extern _DECL_INFO gHelpInfo_Ss2BowRank;
extern _DECL_INFO gHelpInfo_Ss2Support;

_DECL_INFO New_sHelpInfo_Ss2Char =
{
    NULL, &New_sHelpInfo_Ss2Level, NULL, &New_sHelpInfo_Ss2Class,
    125, 24, 0, NULL, HbPopulate_SSCharacter,
};

_DECL_INFO New_sHelpInfo_Ss2Class =
{
    NULL, &New_sHelpInfo_Ss2Level, &New_sHelpInfo_Ss2Char, NULL,
    160, 24, 0x6E8, NULL, HbPopulate_SSClass,
};

_DECL_INFO New_sHelpInfo_Ss2Level =
{
    &New_sHelpInfo_Ss2Char, &gHelpInfo_Ss2AnimaRank, NULL, &New_sHelpInfo_Ss2Exp,
    100, 48, 0x542, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss2Exp =
{
    &New_sHelpInfo_Ss2Char, &gHelpInfo_Ss2AnimaRank, &New_sHelpInfo_Ss2Level, &New_sHelpInfo_Ss2HP,
    130, 48, 0x543, NULL, NULL
};

_DECL_INFO New_sHelpInfo_Ss2HP =
{
    &New_sHelpInfo_Ss2Char, &gHelpInfo_Ss2AnimaRank, &New_sHelpInfo_Ss2Exp, NULL,
    160, 48, 0x544, NULL, NULL
};

_DECL_INFO gHelpInfo_Ss2AnimaRank =
{
    &New_sHelpInfo_Ss2Level, &gHelpInfo_Ss2LightRank, NULL, &gHelpInfo_Ss2SwordRank,
    4, 88, 4, NULL, HbPopulate_SSWExp,
};

_DECL_INFO gHelpInfo_Ss2LightRank =
{
    &gHelpInfo_Ss2AnimaRank, &gHelpInfo_Ss2DarkRank, NULL, &gHelpInfo_Ss2LanceRank,
    4, 104, 5, NULL, HbPopulate_SSWExp,
};

_DECL_INFO gHelpInfo_Ss2DarkRank =
{
    &gHelpInfo_Ss2LightRank, &gHelpInfo_Ss2StaffRank, NULL, &gHelpInfo_Ss2AxeRank,
    4, 120, 6, NULL, HbPopulate_SSWExp,
};

_DECL_INFO gHelpInfo_Ss2StaffRank =
{
    &gHelpInfo_Ss2DarkRank, NULL, NULL, &gHelpInfo_Ss2BowRank,
    4, 136, 7, NULL, HbPopulate_SSWExp,
};

_DECL_INFO gHelpInfo_Ss2SwordRank =
{
    &New_sHelpInfo_Ss2Level, &gHelpInfo_Ss2LanceRank, &gHelpInfo_Ss2AnimaRank, &gHelpInfo_Ss2Support,
    64, 88, 0, NULL, HbPopulate_SSWExp,
};

_DECL_INFO gHelpInfo_Ss2LanceRank =
{
    &gHelpInfo_Ss2SwordRank, &gHelpInfo_Ss2AxeRank, &gHelpInfo_Ss2LightRank, &gHelpInfo_Ss2Support,
    64, 104, 1, NULL, HbPopulate_SSWExp,
};

_DECL_INFO gHelpInfo_Ss2AxeRank =
{
    &gHelpInfo_Ss2LanceRank, &gHelpInfo_Ss2BowRank, &gHelpInfo_Ss2DarkRank, &gHelpInfo_Ss2Support,
    64, 120, 2, NULL, HbPopulate_SSWExp,
};

_DECL_INFO gHelpInfo_Ss2BowRank =
{
    &gHelpInfo_Ss2AxeRank, NULL, &gHelpInfo_Ss2StaffRank, &gHelpInfo_Ss2Support,
    64, 136, 3, NULL, HbPopulate_SSWExp,
};

_DECL_INFO gHelpInfo_Ss2Support =
{
    &New_sHelpInfo_Ss2Level, NULL, &gHelpInfo_Ss2SwordRank, &New_sHelpInfo_Ss2Level,
    120, 80, 0x569, HbRedirect_SSSupports, NULL,
};


void StartStatScreenHelp(int pageid, struct Proc* proc)
{
    LoadHelpBoxGfx(NULL, -1); // default

    if (!gStatScreen.help)
    {
        switch (pageid)
        {

        case STATSCREEN_PAGE_0:
            gStatScreen.help = &New_gHelpInfo_Ss0Pow;
            break;
        
        case STATSCREEN_PAGE_1:
            gStatScreen.help = &New_gHelpInfo_Ss1Item0;
            break;

        case STATSCREEN_PAGE_2:
            gStatScreen.help = &gHelpInfo_Ss2AnimaRank;
            break;

        } // switch (pageid)
    }

    StartMovingHelpBox(gStatScreen.help, proc);
}