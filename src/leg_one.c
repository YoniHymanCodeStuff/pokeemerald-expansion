#include "global.h"
#include "leg_one.h"
#include "battle.h"
#include "battle_setup.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "pokemon.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "constants/battle_partner.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/opponents.h"
#include "constants/species.h"
#include "constants/vars.h"

EWRAM_DATA u16 gLegOpeningPreferences = 0;
EWRAM_DATA bool8 gLegOpenMovesPage = FALSE;

void LegOneApplyPreferences(void)
{
    if (gLegOpeningPreferences & 1) FlagSet(FLAG_LEG_NICKNAME);
    if (gLegOpeningPreferences & 2) FlagSet(FLAG_LEG_FAST_LEVEL);
    if (gLegOpeningPreferences & 4) FlagSet(FLAG_LEG_SET_MOVES);
}

// PC, Neville, Astrid, Edwulf. The fifth Pokémon stays in the laboratory.
static const u16 sStarterSpecies[5] = {SPECIES_VULPIX, SPECIES_PSYDUCK, SPECIES_PHANPY, SPECIES_CRABRAWLER, SPECIES_DEERLING};
static const u8 sStarterAssignments[5][4] = {{0,2,1,4},{1,2,4,3},{2,1,4,3},{3,0,1,2},{4,1,0,3}};
static const u16 sAstridIds[5] = {TRAINER_LEG_ASTRID_PSYDUCK,TRAINER_LEG_ASTRID_DEERLING,TRAINER_LEG_ASTRID_DEERLING,TRAINER_LEG_ASTRID_PSYDUCK,TRAINER_LEG_ASTRID_VULPIX};
static const u16 sEdwulfIds[5] = {TRAINER_LEG_EDWULF_DEERLING,TRAINER_LEG_EDWULF_CRABRAWLER,TRAINER_LEG_EDWULF_CRABRAWLER,TRAINER_LEG_EDWULF_PHANPY,TRAINER_LEG_EDWULF_CRABRAWLER};
static const u16 sNevilleIds[5] = {PARTNER_LEG_NEVILLE_PHANPY,PARTNER_LEG_NEVILLE_PHANPY,PARTNER_LEG_NEVILLE_PSYDUCK,PARTNER_LEG_NEVILLE_VULPIX,PARTNER_LEG_NEVILLE_PSYDUCK};
extern u8 Leg_Text_Lab_DefeatA[];
extern u8 Leg_Text_Lab_DefeatE[];

static u32 StarterIndex(void)
{
    u32 index = VarGet(VAR_POC_STARTER);
    return index < ARRAY_COUNT(sStarterSpecies) ? index : 0;
}

void LegOnePreviewStarter(void)
{
    gSpecialVar_0x8004 = sStarterSpecies[StarterIndex()];
    StringCopy(gStringVar1, GetSpeciesName(gSpecialVar_0x8004));
}

void LegOneGiveStarter(void)
{
    ScriptGiveMon(sStarterSpecies[StarterIndex()], 5, ITEM_NONE);
    LegOneTrackLevel(5);
}

void LegOneBufferNeville(void)
{
    StringCopy(gStringVar1, GetSpeciesName(sStarterSpecies[sStarterAssignments[StarterIndex()][1]]));
}

void LegOneBufferBall(void)
{
    u32 index = gSpecialVar_0x8004;
    if (index >= ARRAY_COUNT(sStarterSpecies))
        index = 0;
    StringCopy(gStringVar1, GetSpeciesName(sStarterSpecies[index]));
}

void LegOneRemoveChosenBalls(void)
{
    u32 i;
    for (i = 0; i < 4; ++i)
    {
        u32 ball = sStarterAssignments[StarterIndex()][i];
        FlagSet(FLAG_LEG_BALL_0 + ball);
        RemoveObjectEventByLocalIdAndMap(5 + ball, MAP_NUM(MAP_LEG_LAB), MAP_GROUP(MAP_LEG_LAB));
    }
}

void LegOneSetupBattle(void)
{
    // Same setup as setmultitrainerbattle, selecting the pair for this starter.
    memset(&gTrainerBattleParameter, 0, sizeof(gTrainerBattleParameter));
    TRAINER_BATTLE_PARAM.opponentA = sAstridIds[StarterIndex()];
    TRAINER_BATTLE_PARAM.opponentB = sEdwulfIds[StarterIndex()];
    TRAINER_BATTLE_PARAM.defeatTextA = Leg_Text_Lab_DefeatA;
    TRAINER_BATTLE_PARAM.defeatTextB = Leg_Text_Lab_DefeatE;
    gPartnerTrainerId = TRAINER_PARTNER(sNevilleIds[StarterIndex()]);
}

