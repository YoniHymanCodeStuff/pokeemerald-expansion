PocVillage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PocVillage_OnTransition
	.byte 0

PocVillage_OnTransition::
	setrespawn HEAL_LOCATION_POC_VILLAGE
	end
