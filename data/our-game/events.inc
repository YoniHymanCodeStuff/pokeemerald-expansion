LegLab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LegLab_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LegLab_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LegLab_OnWarp
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, LegLab_BallsLayer
	.byte 0

LegLab_OnWarp::
	map_script_2 VAR_TEMP_1, 0, LegLab_BallsInit
	.2byte 0

LegLab_BallsInit::
	setvar VAR_TEMP_1, 1

LegLab_BallsLayer::
	callnative LegOneLiftTableBalls
	end

LegLab_OnTransition::
	setrespawn HEAL_LOCATION_POC_VILLAGE
	end

LegLab_OnFrame::
	map_script_2 VAR_LEG_STAGE, 0, LegLab_Start
	.2byte 0
LegLab_Start::
	lockall
	setvar VAR_LEG_STAGE, 1
	setvar VAR_TRAINER_LEVEL, 5
	applymovement OBJ_EVENT_ID_PLAYER, Leg_Move_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Leg_Text_Lab_Welcome, MSGBOX_DEFAULT
	applymovement 2, Leg_Move_FaceRight
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Leg_Move_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Leg_Text_Lab_Whisper, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Interrupt, MSGBOX_DEFAULT
	applymovement 2, Leg_Move_FaceUp
	waitmovement 2
	applymovement OBJ_EVENT_ID_PLAYER, Leg_Move_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Leg_Text_Lab_Nerves, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Listen, MSGBOX_DEFAULT
	setvar VAR_LEG_STAGE, 2
	closemessage
	releaseall
	end
LegLab_Table::
	lockall
	setvar VAR_LEG_STAGE, 5
	applymovement OBJ_EVENT_ID_PLAYER, Leg_Move_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Leg_Text_Lab_Listening, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Hear, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Table, MSGBOX_DEFAULT
	releaseall
	end
LegLab_NoExit::
	lockall
	msgbox Leg_Text_Lab_FinishChoosing, MSGBOX_DEFAULT
	releaseall
	end
LegLab_Ball0::
	lockall
	setvar VAR_0x8004, 0
	callnative LegOneBufferBall
	goto_if_eq VAR_LEG_STAGE, 4, LegLab_BallResting
	setvar VAR_POC_STARTER, 0
	callnative LegOnePreviewStarter
	showmonpic VAR_0x8004, 10, 1
	msgbox Leg_Text_Ball_0, MSGBOX_YESNO
	copyvar VAR_LEG_REPLY, VAR_RESULT
	hidemonpic
	goto_if_eq VAR_LEG_REPLY, NO, LegLab_BallDeclined
	callnative LegOneGiveStarter
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_LEG_STAGE, 3
	setvar VAR_0x8004, 0
	callnative LegOneTakeBall
	msgbox Leg_Text_Lab_Chosen, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	goto_if_set FLAG_LEG_NICKNAME, LegLab_NameStarter
	msgbox Leg_Text_Lab_Nickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LegLab_NameStarter
	goto LegLab_Selected
LegLab_Ball1::
	lockall
	setvar VAR_0x8004, 1
	callnative LegOneBufferBall
	goto_if_eq VAR_LEG_STAGE, 4, LegLab_BallResting
	setvar VAR_POC_STARTER, 1
	callnative LegOnePreviewStarter
	showmonpic VAR_0x8004, 10, 1
	msgbox Leg_Text_Ball_1, MSGBOX_YESNO
	copyvar VAR_LEG_REPLY, VAR_RESULT
	hidemonpic
	goto_if_eq VAR_LEG_REPLY, NO, LegLab_BallDeclined
	callnative LegOneGiveStarter
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_LEG_STAGE, 3
	setvar VAR_0x8004, 0
	callnative LegOneTakeBall
	msgbox Leg_Text_Lab_Chosen, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	goto_if_set FLAG_LEG_NICKNAME, LegLab_NameStarter
	msgbox Leg_Text_Lab_Nickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LegLab_NameStarter
	goto LegLab_Selected
