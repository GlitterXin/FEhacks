#include "gbafe.h"

void UnitSlide_FadeOutLoop(struct StatScreenEffectProc* proc)
{
    SetBlendConfig(1, proc->timer, 0x10 - proc->timer, 0);

    SetMuScreenPosition(gStatScreen.mu,
        110, 40 + gStatScreen.yDispOff);

    gStatScreen.yDispOff = Interpolate(2, proc->yDispInit, proc->yDispFinal, proc->timer, 0x10);

    proc->timer += 3;

    if (proc->timer > 0x10)
        Proc_Break(proc);
}

void UnitSlide_FadeInLoop(struct StatScreenEffectProc* proc)
{
    SetBlendConfig(1, 0x10 - proc->timer, proc->timer, 0);

    SetMuScreenPosition(gStatScreen.mu,
        110, 40 + gStatScreen.yDispOff);

    gStatScreen.yDispOff = Interpolate(5, proc->yDispInit, proc->yDispFinal, proc->timer, 0x10);

    proc->timer += 3;

    if (proc->timer >= 0x10)
        Proc_Break(proc);
}

void ClearSlide(struct Proc* proc)
{
    if (gStatScreen.mu)
        SetMuScreenPosition(gStatScreen.mu,
            110, 40);

    gLCDControlBuffer.bg0cnt.priority = 1;
    gLCDControlBuffer.bg1cnt.priority = 3;
    gLCDControlBuffer.bg2cnt.priority = 2;
    gLCDControlBuffer.bg3cnt.priority = 3;

    SetDefaultColorEffects();

    gStatScreen.inTransition = FALSE;
}