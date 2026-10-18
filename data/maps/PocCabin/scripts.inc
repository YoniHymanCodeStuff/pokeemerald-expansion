PocCabin_MapScripts::
	.byte 0

PocCabin_Heal::
	lock
	faceplayer
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	msgbox PocCabin_Text_Heal, MSGBOX_DEFAULT
	release
	end

PocCabin_Text_Heal::
	.string "Your team is fully healed!\n"
	.string "Come back whenever you need.$"
