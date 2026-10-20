# Hometown opening — leg one, v0.3

Open `pokemon-leg-one-v0.3.gba` in your GBA emulator and start a **NEW GAME**.
Old proof-of-concept saves are not compatible with this story opening.
Press START to skip the title movie, then START again for the main menu.
Use NEW GAME to see Yew's introduction, choose your appearance and name,
and set your initial training preferences. SELECT on the title screen is an
upstream quick-start shortcut; avoid it for a normal story playthrough.

## This playable segment

- Yew's group introduction and the lab reveal.
- Vulpix, Psyduck, Phanpy, Crabrawler, or Deerling at level 5.
- Walk up to the table and inspect each physical Poké Ball for its Pokémon
  sprite, description and confirmation. Decline freely to inspect another.
- The other three classmates walk up and choose from the same pool. Their selections
  follow the approved five-row assignment table.
- A real multi battle: you and AI Neville versus Astrid and Edwulf.
- Both victory and defeat continue into the program briefing and Pokédex.
- A small, fully connected hometown with six buildings and a two-floor player home, optional dialogue
  choices, the old man's revised monologue, and the approved mechanics tips.
- Astrid and Edwulf are already gone when you visit their houses.
- Mom gives Running Shoes and a usable local Town Map. Hold B to run.
- The lab's northwest terminal can change this build's training preferences.
- Enabled SET MOVES opens the moves page from the party menu. Use the
  on-screen relearner prompt to choose a previously available level-up move.
- Leaving north requires Mom's farewell. Crossing into Route 1 marks the
  end of leg one; you can return, explore, and save normally.

## Prototype limits

This is the first implementation of the approved opening, not the full game.
The setting is labelled HOMETOWN / ROUTE 1 pending location names. Existing
Emerald tiles provide the environments. The approved custom Yew, Astrid,
Edwulf, and Neville designs now have native battle portraits and walking sprites;
Neville also has a custom partner battle back sprite.
The title screen still uses Emerald's original artwork/music.

The complete mechanics specification is design work, not a claim that every
feature has shipped. This segment provides nickname prompting, the free move
relearner, a persistent trainer-level high-water mark, and saved preference
flags. Fast Leveling is recorded for the later Center implementation; this
segment has no Center, wild captures, or grind. The larger Nuzlocke settings,
level caps, EV/IV editing, abilities, portable Center and Repel systems remain
future implementation work. No unused controls pretend to enforce those rules.
The opening battle cannot cause a game-over or permanent loss of your starter.

## Reviewing it

Try a fresh game with each starter, test the two battle outcomes, then visit
all houses and NPCs in different orders. Try leaving before visiting Mom.
Check the Town Map and SET MOVES, then save and reload after leaving the lab
and again after reaching Route 1. Repeated Mom visits must not duplicate items,
and returning to the lab must not replay the starter ceremony.

## Source

`data/our-game/dialogue.json` is the editable dialogue source.
`docs/our-game/Leg-One-Dialogue.txt` records the approved dialogue and decisions.
`dev_scripts/build_leg_one.py` regenerates the new maps and event scripts.

Build with the upstream toolchain and `make -j8`. No copyrighted base ROM is
needed for this source build. See upstream INSTALL.md and CREDITS.md.

## Revision v0.3 review points

New dialogue messages clear the previous message. At the lab reveal everyone
faces Yew; Neville turns toward you before whispering. Each claimed ball leaves
the table immediately. All four trainers walk to their practice positions.
Neville keeps fighting if your Pokémon faints first. Yew enters the practice
floor before feedback, retrieves devices from the desk, and hands them out.
Mom hands you the supplies and her dialogue now says so. Explore the upstairs
bedroom; Astrid's mom and Edwulf's mom/dad remain home after the children leave.

Start NEW GAME for this revision. Earlier saves and emulator save states can
retain the old positions and story stages.