LegLab_Ball2::
	lockall
	setvar VAR_0x8004, 2
	callnative LegOneBufferBall
	goto_if_eq VAR_LEG_STAGE, 4, LegLab_BallResting
	setvar VAR_POC_STARTER, 2
	callnative LegOnePreviewStarter
	showmonpic VAR_0x8004, 10, 1
	msgbox Leg_Text_Ball_2, MSGBOX_YESNO
	copyvar VAR_LEG_REPLY, VAR_RESULT
	hidemonpic
	goto_if_eq VAR_LEG_REPLY, NO, LegLab_BallDeclined
	callnative LegOneGiveStarter
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_LEG_STAGE, 3
	setvar VAR_0x8004, 0
	callnative LegOneTakeBall
	msgbox Leg_Text_Lab_Chosen, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	goto_if_set FLAG_LEG_NICKNAME, LegLab_NameStarter
	msgbox Leg_Text_Lab_Nickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LegLab_NameStarter
	goto LegLab_Selected
LegLab_Ball3::
	lockall
	setvar VAR_0x8004, 3
	callnative LegOneBufferBall
	goto_if_eq VAR_LEG_STAGE, 4, LegLab_BallResting
	setvar VAR_POC_STARTER, 3
	callnative LegOnePreviewStarter
	showmonpic VAR_0x8004, 10, 1
	msgbox Leg_Text_Ball_3, MSGBOX_YESNO
	copyvar VAR_LEG_REPLY, VAR_RESULT
	hidemonpic
	goto_if_eq VAR_LEG_REPLY, NO, LegLab_BallDeclined
	callnative LegOneGiveStarter
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_LEG_STAGE, 3
	setvar VAR_0x8004, 0
	callnative LegOneTakeBall
	msgbox Leg_Text_Lab_Chosen, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	goto_if_set FLAG_LEG_NICKNAME, LegLab_NameStarter
	msgbox Leg_Text_Lab_Nickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LegLab_NameStarter
	goto LegLab_Selected
LegLab_Ball4::
	lockall
	setvar VAR_0x8004, 4
	callnative LegOneBufferBall
	goto_if_eq VAR_LEG_STAGE, 4, LegLab_BallResting
	setvar VAR_POC_STARTER, 4
	callnative LegOnePreviewStarter
	showmonpic VAR_0x8004, 10, 1
	msgbox Leg_Text_Ball_4, MSGBOX_YESNO
	copyvar VAR_LEG_REPLY, VAR_RESULT
	hidemonpic
	goto_if_eq VAR_LEG_REPLY, NO, LegLab_BallDeclined
	callnative LegOneGiveStarter
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_LEG_STAGE, 3
	setvar VAR_0x8004, 0
	callnative LegOneTakeBall
	msgbox Leg_Text_Lab_Chosen, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	goto_if_set FLAG_LEG_NICKNAME, LegLab_NameStarter
	msgbox Leg_Text_Lab_Nickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LegLab_NameStarter
	goto LegLab_Selected
LegLab_BallResting::
	msgbox Leg_BallRemaining, MSGBOX_DEFAULT

LegLab_BallDeclined::
	releaseall
	end

LegLab_NameStarter::
	call Common_EventScript_NameReceivedPartyMon
	goto LegLab_Selected
LegLab_Selected::
	closemessage
	setvar VAR_0x8004, OBJ_EVENT_ID_PLAYER
	setvar VAR_0x8005, 7
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_0x8004, OBJ_EVENT_ID_PLAYER
	setvar VAR_0x8005, 7
	setvar VAR_0x8006, 9
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Leg_Move_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Leg_Text_Lab_NevChoice, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_AstridTurn, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 9
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 3
	setvar VAR_0x8004, 2
	callnative LegOnePrepareChoice
	callnative LegOneApproachChosenBall
	waitmovement 3
	delay 16
	setvar VAR_0x8004, 2
	callnative LegOneTakeBall
	msgbox Leg_Text_Lab_AstridChoice, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 9
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 3
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 9
	setvar VAR_0x8006, 7
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 3
	applymovement 3, Leg_Move_FaceUp
	waitmovement 3
	msgbox Leg_Text_Lab_EdwulfTurn, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 10
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 4
	setvar VAR_0x8004, 3
	callnative LegOnePrepareChoice
	callnative LegOneApproachChosenBall
	waitmovement 4
	delay 16
	setvar VAR_0x8004, 3
	callnative LegOneTakeBall
	msgbox Leg_Text_Lab_EdwulfChoice, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 10
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 4
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 10
	setvar VAR_0x8006, 7
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 4
	applymovement 4, Leg_Move_FaceUp
	waitmovement 4
	msgbox Leg_Text_Lab_NevilleTurn, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 2
	msgbox Leg_Text_Lab_NevilleThinking, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1
	callnative LegOnePrepareChoice
	callnative LegOneApproachChosenBall
	waitmovement 2
	delay 16
	setvar VAR_0x8004, 1
	callnative LegOneTakeBall
	callnative LegOneBufferNeville
	msgbox Leg_Text_Lab_NevilleChoice, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 2
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 7
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 2
	applymovement 2, Leg_Move_FaceUp
	waitmovement 2
	msgbox Leg_Text_Lab_Serious, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Introduced, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Before, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Important, MSGBOX_DEFAULT
	dynmultipush Leg_Reply_Heard, 0
	dynmultipush Leg_Reply_Notes, 1
	dynmultistack 2, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, LegLab_Notes
	msgbox Leg_Text_Lab_Heard, MSGBOX_DEFAULT
	goto LegLab_Practice

