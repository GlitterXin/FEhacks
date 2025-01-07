#include "gbafe.h"

void StatScreen_InitDisplay(struct Proc* proc)
{
    u16 bgConfig[12] =
    {
        0x0000, 0x6000, 0,
        0x0000, 0x6800, 0,
        0x8000, 0x7000, 0,
        0x8000, 0x7800, 0,
    };

    SetupBackgrounds(bgConfig);

    UnpackUiFramePalette(STATSCREEN_BGPAL_3);
    RegisterBlankTile(0x400);

    BG_Fill(gBG2TilemapBuffer, 0);
    BG_EnableSyncByMask(BG2_SYNC_BIT);

    sub_80156D4();
    ApplyUnitSpritePalettes();

    // TODO: port the macros from mapanim wip

    gLCDControlBuffer.dispcnt.win0_on   = TRUE;
    gLCDControlBuffer.dispcnt.win1_on   = FALSE;
    gLCDControlBuffer.dispcnt.objWin_on = FALSE;

    gLCDControlBuffer.win0_left   = 0;
    gLCDControlBuffer.win0_top    = 80;
    gLCDControlBuffer.win0_right  = 240;
    gLCDControlBuffer.win0_bottom = 81;

    gLCDControlBuffer.wincnt.win0_enableBg0 = FALSE;
    gLCDControlBuffer.wincnt.win0_enableBg1 = FALSE;
    gLCDControlBuffer.wincnt.win0_enableBg2 = FALSE;
    gLCDControlBuffer.wincnt.win0_enableBg3 = TRUE;
    gLCDControlBuffer.wincnt.win0_enableObj = TRUE;

    gLCDControlBuffer.wincnt.wout_enableBg0 = TRUE;
    gLCDControlBuffer.wincnt.wout_enableBg1 = TRUE;
    gLCDControlBuffer.wincnt.wout_enableBg2 = TRUE;
    gLCDControlBuffer.wincnt.wout_enableBg3 = TRUE;
    gLCDControlBuffer.wincnt.wout_enableObj = TRUE;

    gLCDControlBuffer.wincnt.win0_enableBlend = TRUE;
    gLCDControlBuffer.wincnt.win1_enableBlend = TRUE;
    gLCDControlBuffer.wincnt.wout_enableBlend = TRUE;

    // Load and display Halo

    Decompress(
        gUnknown_08A064E0, (void*)(VRAM + 0x220 * 0x20));

    ApplyPalette(gUnknown_08A0731C, STATSCREEN_BGPAL_HALO);

    Decompress(
        gUnknown_08A071FC, gGenericBuffer);

    CallARM_FillTileRect(gBG1TilemapBuffer + TILEMAP_INDEX(12, 0),
        gGenericBuffer, TILEREF(0x220, STATSCREEN_BGPAL_HALO));

    // Load and display Background

    Decompress(
        gUnknown_08A03368, (void*)(VRAM + 0x580 * 0x20));

    ApplyPalettes(gUnknown_08A06460, STATSCREEN_BGPAL_BACKGROUND, 4);

    Decompress(gUnknown_08A05F10, gGenericBuffer);

    CallARM_FillTileRect(gBG3TilemapBuffer, gGenericBuffer,
        TILEREF(0x180, 12));

    // Load object graphics

    Decompress(
        gUnknown_08A02274, (void*)(VRAM + 0x10000 + 0x240 * 0x20));

    LoadIconPalettes(STATSCREEN_BGPAL_ITEMICONS);

    UnpackUiBarPalette(STATSCREEN_BGPAL_6);

    LoadIconPalette(1, 0x13);

    Decompress(
        gUnknown_08A01F24, (void*)(VRAM + 0x440 * 0x20));

    ApplyPalette(gUnknown_08A021E4, STATSCREEN_BGPAL_7);

    LoadIconPalette(1, 0x14);

    Decompress(
        gUnknown_08A020F0, (void*)(VRAM + 0x60 * 0x20));

    gStatScreen.mu = NULL;

    ClearSlide(proc);
}

void StatScreen_Display(struct Proc* proc)
{
    // Get portrait id

    int fid = GetUnitPortraitId(gStatScreen.unit);

    if (gStatScreen.unit->state & US_BIT23)
        fid++;

    // Set page amount (in FE6, this was dependant on whether this is ally or enemy)
    gStatScreen.pageAmt = STATSCREEN_PAGE_MAX;

    // Init text and icons

    ResetText();
    ResetIconGraphics_();

    InitTexts();

    // Display portrait

    PutFace80x72(proc, gBG2TilemapBuffer + TILEMAP_INDEX(1, 1), fid,
        0x4E0, STATSCREEN_BGPAL_FACE);

    if (GetPortraitData(fid)->img)
        ApplyPalette(gUnknown_08A01EE4, STATSCREEN_BGPAL_2);
    else
        ApplyPalette(gUnknown_08A01F04, STATSCREEN_BGPAL_2);

    // Display Map Sprite

    EndAllMus();
    gStatScreen.mu = StartUiMu(gStatScreen.unit, 110, 40);

    // Draw left panel labels and info

    DisplayLeftPanel();

    // Draw page content

    DisplayPage(gStatScreen.page);

    TileMap_CopyRect(gUiTmScratchA, gBG0TilemapBuffer + TILEMAP_INDEX(0, 10), 30, 20);
    TileMap_CopyRect(gUiTmScratchC, gBG2TilemapBuffer + TILEMAP_INDEX(0, 10), 30, 20);

    BG_EnableSyncByMask(BG0_SYNC_BIT | BG1_SYNC_BIT | BG2_SYNC_BIT);
}

void PageSlide_OnLoop(struct StatScreenEffectProc* proc)
{
    int off;

    int len, dstOff, srcOff;

    // clear bg0, bg2 page area
    TileMap_FillRect(gBG0TilemapBuffer + TILEMAP_INDEX(0, 10), 30, 20, 0);
    TileMap_FillRect(gBG2TilemapBuffer + TILEMAP_INDEX(0, 10), 30, 20, 0);

    off = sPageSlideOffsetLut[proc->timer];

    if (off == INT8_MAX)
    {
        // INT8_MAX offset means switch to displaying next page

        DisplayPage(proc->newItem);

        proc->timer++;
        off = sPageSlideOffsetLut[proc->timer];
    }

    // compute len, dstOff and srcOff
    // len is the length of the display bit of the page
    // dstOff is the x offset to which to copy the page to
    // srcOff is the x offset from which to copy the page from

    if (proc->key & DPAD_LEFT)
        off = -off;

    len = 30 - abs(off);

    if (off < 0)
    {
        dstOff = 0;
        srcOff = -off;
    }
    else
    {
        dstOff = off;
        srcOff = 0;
    }

    TileMap_CopyRect(
        gUiTmScratchA + srcOff,
        gBG0TilemapBuffer + dstOff + TILEMAP_INDEX(0, 10),
        len, 20);

    TileMap_CopyRect(
        gUiTmScratchC + srcOff,
        gBG2TilemapBuffer + dstOff + TILEMAP_INDEX(0, 10),
        len, 20);

    BG_EnableSyncByMask(BG0_SYNC_BIT + BG1_SYNC_BIT + BG2_SYNC_BIT);

    proc->timer++;
    off = sPageSlideOffsetLut[proc->timer];

    if (off == INT8_MIN)
        Proc_Break(proc);
}