void LegOneTrackLevel(u32 level)
{
    // Event-driven high-water mark; never reduced by a faint, release or level cap.
    if (level > VarGet(VAR_TRAINER_LEVEL))
        VarSet(VAR_TRAINER_LEVEL, level);
}

// Authored scene routes; one independent movement buffer per actor.
#include "script_movement.h"
#include "fieldmap.h"
#include "sprite.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
EWRAM_DATA static u8 sLegActorRoutes[5][96] = {0};
static void LegWalkTo(u8 actor, s16 x, s16 y, bool32 verticalFirst)
{
    u8 id, index, axis, n = 0;
    s16 cx, cy;
    u8 *moves;
    index = actor == OBJ_EVENT_ID_PLAYER ? 0 : actor;
    if (index > 4 || TryGetObjectEventIdByLocalIdAndMap(actor, MAP_NUM(MAP_LEG_LAB), MAP_GROUP(MAP_LEG_LAB), &id))
        return;
    moves = sLegActorRoutes[index];
    cx = gObjectEvents[id].currentCoords.x - MAP_OFFSET;
    cy = gObjectEvents[id].currentCoords.y - MAP_OFFSET;
    for (axis = 0; axis < 2; axis++)
    {
        bool32 vertical = axis == 0 ? verticalFirst : !verticalFirst;
        while ((vertical ? cy != y : cx != x) && n < 94)
        {
            if (vertical) { moves[n++] = cy < y ? MOVEMENT_ACTION_WALK_NORMAL_DOWN : MOVEMENT_ACTION_WALK_NORMAL_UP; cy += cy < y ? 1 : -1; }
            else { moves[n++] = cx < x ? MOVEMENT_ACTION_WALK_NORMAL_RIGHT : MOVEMENT_ACTION_WALK_NORMAL_LEFT; cx += cx < x ? 1 : -1; }
        }
    }
    moves[n] = MOVEMENT_ACTION_STEP_END;
    ScriptMovement_StartObjectMovementScript(actor, MAP_NUM(MAP_LEG_LAB), MAP_GROUP(MAP_LEG_LAB), moves);
}
void LegOneMoveActor(void) { LegWalkTo(gSpecialVar_0x8004, gSpecialVar_0x8005, gSpecialVar_0x8006, gSpecialVar_0x8007); }
void LegOnePrepareChoice(void)
{
    u32 role = gSpecialVar_0x8004;
    VarSet(VAR_LEG_REPLY, sStarterAssignments[StarterIndex()][role < 4 ? role : 0]);
}
void LegOneApproachChosenBall(void)
{
    u8 role = gSpecialVar_0x8004;
    u8 actor = role == 1 ? 2 : role == 2 ? 3 : 4;
    u8 *moves = sLegActorRoutes[actor];
    u32 n;
    LegWalkTo(actor, 4 + 2 * VarGet(VAR_LEG_REPLY), 6, FALSE);
    for (n = 0; n < 94 && moves[n] != MOVEMENT_ACTION_STEP_END; n++);
    moves[n++] = MOVEMENT_ACTION_FACE_UP;
    moves[n] = MOVEMENT_ACTION_STEP_END;
}
void LegOneTakeBall(void)
{
    u32 role = gSpecialVar_0x8004;
    u32 ball = sStarterAssignments[StarterIndex()][role < 4 ? role : 0];
    FlagSet(FLAG_LEG_BALL_0 + ball);
    RemoveObjectEventByLocalIdAndMap(5 + ball, MAP_NUM(MAP_LEG_LAB), MAP_GROUP(MAP_LEG_LAB));
}
void LegOneLiftTableBalls(void)
{
    u8 i, id;
    for (i = 5; i <= 9; i++)
        if (!TryGetObjectEventIdByLocalIdAndMap(i, MAP_NUM(MAP_LEG_LAB), MAP_GROUP(MAP_LEG_LAB), &id))
        {
            gObjectEvents[id].fixedPriority = TRUE;
            gSprites[gObjectEvents[id].spriteId].oam.priority = 0;
            gSprites[gObjectEvents[id].spriteId].y2 = -16;
            gSprites[gObjectEvents[id].spriteId].subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
        }
}
bool32 LegOneIsPracticeBattle(void)
{
    return gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_LEG_LAB)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_LEG_LAB) && VarGet(VAR_LEG_STAGE) == 3;
}
