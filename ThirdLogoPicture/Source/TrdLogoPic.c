#include "global.h"
#include "ctc.h"
#include "proc.h"
#include "soundwrapper.h"
#include "hardware.h"
#include "bmlib.h"
#include "gamecontrol.h"
#include "opanim.h"

#include "TrdLogoPic.h"

void TryTickHSScreenExit(struct ProcOpAnimHS * proc)
{
    /* If not software-reset, HS screen cannot skip */
    if (proc->status == 3 || IsSoftwareReset())
    {
        if (gKeyStatusPtr->newKeys & 0xA)
            Proc_Goto(proc, 0);
    }
}

void GameIntroPrepareNintendofx(struct ProcOpAnimHS * proc)
{
    Sound_FadeOutBGM(1);
    SetupBackgrounds(NULL);
    SetPrimaryHBlankHandler(NULL);
    SetDispEnable(0, 0, 0, 0, 0);

    Decompress(Img_GameIntroNintendo, (void *)VRAM);
    Decompress(Tsa_GameIntroNintendo, gGenericBuffer);
    CallARM_FillTileRect(gBG0TilemapBuffer, gGenericBuffer, 0);

    Decompress(Img_IntelligentSystems, (void *)VRAM + 0x2000);
    Decompress(Tsa_IntelligentSystems, gGenericBuffer);
    CallARM_FillTileRect(gBG1TilemapBuffer, gGenericBuffer, 0x1100);
	
    Decompress(Img_TrdPic, (void *)VRAM + 0x4000);
    Decompress(Tsa_TrdPic, gGenericBuffer);
    CallARM_FillTileRect(gBG2TilemapBuffer, gGenericBuffer, 0x2200);


    CpuFastFill16(0, gPaletteBuffer, 0x400);
    EnablePaletteSync();
    BG_EnableSyncByMask(BG0_SYNC_BIT | BG1_SYNC_BIT | BG2_SYNC_BIT);

    SetDispEnable(1, 0, 0, 0, 0);

    proc->palette_timer = 0;
}

void GameIntroIntelligentSystemsFadeOUT(struct ProcOpAnimHS * proc)
{
    proc->palette_timer++;
    OpAnimHS_BrightenPalette(Pal_IntelligentSystems, 1, 3, 0x1E - proc->palette_timer, 0x1E);

    if (proc->palette_timer > 0x1D)
    {
        proc->delay_timer = 0x28;
        Proc_Break(proc);
    }
    TryTickHSScreenExit(proc);
}

void TrdPicFadeIN(struct ProcOpAnimHS * proc)
{
    if (proc->palette_timer == 0)
    {
        SetDispEnable(0, 0, 1, 0, 0);
    }
    proc->palette_timer++;
    OpAnimHS_BrightenPalette(Pal_TrdPic, 2, 5, proc->palette_timer, 0x1E);

    if (proc->palette_timer > 0x1D)
    {
        proc->delay_timer = 0x3C;
        Proc_Break(proc);
    }
    TryTickHSScreenExit(proc);
}

void TrdPicFadeOUT(struct ProcOpAnimHS * proc)
{
    proc->palette_timer++;
    OpAnimHS_BrightenPalette(Pal_TrdPic, 2, 5, 0x28 - proc->palette_timer, 0x28);

    if (proc->palette_timer > 0x27)
    {
        proc->delay_timer = 0x3C;
        Proc_Break(proc);
    }
    TryTickHSScreenExit(proc);
}

void SetOpAnimHsStatus3(struct ProcOpAnimHS * proc)
{
    proc->status = 3;
}

const struct ProcCmd New_ProcScr_GameEarlyStartUI[] = {
    PROC_YIELD,
    PROC_CALL(SetOpAnimHsStatus0),
    PROC_CALL(PrepareHealthAndSafetyScreen),

    /* "Warning-Health and Safety" */
    PROC_REPEAT(GameIntroHealthSafetyFadeIN),
    PROC_REPEAT(GameEarlyStartDelay),
    PROC_REPEAT(GameIntroHealthSafetyWaitButton),
    PROC_REPEAT(GameIntroHealthSafetyFadeOUT),
    PROC_REPEAT(GameEarlyStartDelay),

PROC_LABEL(0x3E7),

    /* "Nintendo" */
    PROC_CALL(GameIntroPrepareNintendofx),
    PROC_CALL(SetOpAnimHsStatus1),
    PROC_REPEAT(GameIntroNintendoFadeIN),
    PROC_REPEAT(GameEarlyStartDelay),
    PROC_REPEAT(GameIntroNintendoFadeOUT),
    PROC_REPEAT(GameEarlyStartDelay),

    /* "Intelligent Systems" */
    PROC_CALL(SetOpAnimHsStatus2),
    PROC_REPEAT(GameIntroIntelligentSystemsFadeIN),
    PROC_REPEAT(GameEarlyStartDelay),
    PROC_REPEAT(GameIntroIntelligentSystemsFadeOUT),
    PROC_REPEAT(GameEarlyStartDelay),
	PROC_CALL(EnableKeyComboResetEN),
	
	/* "Third Picture" */
	PROC_CALL(SetOpAnimHsStatus3),
    PROC_REPEAT(TrdPicFadeIN),
    PROC_REPEAT(GameEarlyStartDelay),
    PROC_REPEAT(TrdPicFadeOUT),
    PROC_REPEAT(GameEarlyStartDelay),
    PROC_GOTO(0x1),

PROC_LABEL(0x0),
    PROC_CALL(EnableKeyComboResetEN),
    PROC_CALL(sub_80CBF9C),
    PROC_REPEAT(sub_80CBFC0),

PROC_LABEL(0x1),
    PROC_END
};