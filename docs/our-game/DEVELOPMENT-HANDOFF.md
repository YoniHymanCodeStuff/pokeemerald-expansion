# Development handoff — October 20, 2026

## Goal and next action

A dark Pokémon game built on pokeemerald-expansion. This is a native Emerald
ROM hack, not a browser remake. The current playable unit is the opening
ceremony and hometown farewell, ending at the Route 1 boundary. Review v0.3
with the user before extending Route 1. The user requested the GitHub backup
explicitly after delivery of v0.3. No new story expansion was requested.

Index assistant responses. The most recent response before this backup work
was 168; backup progress began at 169. Continue naturally in this thread.

## Creative decisions and authoritative documents

Full narrative and mechanics handoffs are beside this file. PROJECT-NOTES.md
preserves newer decisions: Yew, Astrid, Edwulf, Neville, five starter candidates,
regional hierarchy, opening relationships and automatic Pokédex surveillance.
Leg-One-Dialogue.txt and dialogue.json contain the implemented approved text.

Yew is a woman and the highest regional official, under a broader administration
shared with other isolated regions. She addresses four classmates in the intro.
Player and Neville are a joking, laid-back pair; Astrid and Edwulf are a more
serious pair. Astrid initially praises the government, then ultimately joins
Team Anarchy. Edwulf eventually knowingly accepts repression as necessary.
Neville struggles, fails the gauntlet and later becomes a route challenger.

The last specific user fixes, all implemented in v0.3:

1. Clear old text before printing a new message.
2. Integrate the approved custom character designs.
3. Face Yew, turn Neville toward the player to whisper, put balls on a table.
4. Return movement control when called forward; individual physical ball
   inspection, Pokémon sprite, description, and confirmation.
5. Rivals walk to their choices; remove each chosen ball immediately.
6. Move the player into practice position too.
7. A fainted player Pokémon does not end the doubles battle while Neville lives.
8. Yew walks into frame before feedback.
9. Stage retrieval and distribution of the Pokédex devices.
10. Two-storey player home with upstairs bed; Mom's supply dialogue says she is
    handing items over rather than leaving them by the door.
11. Astrid's mom and Edwulf's mom are named; Edwulf's parents stand around the
    table, offset from each other. Astrid and Edwulf are absent from their homes.

## Opening structure

New Game: Yew speech, player appearance/name, initial preferences, lab reveal.
Everyone faces Yew; Neville turns to whisper. Yew calls the player forward.
The player walks to the table and inspects five balls. On confirmation the
starter is given at level 5, the ball disappears, nickname handling runs, and
Astrid, Edwulf and Neville approach and take their assigned starters.
The two dialogue-choice replies converge on a supervised doubles battle.
Player+AI Neville oppose Astrid+Edwulf. Both win and loss continue.
Yew enters the practice floor for feedback, heals, explains the program,
retrieves devices and visits each child to distribute them. Rivals depart.
Mom supplies shoes and Town Map. Optional NPC conversations can be visited in
any order; only Mom's farewell is required to leave. Crossing north into
Route 1 sets the completion flag; player may return to town.

Starter assignments: PC / Neville / Astrid / Edwulf / unused:

- Vulpix / Phanpy / Psyduck / Deerling / Crabrawler
- Psyduck / Phanpy / Deerling / Crabrawler / Vulpix
- Phanpy / Psyduck / Deerling / Crabrawler / Vulpix
- Crabrawler / Vulpix / Psyduck / Phanpy / Deerling
- Deerling / Psyduck / Vulpix / Crabrawler / Phanpy

## Source ownership and scene states

- `data/our-game/dialogue.json`: editable dialogue.
- `dev_scripts/build_leg_one.py`: map geometry, maps, events and text generator.
- `data/our-game/events.inc`, `text.inc`: generated scripts/text, included by
  `data/event_scripts.s`. Edit the generator rather than these outputs.
- `src/leg_one.c`, `include/leg_one.h`: starter assignment, scene movement,
  battle setup, high-water trainer-level tracking and ball display helpers.
- `src/main_menu.c`: modified New Game speech and Yew intro portrait.
- `src/menu.c`: clear the message window in AddTextPrinterParameterized2.
  Do not apply the clear to the other printer helpers used for incremental UI.
- `src/battle_script_commands.c`: practice-only exception in
  WillPlayerWhiteOutIfPartnerWinsAlone. Normal partner battles are unchanged.
- `src/data/trainers.party`, `battle_partners.party`: level-5 rival teams.
  Trainer Pic names use spaces, e.g. `Leg Neville` -> TRAINER_PIC_LEG_NEVILLE.
- Maps: PocVillage is the hometown exterior; PocTrail is only the Route 1
  boundary. LegLab, LegHome, LegHomeUpstairs, LegNeville, LegAstrid,
  LegEdwulf, LegOldMan are the new interiors. PocCabin is legacy/unconnected.

VAR_LEG_STAGE (0x40FA): 0=not started, 1=opening dialogue, 2=free walk to table,
5=free inspection, 3=chosen starter/rival movements/practice, 4=lab complete.
VAR_TRAINER_LEVEL (0x40F7) is a monotonic high-water mark, not a party scan.
VAR_LEG_FAREWELL 0x40F8; VAR_LEG_COMPLETE 0x40F9; VAR_LEG_REPLY 0x40FB.
FLAG_LEG_* definitions are in flags.h, including per-ball and departed-rival
flags. Do not reuse their IDs for unrelated events.

The 17x18 lab has balls at x=4,6,8,10,12 and y=5; the counter occupies y=4/5.
Ball objects retain elevation 3 for interaction. The rendering helper applies
fixed priority, ignores subsprite priority and raises sprite y2 by 16 pixels.
The helper runs on warp-in and return from battle. Exit tiles (8,17)/(9,17)
are actual south arrow warp metatiles 0x0206/0x0207; plain floor here prevents
leaving, even if JSON warp coordinates are present.