LegLab_Notes::
	msgbox Leg_Text_Lab_Notes, MSGBOX_DEFAULT
	goto LegLab_Practice
LegLab_Practice::
	msgbox Leg_Text_Lab_Fun, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Practice, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Paper, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Safe, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, OBJ_EVENT_ID_PLAYER
	setvar VAR_0x8005, 5
	setvar VAR_0x8006, 11
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_0x8004, OBJ_EVENT_ID_PLAYER
	setvar VAR_0x8005, 5
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Leg_Move_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 5
	setvar VAR_0x8006, 13
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 2
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 5
	setvar VAR_0x8006, 14
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 2
	applymovement 2, Leg_Move_FaceRight
	waitmovement 2
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 11
	setvar VAR_0x8006, 11
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 3
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 11
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 3
	applymovement 3, Leg_Move_FaceLeft
	waitmovement 3
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 11
	setvar VAR_0x8006, 13
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 4
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 11
	setvar VAR_0x8006, 14
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 4
	applymovement 4, Leg_Move_FaceLeft
	waitmovement 4
	msgbox Leg_Text_Lab_ReadyA, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_ReadyE, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_ReadyN, MSGBOX_DEFAULT
	closemessage
	callnative LegOneSetupBattle
	special SavePlayerParty
	setvar VAR_0x8005, MULTI_BATTLE_2_VS_2
	callnative BattleSetup_StartMultiBattle
	waitstate
	copyvar VAR_LEG_REPLY, VAR_RESULT
	setvar VAR_0x8004, FRONTIER_UTIL_FUNC_SAVE_PARTY
	special CallFrontierUtilFunc
	special LoadPlayerParty
	goto_if_eq VAR_LEG_REPLY, B_OUTCOME_WON, LegLab_Won
	msgbox Leg_Text_Lab_LoseA, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_LoseE, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_LoseA2, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_LoseN, MSGBOX_DEFAULT
	goto LegLab_Feedback

LegLab_Won::
	setflag FLAG_LEG_LAB_WON
	msgbox Leg_Text_Lab_WinN, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_WinA, MSGBOX_DEFAULT
	goto LegLab_Feedback
LegLab_Feedback::
	closemessage
	addobject 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 3
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 11
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 7
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	applymovement 1, Leg_Move_FaceLeft
	waitmovement 1
	goto_if_set FLAG_LEG_LAB_WON, LegLab_WinFeedback
	msgbox Leg_Text_Lab_LoseY, MSGBOX_DEFAULT
	goto LegLab_AfterBattle

LegLab_WinFeedback::
	msgbox Leg_Text_Lab_WinY, MSGBOX_DEFAULT
	goto LegLab_AfterBattle
