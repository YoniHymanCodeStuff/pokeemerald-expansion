#ifndef GUARD_LEG_ONE_H
#define GUARD_LEG_ONE_H
extern u16 gLegOpeningPreferences;
extern bool8 gLegOpenMovesPage;
void LegOneApplyPreferences(void);
void LegOnePreviewStarter(void);
void LegOneGiveStarter(void);
void LegOneBufferNeville(void);
void LegOneBufferBall(void);
void LegOneSetupBattle(void);
void LegOneRemoveChosenBalls(void);
void LegOneTrackLevel(u32 level);
void LegOneMoveActor(void);
void LegOnePrepareChoice(void);
void LegOneApproachChosenBall(void);
void LegOneTakeBall(void);
void LegOneLiftTableBalls(void);
bool32 LegOneIsPracticeBattle(void);
#endif