Initial positions: PC (7,7), Neville (6,7), Astrid (9,7), Edwulf (10,7),
Yew (8,3). Practice: PC (5,12), Neville (5,14), Astrid (11,12), Edwulf (11,14).
Native movement buffers are independent per actor; every authored walk waits
before its next step. Routes avoid other actors and furniture. Yew detours up
before walking left after feedback to avoid walking through the player.

## Character assets

`graphics/our_game/references/` retains the approved front designs, nine-pose
walking sheets and Neville's back reference. `graphics/our_game/characters/`
holds native indexed assets: 64x64 portraits, 144x32 nine-frame walking sheets,
and Neville's 64x64 battle back sprite. All use transparent index 0 plus at
most 15 opaque colours. References are retained so nothing must be regenerated
from a remembered description.

Run `python3 dev_scripts/convert_character_assets.py` to reproduce native
packing. It thresholds alpha at 128 before finding bounds, locates gaps between
sheet rows, scales uniformly per character, and packs indices
[0,3,6,1,2,4,5,7,8]. The engine mirrors the left frames for right-facing motion.
Registration spans graphics/trainers.h, object-event graphics/pic/info tables,
trainer/event-object constants, and palette entries in event_object_movement.c.
Neville's back uses the static sBackAnims_None, not a multi-frame throw sequence.

## Build and test from a fresh Linux checkout

Install ordinary toolchain dependencies (on Ubuntu):

    sudo apt-get update
    sudo apt-get install -y build-essential pkg-config gcc-arm-none-eabi \
      binutils-arm-none-eabi libnewlib-arm-none-eabi libpng-dev python3

Use Pillow for content/asset checks and libmgba development headers for the
optional emulator bridge. A virtual environment with Pillow is sufficient.
The validated ARM compiler was GCC 13.2.1; mGBA was 0.10.2.

    python3 dev_scripts/build_leg_one.py
    python3 tests/leg-one/test_content.py
    make -j8

Output: pokeemerald.gba. A normal full build was tested, not the upstream
strict unused-variable CI configuration. The upstream CI workflow does not
run automatically on the leg-one branch. No green remote CI result is claimed.

After an interrupted or failed parallel build, inspect for zero-byte .o files
under build/ and remove those before retrying. Interrupted compiler pipelines
can leave empty objects that make linking fail with misleading undefined
references. Do not change LTO or remove functions to work around empty files.
Do not add generated build outputs to Git.

Optional headless emulator:

    gcc -shared -fPIC tests/leg-one/emulator.c -lmgba -o /tmp/leg-one-emulator.so
    LEG_ONE_EMULATOR_LIBRARY=/tmp/leg-one-emulator.so \
      ARM_NM=arm-none-eabi-nm python3 tests/leg-one/qa_opening.py

The self-contained replay boots New Game and checks five ball selections,
declining a choice, rival collection walks, one remaining ball and all practice
positions. It writes temporary checkpoints/screenshots/results to ../playtest.
The interactive driver accepts one JSON request per line; see its source.
Use four-frame button pulses; after a walk, allow movement to settle before
interacting. Message pages often require A; avoid repeatedly pressing A after
a conversation ends or you will immediately start it again.

SAVE validation must wait for the saved-game confirmation, not merely the
SAVING message. The emulator bridge exports real 128 KiB SRAM. An early export
while SAVING is on screen can still be blank. The final test reset the emulator
and used CONTINUE to restore the upstairs location, stage and farewell flag.

## Verification and limits

TEST-RESULTS.md contains the validated ROM checksum and exact test scope.
Nine structural/content checks and all five starter replays passed. Both battle
feedback branches, a player-first faint with Neville continuing, full ceremony,
lab exit, two-storey home, gifts and actual save/reload were exercised.
Edge-case HP adjustments were used in the battle regression tests; those are
identified in TEST-RESULTS.md rather than represented as normal balance tests.
The final parent placement adjustment was compiled and content checked.

This is not yet the whole intended mechanics system. Nickname prompting,
Set Moves/relearning, trainer-level tracking and preference flags exist.
Fast Leveling is recorded for the future Center. Full Nuzlocke rules, EV/IV and
nature editing, abilities, level caps, portable Center, Repel, Sadist NPC,
clock controls and move transfer remain design requirements, not shipped
features. The title screen still uses Emerald art/music. Town names are open.
No real Route 1 encounters, gym, cave or later-story gameplay is implemented.

## Recovery and Git history

Temporary workspace loss required recovery from the saved v0.2 source archive.
The recovered local history contains the complete v0.2 snapshot and v0.3 edits.
For GitHub, the final tree is attached to the existing poc-demo commit as its
first parent on a new leg-one branch, preserving the original repository
ancestry. The recovered development snapshots are preserved locally; publication uses
the complete current tree on top of the original poc-demo commit.
No force push or default-branch replacement is required. master and poc-demo
are preserved. Use the repository and its tracked artwork/docs for recovery;
do not depend on scratch paths, chat context or ephemeral emulator states.

The release ZIP contains the playable ROM, README, dialogue, test report,
source-info and visual test evidence. The source-info inside that original
release records the local pre-backup commit and remote_published=false as a
historical record; this backup commit now publishes that source tree.
The release checksum manifest identifies the exact archived ZIP and ROM.

Recovery detail: Git ignores tools/compresSmol and executable files even though
some are tracked upstream. They were explicitly restored from poc-demo before
this backup, so a fresh clone includes the build-tool sources.