LegLab_AfterBattle::
	special HealPlayerParty
	msgbox Leg_Text_Lab_Rested, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_JustAsWell, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Program, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Service, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Opportunities, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_VictoryRoad, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Graduation, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_HowFar, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Routes, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 7
	setvar VAR_0x8006, 11
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 11
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 3
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 8
	setvar VAR_0x8006, 3
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	applymovement 1, Leg_Move_FaceUp
	waitmovement 1
	delay 24
	msgbox Leg_Text_Lab_Equipment, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 3
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 11
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	applymovement 1, Leg_Move_FaceLeft
	waitmovement 1
	delay 24
	setflag FLAG_SYS_POKEDEX_GET
	special EnableNationalPokedex
	msgbox Leg_Text_DexReceived, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 10
	setvar VAR_0x8006, 13
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 10
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	applymovement 1, Leg_Move_FaceRight
	waitmovement 1
	delay 16
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 10
	setvar VAR_0x8006, 14
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	applymovement 1, Leg_Move_FaceRight
	waitmovement 1
	delay 16
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 15
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 14
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	applymovement 1, Leg_Move_FaceLeft
	waitmovement 1
	delay 16
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 1
	applymovement 1, Leg_Move_FaceLeft
	waitmovement 1
	msgbox Leg_Text_Lab_Dex, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Contributing, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_FourTrainers, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Reports, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Automatic, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Invention, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Appreciate, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Goodbyes, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_Moving, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_GoodbyeHome, MSGBOX_DEFAULT
	msgbox Leg_Text_Lab_AfterThat, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 12
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 3
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 12
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 3
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 8
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 3
	setvar VAR_0x8004, 3
	setvar VAR_0x8005, 8
	setvar VAR_0x8006, 17
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 3
	removeobject 3
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 11
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 4
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 8
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 4
	setvar VAR_0x8004, 4
	setvar VAR_0x8005, 8
	setvar VAR_0x8006, 17
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 4
	removeobject 4
	msgbox Leg_Text_Lab_MeetNeville, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 5
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 1
	callnative LegOneMoveActor
	waitmovement 2
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 8
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 2
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 8
	setvar VAR_0x8006, 17
	setvar VAR_0x8007, 0
	callnative LegOneMoveActor
	waitmovement 2
	removeobject 2
	setflag FLAG_LEG_CLASS_LEFT
	setvar VAR_LEG_STAGE, 4
	releaseall
	end
LegLab_Yew::
	lock
	faceplayer
	msgbox Leg_Text_Lab_YewAgain, MSGBOX_DEFAULT
	release
	end
LegLab_Classmate::
	lock
	faceplayer
	msgbox Leg_Text_Lab_Table, MSGBOX_DEFAULT
	release
	end
Leg_Move_FaceUp::
	face_up
	step_end
Leg_Move_FaceDown::
	face_down
	step_end
Leg_Move_FaceLeft::
	face_left
	step_end
Leg_Move_FaceRight::
	face_right
	step_end
LegHome_MapScripts::
	.byte 0

LegHome_Mom::
	lock
	faceplayer
	special HealPlayerParty
	goto_if_set FLAG_LEG_MOM_GIFT, LegHome_Again
	msgbox Leg_Text_Mom_First, MSGBOX_DEFAULT
	goto_if_unset FLAG_LEG_LAB_WON, LegHome_HadBattle
	dynmultipush Leg_Reply_Won, 0
	dynmultipush Leg_Reply_Battled, 1
	dynmultistack 1, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, LegHome_HadBattle
	msgbox Leg_Text_Mom_Win, MSGBOX_DEFAULT
	goto LegHome_Gifts

LegHome_HadBattle::
	msgbox Leg_Text_Mom_Battle, MSGBOX_DEFAULT

goto LegHome_Gifts

LegHome_Gifts::
	msgbox Leg_Text_Mom_Shoes, MSGBOX_DEFAULT
	setflag FLAG_SYS_B_DASH
	msgbox Leg_Text_ShoesReceived, MSGBOX_DEFAULT
	msgbox Leg_Text_Mom_Map, MSGBOX_DEFAULT
	giveitem ITEM_TOWN_MAP
	msgbox Leg_Text_Mom_Farewell, MSGBOX_DEFAULT
	setflag FLAG_LEG_MOM_GIFT
	setvar VAR_LEG_FAREWELL, 1
	release
	end

LegHome_Again::
	msgbox Leg_Text_Mom_Again, MSGBOX_DEFAULT
	release
	end
LegNeville_MapScripts::
	.byte 0

LegNeville_Talk::
	lock
	faceplayer
	goto_if_set FLAG_LEG_NEV_TALKED, LegNeville_Again
	msgbox Leg_Text_Neville_Home, MSGBOX_DEFAULT
	dynmultipush Leg_Reply_Knows, 0
	dynmultipush Leg_Reply_Food, 1
	dynmultistack 2, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, LegNeville_Food
	msgbox Leg_Text_Neville_Knows, MSGBOX_DEFAULT
	goto LegNeville_Meet

