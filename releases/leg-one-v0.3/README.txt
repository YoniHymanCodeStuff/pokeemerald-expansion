POKEMON: LEG ONE — PLAYTEST v0.3

Open pokemon-leg-one-v0.3.gba in your GBA emulator. Start NEW GAME.
Older saves and emulator states can retain the old maps, positions and stages.
A = interact/confirm; directional buttons = move; START = menu; hold B to run
once Mom gives you the Running Shoes.

FIXES IN THIS REVISION
1. New dialogue messages clear the previous text.
2. Custom Yew, Astrid, Edwulf and Neville walking sprites and battle portraits;
   Neville also has his own partner battle back sprite.
3. Everyone faces Yew; Neville turns toward you to whisper. Balls sit on a counter.
4. You regain control when called forward. Walk to the table, then inspect each
   physical ball for a Pokemon sprite, description and Yes/No confirmation.
5. Rivals walk to their assigned choices. Each taken ball disappears immediately.
6. Your character also walks into position for the doubles battle.
7. Neville continues fighting when your Pokemon faints. Both allies must be out
   before your side loses this supervised match.
8. Yew enters the practice floor before giving feedback.
9. Yew retrieves the Pokedexes and walks between the children to distribute them.
10. Your home has two floors and an upstairs bedroom/bed. Mom's dialogue matches
    handing you the shoes and map.
11. Astrid's mom and Edwulf's mom are named explicitly. Edwulf's parents stand
    around the table in different positions rather than in a line.

This opening ends at the Route 1 boundary. The full future mechanics and later
chapters are still in development. See PLAYTEST.md and TEST-RESULTS.md.
Publication and recovery notes: docs/our-game/RECOVERY-STATUS.md.

GitHub recovery note (October 20, 2026):
The upload interface limits individual request sizes. The original ZIP is stored
losslessly as .part01 and .part02. Reassemble it before unzipping:

Linux/macOS:
cat Pokemon-Leg-One-v0.3.zip.part01 Pokemon-Leg-One-v0.3.zip.part02 > Pokemon-Leg-One-v0.3.zip

Windows Command Prompt:
copy /b Pokemon-Leg-One-v0.3.zip.part01+Pokemon-Leg-One-v0.3.zip.part02 Pokemon-Leg-One-v0.3.zip

Verify the resulting ZIP against SHA256SUMS.txt.
