// Local town map for the opening; does not expose the unrelated Hoenn map.
#include "global.h"
#include "bg.h"
#include "gpu_regs.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "scanline_effect.h"
#include "script.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/vars.h"

static const struct BgTemplate sMapBg = {.bg = 0, .charBaseIndex = 0, .mapBaseIndex = 31, .screenSize = 0, .paletteMode = 0, .priority = 0, .baseTile = 0};
static const struct WindowTemplate sMapWindow[] = {{.bg=0,.tilemapLeft=1,.tilemapTop=1,.width=28,.height=18,.paletteNum=15,.baseBlock=1}, DUMMY_WIN_TEMPLATE};
static const u16 sMapPalette[16] = {RGB(3,7,10),RGB(29,30,27),RGB(4,8,10),RGB(19,22,21),RGB(8,18,10),RGB(28,24,13)};
static const u8 sRoute[] = _("ROUTE 1");
static const u8 sOld[] = _("Old man's\nhome");
static const u8 sEd[] = _("Edwulf's\nhome");
static const u8 sNev[] = _("Neville's\nhome");
static const u8 sAstrid[] = _("Astrid's\nhome");
static const u8 sHome[] = _("Your home");
static const u8 sLab[] = _("Yew's lab");
static const u8 sBack[] = _("A/B: Back");
static void MapVBlank(void) {LoadOam(); ProcessSpriteCopyRequests(); TransferPlttBuffer();}
static void MapRun(void)
{
    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        FreeAllWindowBuffers();
        SetVBlankCallback(NULL);
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
}
static void MapInit(void)
{
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT,0);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0,&sMapBg,1);
    ResetAllBgsCoordinates();
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetPaletteFade();
    InitWindows(sMapWindow);
    DeactivateAllTextPrinters();
    LoadPalette(sMapPalette,BG_PLTT_ID(15),sizeof(sMapPalette));
    FillWindowPixelBuffer(0,PIXEL_FILL(1));
    FillWindowPixelRect(0,PIXEL_FILL(5),108,16,7,110);
    for (u32 y=40;y<=112;y+=36)
        FillWindowPixelRect(0,PIXEL_FILL(5),90,y,42,4);
    AddTextPrinterParameterized(0,FONT_NORMAL,sRoute,88,0,TEXT_SKIP_DRAW,NULL);
    AddTextPrinterParameterized(0,FONT_NORMAL,sOld,5,28,TEXT_SKIP_DRAW,NULL);
    AddTextPrinterParameterized(0,FONT_NORMAL,sEd,140,28,TEXT_SKIP_DRAW,NULL);
    AddTextPrinterParameterized(0,FONT_NORMAL,sNev,5,64,TEXT_SKIP_DRAW,NULL);
    AddTextPrinterParameterized(0,FONT_NORMAL,sAstrid,140,64,TEXT_SKIP_DRAW,NULL);
    AddTextPrinterParameterized(0,FONT_NORMAL,sHome,5,105,TEXT_SKIP_DRAW,NULL);
    AddTextPrinterParameterized(0,FONT_NORMAL,sLab,140,105,TEXT_SKIP_DRAW,NULL);
    AddTextPrinterParameterized(0,FONT_NORMAL,sBack,85,130,TEXT_SKIP_DRAW,NULL);
    PutWindowTilemap(0);
    CopyWindowToVram(0,COPYWIN_FULL);
    ShowBg(0);
    SetGpuReg(REG_OFFSET_DISPCNT,DISPCNT_MODE_0 | DISPCNT_BG0_ON);
    SetVBlankCallback(MapVBlank);
    SetMainCallback2(MapRun);
}
void LegOneShowTownMap(void) {SetMainCallback2(MapInit);}
