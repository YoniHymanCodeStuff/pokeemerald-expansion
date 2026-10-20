# Dark Region project — recovery starting point

This branch contains the complete current game source, approved character art,
playable v0.3 package, narrative handoff, mechanics specification and development
notes. It is a backup of the work through October 20, 2026.

Read [Recovery status](RECOVERY-STATUS.md) first, then read in this order:

1. [Development handoff](DEVELOPMENT-HANDOFF.md): current implementation,
   recovery/build instructions, verification, limitations and next work.
2. [Current decisions](PROJECT-NOTES.md): character names, government structure,
   starter pool, relationships and decisions newer than the story bible.
3. [Narrative handoff](Narrative-Handoff-v0.2.txt): full story and branching design.
4. [Mechanics handoff](Mechanics-Handoff-v0.1.txt): complete intended QoL/rules.
   This is a specification, not a list of finished features.
5. [Approved opening dialogue](Leg-One-Dialogue.txt): current intro and town text.
6. [Playtest instructions](PLAYTEST.md) and [test results](TEST-RESULTS.md).

The editable dialogue source is `data/our-game/dialogue.json`.
The map/event generator is `dev_scripts/build_leg_one.py`.
The latest approved dialogue and explicit later user decisions override older
handoff passages. Do not restore discarded conversations with Astrid or Edwulf
at home: they have already left when the player visits those houses.

The playable ZIP is split into two lossless parts with reassembly instructions under `releases/leg-one-v0.3/`. Start a NEW GAME.
Continue development on `leg-one`; the repository default branch is still
`master`. The original `poc-demo` branch remains untouched.
