PocVillage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PocVillage_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PocVillage_OnFrame
	.byte 0

PocVillage_OnTransition::
	setrespawn HEAL_LOCATION_POC_VILLAGE
	end

PocVillage_OnFrame::
	map_script_2 VAR_POC_INTRO, 0, PocVillage_Intro
	.2byte 0

PocVillage_Intro::
	lockall
	setflag FLAG_SYS_B_DASH
	setvar VAR_POC_INTRO, 1
	msgbox PocVillage_Text_Intro, MSGBOX_DEFAULT
	releaseall
	end

PocVillage_Professor::
	lock
	faceplayer
	goto_if_eq VAR_POC_STARTER, 1, PocVillage_ProfessorAgain
	msgbox PocVillage_Text_Starter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PocVillage_ProfessorLater
	givemon SPECIES_SPRIGATITO, 8
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_SYS_POKEDEX_GET
	special EnableNationalPokedex
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_POC_STARTER, 1
	giveitem ITEM_POKE_BALL, 10
	giveitem ITEM_POTION, 5
	msgbox PocVillage_Text_Received, MSGBOX_DEFAULT
	release
	end

PocVillage_ProfessorAgain::
	msgbox PocVillage_Text_North, MSGBOX_DEFAULT
	release
	end

PocVillage_ProfessorLater::
	msgbox PocVillage_Text_Later, MSGBOX_DEFAULT
	release
	end

PocVillage_Help::
	msgbox PocVillage_Text_Help, MSGBOX_NPC
	end

PocVillage_Sign::
	msgbox PocVillage_Text_Sign, MSGBOX_SIGN
	end

PocVillage_Text_Intro::
	.string "Welcome to the region demo!\n"
	.string "Speak to the professor ahead.\p"
	.string "Then follow the northern trail\n"
	.string "and challenge the scout.\p"
	.string "Hold B to run. START: menu.\n"
	.string "The house offers free healing.$"

PocVillage_Text_Starter::
	.string "Ready to test a new adventure?\p"
	.string "Take a level 8 SPRIGATITO\n"
	.string "as your partner?$"

PocVillage_Text_Received::
	.string "SPRIGATITO joined your team!\n"
	.string "Your NATIONAL POKéDEX is ready.\p"
	.string "You also have 10 POKé BALLS\n"
	.string "and 5 POTIONS.\p"
	.string "Catch POKéMON in the grass.\n"
	.string "Beat the scout to open the gate.$"

PocVillage_Text_North::
	.string "Follow the northern trail.\n"
	.string "The house offers free healing.\p"
	.string "After beating the scout, read\n"
	.string "sign beyond the gate.$"

PocVillage_Text_Later::
	.string "Come back when you are ready.$"

PocVillage_Text_Help::
	.string "Use START to open the menu.\n"
	.string "Choose SAVE to keep your progress.\p"
	.string "In battle, BAG holds POKé BALLS.\n"
	.string "They only work on wild POKéMON.$"

PocVillage_Text_Sign::
	.string "DEMO VILLAGE\n"
	.string "North: DEMO TRAIL\p"
	.string "House: free healing\n"
	.string "Professor: starter POKéMON$"