LegNeville_Food::
	msgbox Leg_Text_Neville_Food, MSGBOX_DEFAULT

goto LegNeville_Meet

LegNeville_Meet::
	msgbox Leg_Text_Neville_Meet, MSGBOX_DEFAULT
	setflag FLAG_LEG_NEV_TALKED
	release
	end

LegNeville_Again::
	msgbox Leg_Text_Neville_Again, MSGBOX_DEFAULT
	release
	end
LegNeville_Mother::
	lock
	faceplayer
	msgbox Leg_Text_NevMom, MSGBOX_DEFAULT
	goto_if_set FLAG_LEG_NEVILLE_LEFT, LegNeville_MotherEnd
	msgbox Leg_Text_NevOnce, MSGBOX_DEFAULT
	msgbox Leg_Text_NevTwice, MSGBOX_DEFAULT

LegNeville_MotherEnd::
	msgbox Leg_Text_NevMom_End, MSGBOX_DEFAULT
	release
	end
LegAstrid_MapScripts::
	.byte 0
LegAstrid_Parent::
	lock
	faceplayer
	msgbox Leg_Text_AstridParent, MSGBOX_DEFAULT
	release
	end
LegEdwulf_MapScripts::
	.byte 0

LegEdwulf_Parent::
	lock
	faceplayer
	goto_if_set FLAG_LEG_ED_TALKED, LegEdwulf_Repeat
	msgbox Leg_Text_EdParents, MSGBOX_DEFAULT
	msgbox Leg_Text_EdParents2, MSGBOX_DEFAULT
	dynmultipush Leg_Reply_No, 0
	dynmultipush Leg_Reply_Yes, 1
	dynmultistack 2, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, 1, LegEdwulf_Yes
	msgbox Leg_Text_EdParents_No, MSGBOX_DEFAULT
	goto LegEdwulf_End

LegEdwulf_Yes::
	msgbox Leg_Text_EdParents_Yes, MSGBOX_DEFAULT

goto LegEdwulf_End

LegEdwulf_End::
	msgbox Leg_Text_EdParents_End, MSGBOX_DEFAULT
	setflag FLAG_LEG_ED_TALKED
	release
	end

LegEdwulf_Repeat::
	msgbox Leg_Text_EdParents_Again, MSGBOX_DEFAULT
	release
	end
LegEdwulf_Again::
	lock
	faceplayer
	msgbox Leg_Text_EdParents_Again, MSGBOX_DEFAULT
	release
	end
LegOldMan_MapScripts::
	.byte 0

LegOldMan_Talk::
	lock
	faceplayer
	goto_if_set FLAG_LEG_OLD_TALKED, LegOldMan_Again
	msgbox Leg_Text_OldMan, MSGBOX_DEFAULT
	setflag FLAG_LEG_OLD_TALKED
	release
	end

LegOldMan_Again::
	msgbox Leg_Text_OldMan_Again, MSGBOX_DEFAULT
	release
	end
Leg_Resident::
	lock
	faceplayer
	msgbox Leg_Text_Resident, MSGBOX_DEFAULT
	release
	end
Leg_Worker::
	lock
	faceplayer
	msgbox Leg_Text_Worker, MSGBOX_DEFAULT
	release
	end
Leg_SetMoves::
	lock
	faceplayer
	msgbox Leg_Text_SetMoves, MSGBOX_DEFAULT
	release
	end
Leg_Child::
	lock
	faceplayer
	msgbox Leg_Text_Child, MSGBOX_DEFAULT
	release
	end
Leg_Guide::
	lock
	faceplayer
	msgbox Leg_Text_Guide, MSGBOX_DEFAULT
	release
	end
Leg_Boundary::
	lock
	faceplayer
	msgbox Leg_Text_Boundary, MSGBOX_DEFAULT
	release
	end
Leg_FastLevel::
	lock
	faceplayer
	msgbox Leg_Text_FastLevel, MSGBOX_DEFAULT
	goto_if_set FLAG_LEG_FAST_LEVEL, Leg_FastLevelEnd
	msgbox Leg_Text_FastLevel_Off, MSGBOX_DEFAULT

