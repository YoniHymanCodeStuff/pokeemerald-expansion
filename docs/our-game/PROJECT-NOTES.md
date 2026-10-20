# Current decisions and implementation boundary

The narrative and mechanics handoffs preserve the earlier design discussions.
For the opening, **Leg-One-Dialogue.txt and data/our-game/dialogue.json supersede
all earlier dialogue drafts**. These include the user's latest board edits.

## Later decisions carried forward

- Professor **Yew**, a woman, runs the regional program. Other isolated regions
  exist under a common higher administration. She is the senior local official,
  rather than the ruler of the entire surviving world.
- Yew's approved concept: black neat ponytail, green glasses, a subtle smile,
  lab coat slightly longer than a knee-length dark dress, one hand explaining,
  the other holding a clipboard. Source inspiration B051.
- **Astrid** is the most idealistic, enthusiastic, preachy classmate, initially
  devoted to government service. Later disillusionment leads her to Anarchy.
  Approved concept: blonde frizzy hair, pale blue streak and headband, tie-dye
  shirt, jeans, a large backpack, a Poké Ball in her outstretched hand (B078).
- **Edwulf** is the modernized spelling. He is quiet, knowledgeable and reserved.
  He respects Astrid's initiative; she trusts his knowledge. He later accepts
  repression as a necessary evil, rather than remaining oblivious to it.
  Approved concept: short black buzz cut, white button-down, dark trousers (B017).
- **Neville**, the player's best friend, is nervous, talkative, kind and prepared
  from reading, but struggles under pressure. Both enjoy joking around.
  Approved concept: stocky, orange-brown hair, no glasses, brown vest over black
  shirt, green trousers, white/red sneakers; less baby-faced (B030).
- These four classmates already know each other. The initial divide is
  player/Neville versus Astrid/Edwulf. The latter pair dislike their levity.
- Starter pool: Vulpix, Psyduck, Phanpy, Crabrawler, Deerling. Four chosen,
  one left at the lab. See the assignment table in the dialogue log.
- Early moves stay unchanged. No Infinite Repel until before the first dungeon;
  no significant early TM reward is planned in this segment.
- Pokédex scanning is automatic. The player is unknowingly providing government
  surveillance. A later Charizard encounter triggers black-ops arrival only
  after it is scanned. The friendly gym entrance attendants are program staff;
  no attendant is introduced in the lab opening.
- A farewell walk through town follows the ceremony. Mom offers shoes/map and
  sincerely celebrates the program. Edwulf's parents are more reserved, hinting
  that postponement is not theirs to decide. Astrid and Edwulf are already gone
  when either house is visited. Neville can still be found packing.
- The old man's optional monologue recalls a lock and a prayer against dangers
  outside, contrasting this with everybody leaving doors wide open now. Avoid
  an explicit early explanation of government repression.

## What this version implements

The playable unit runs from New Game to crossing the Route 1 boundary. Its
scope is documented in PLAYTEST.md. The full mechanics design is not yet all
implemented. Approved character designs are now integrated as native walking sprites and
battle portraits. Existing Emerald tiles and title artwork remain in use.

Town and next-town names remain undecided; the build uses HOMETOWN and
“the next town.” Additional gyms, routes and story arcs are outside this unit.


Opening revision v0.3 (2026-10-20)
-----------------------------------
The saved v0.2 source was restored after the temporary workspace reset. The
recovered local Git history starts with that snapshot. The GitHub backup adds
the completed tree on leg-one with the original poc-demo commit as parent.
The approved character references and nine-frame overworld sheets were recovered
and converted with dev_scripts/convert_character_assets.py. The lab is now a
17x18 room with a five-ball counter and a separate practice floor.
Scene stages: 0=initial, 1=opening, 2=walk to table, 5=inspect choices,
3=selection/rival choreography/practice battle, 4=completed lab.
The practice-only whiteout exception permits Neville to continue after the
player's Pokémon faints; regular partner battles keep upstream behavior.
The script generator is the source of truth; edit dialogue.json and
build_leg_one.py, then regenerate. Do not replace the board-approved text
with an earlier draft.
