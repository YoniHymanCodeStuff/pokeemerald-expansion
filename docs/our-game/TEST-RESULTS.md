# Leg one v0.3 validation — 2026-10-20

ROM SHA-256: `98e2d5530e749a1c7231a31780e5858a750e511347d1879938aa614346fad3f5`.

- Full Emerald build passes. ROM 79.86%, EWRAM 86.56%, IWRAM 86.60%.
- Nine content checks pass: assignments, reverse warp destinations, layout
  sizes and NPC positions, departed classmates, text references, approved text,
  individual ball selection, two-storey home/parent names, native art formats.
- All five physical starter choices were replayed in mGBA 0.10.2 from a
  fresh New Game and a same-build table checkpoint. Each preview identifies the correct species;
  declining leaves all five balls available;
  rivals complete their collection walks; exactly one ball remains; player
  (5,12), Neville (5,14), Astrid (11,12), Edwulf (11,14) face their opponents.
  See tests/leg-one/qa_opening.py and the attached starter-results.json.
- Custom trainer front portraits and Neville's partner back portrait display
  in an actual doubles battle. All four custom overworld actors display.
- Faint regression: set the player's active HP to 1 and temporarily increased
  Neville's HP for observation. The player's Pokémon fainted normally; battle
  outcome stayed 0, Neville remained on screen, continued taking turns and
  damage, and the battle ended only after his Pokémon also fainted. No battle
  outcome was injected for this test. Defeat feedback and handover completed.
- Win feedback was separately exercised by reducing opposing active HP to 1
  and winning through normal attacks. Yew walks into view before feedback
  in both outcome branches. These battle checks preceded the final purely
  visual ball-height and exit-tile fixes.
- Fresh final-build Deerling playthrough completed the battle, briefing,
  handover and rival departures, then walked out of the lab into town.
- Balls visibly rest on the counter; chosen balls disappear immediately.
  Dialogue pages and successive speakers display without old text underneath.
- Entered the new player home, completed Mom's supply conversation and gifts,
  climbed the stairs and inspected the bedroom with its bed.
- Used the game's SAVE menu in the upstairs room; waited for save completion,
  exported a populated 128 KiB battery save, reset, selected CONTINUE, and
  returned to upstairs (7,2), lab stage 4 and farewell flag 1.

The remaining optional conversations and parent placement were structurally
checked and compiled. This revision does not implement the entire future QoL
settings specification. Begin a NEW GAME when upgrading from v0.2.

Source restoration note: v0.2 was recovered from its saved source archive after
a temporary workspace reset. Local Git records the recovered base and these
changes; this revision has not been pushed to GitHub.