Leg_FastLevelEnd::
	release
	end
Leg_Sign_LegHome::
	msgbox Leg_Text_Sign_Mom, MSGBOX_SIGN
	end
Leg_Sign_LegNeville::
	msgbox Leg_Text_Sign_Neville, MSGBOX_SIGN
	end
Leg_Sign_LegAstrid::
	msgbox Leg_Text_Sign_Astrid, MSGBOX_SIGN
	end
Leg_Sign_LegEdwulf::
	msgbox Leg_Text_Sign_Edwulf, MSGBOX_SIGN
	end
Leg_Sign_LegOldMan::
	msgbox Leg_Text_Sign_OldMan, MSGBOX_SIGN
	end
Leg_Sign_LegLab::
	msgbox Leg_Text_Sign_Lab, MSGBOX_SIGN
	end
Leg_NeedMom::
	lockall
	msgbox Leg_Text_NeedMom, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Leg_Move_Down
	waitmovement 0
	releaseall
	end
Leg_Complete::
	lockall
	setvar VAR_LEG_COMPLETE, 1
	setflag FLAG_LEG_NEVILLE_LEFT
	msgbox Leg_Text_Complete, MSGBOX_DEFAULT
	releaseall
	end
Leg_Preferences::
	lockall
	call Leg_PrefsSetup
	releaseall
	end

Leg_PrefsSetup::
	msgbox Leg_Text_Prefs, MSGBOX_DEFAULT
	msgbox Leg_Text_Prefs_Nick, MSGBOX_YESNO
	clearflag FLAG_LEG_NICKNAME
	goto_if_eq VAR_RESULT, NO, Leg_PrefsFast
	setflag FLAG_LEG_NICKNAME

Leg_PrefsFast::
	msgbox Leg_Text_Prefs_Fast, MSGBOX_YESNO
	clearflag FLAG_LEG_FAST_LEVEL
	goto_if_eq VAR_RESULT, NO, Leg_PrefsMoves
	setflag FLAG_LEG_FAST_LEVEL

Leg_PrefsMoves::
	msgbox Leg_Text_Prefs_Moves, MSGBOX_YESNO
	clearflag FLAG_LEG_SET_MOVES
	goto_if_eq VAR_RESULT, NO, Leg_PrefsDone
	setflag FLAG_LEG_SET_MOVES

Leg_PrefsDone::
	msgbox Leg_Text_Prefs_Done, MSGBOX_DEFAULT
	return
Leg_Move_Neville:
	walk_down
	walk_left
	face_right
	step_end
Leg_Move_Astrid:
	walk_right
	face_left
	step_end
Leg_Move_Edwulf:
	walk_down
	walk_right
	face_left
	step_end
Leg_Move_Player:
	walk_down
	face_right
	step_end
Leg_Move_ExitA:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	step_end
Leg_Move_ExitE:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
Leg_Move_ExitN:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
Leg_Move_Down:
	walk_down
	step_end
Leg_Option_0:
	.string "Vulpix$"
Leg_Option_1:
	.string "Psyduck$"
Leg_Option_2:
	.string "Phanpy$"
Leg_Option_3:
	.string "Crabrawler$"
Leg_Option_4:
	.string "Deerling$"
Leg_Reply_Heard:
	.string "We heard her.$"
Leg_Reply_Notes:
	.string "You two can take notes for us.$"
Leg_Reply_Won:
	.string "We won our first battle.$"
Leg_Reply_Battled:
	.string "We had our first battle.$"
Leg_Reply_Knows:
	.string "She knows you.$"
Leg_Reply_Food:
	.string "Any food in there?$"
Leg_Reply_No:
	.string "They didn't say.$"
Leg_Reply_Yes:
	.string "I'm sure we can.$"
Leg_BallRemaining:
	.string "A {STR_VAR_1} is resting inside.$"
Leg_TownMap::
	lockall
	callnative LegOneShowTownMap
	waitstate
	releaseall
	end
LegHomeUpstairs_MapScripts::
	.byte 0
LegHome_PC::
	lock
	faceplayer
	msgbox Leg_Text_Home_PC, MSGBOX_DEFAULT
	release
	end
LegHome_Bed::
	lockall
	msgbox Leg_Text_Home_Bed, MSGBOX_DEFAULT
	special HealPlayerParty
	releaseall
	end
