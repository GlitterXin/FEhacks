#include "gbafe.h"

void DisplayPageNameSprite(int pageid)
{
	
    int colorid;

    PutSprite(4,
        111 + gStatScreen.xDispOff, 1 + gStatScreen.yDispOff,
        sSprite_PageNameBack, TILEREF(0x293, 4) + 0xC00);

    PutSprite(4,
        114 + gStatScreen.xDispOff, 0 + gStatScreen.yDispOff,
        sPageNameSpriteLut[pageid], TILEREF(0x240 + sPageNameChrOffsetLut[pageid], 3) + 0xC00);

    colorid = (GetGameClock()/4) % 16;

    CpuCopy16(
        gUnknown_08A027FC[pageid] + colorid,
        PAL_OBJ(3) + 0xE,
        sizeof(u16));

    EnablePaletteSync();

}
