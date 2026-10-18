PocTrail_MapScripts::
	.byte 0

PocTrail_NoStarter::
	lockall
	msgbox PocTrail_Text_NoStarter, MSGBOX_DEFAULT
	closemessage
	warp MAP_POC_VILLAGE, 9, 12
	waitstate
	releaseall
	end

PocTrail_Gatekeeper::
	lock
	faceplayer
	trainerbattle_single TRAINER_POC_GATEKEEPER, PocTrail_Text_Challenge, PocTrail_Text_Defeated, PocTrail_OpenGate
	goto PocTrail_OpenGate

PocTrail_OpenGate::
	setflag FLAG_POC_GATE_OPEN
	msgbox PocTrail_Text_Open, MSGBOX_DEFAULT
	closemessage
	removeobject LOCALID_POC_GATEKEEPER
	release
	end

PocTrail_Finish::
	lockall
	setflag FLAG_POC_COMPLETE
	msgbox PocTrail_Text_Finish, MSGBOX_DEFAULT
	releaseall
	end

PocTrail_Text_NoStarter::
	.string "You need a partner first!\n"
	.string "Speak to the village professor.$"

PocTrail_Text_Challenge::
	.string "One battle before you pass!\n"
	.string "Ready to meet my team?$"

PocTrail_Text_Defeated::
	.string "Well played! The way is clear.$"

PocTrail_Text_Open::
	.string "You earned your way through.\n"
	.string "Read the sign ahead!$"

PocTrail_Text_Finish::
	.string "DEMO COMPLETE!\p"
	.string "New maps, newer POKéMON,\n"
	.string "and a working trainer gate.\p"
	.string "Keep exploring and catching!\n"
	.string "Save and reload to test progress.$"
