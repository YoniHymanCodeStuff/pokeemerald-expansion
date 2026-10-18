# Pokémon Region Demo — v0.1

Based on RHH pokeemerald-expansion **1.17.1**, tag commit
`bb1093a7c72d3961d9a37d8e02ad2abc2c866682`.

## Play

Open `pokemon-region-demo-v0.1.gba` in a GBA emulator. Start a **new game**.
For a quick start, press START to skip the opening movie, then press SELECT on
the title screen. This uses a default player name and takes you straight into
the demo. Alternatively, press START on the title screen, choose NEW GAME, and
complete the existing character/name introduction. The adventure starts in
**Demo Village**, with no moving-truck or Hoenn opening sequence.

1. Talk to the professor directly north of your starting point. Accept Sprigatito
   (level 8), 10 Poké Balls, five Potions, and the National Pokédex.
2. Enter the house to heal for free. Hold B to run.
3. Walk north to Demo Trail. Catch newer Pokémon in the grass patches beside the path.
4. Talk to the scout blocking the narrow tree passage. Win the battle.
5. Read the sign beyond the opened gate to complete the demo.
6. Save using START → SAVE, restart the emulator, and press START on the title screen and select CONTINUE (do not use SELECT).
   Confirm your party and bag remain, and the gate stays open.

The starter is given once. Entering the trail without it returns you to the village.
Losing a battle returns you to Demo Village with your party healed; retry the scout.

## Scope

These are new maps and scripts using the engine's existing tilesets and sprites.
All names and dialogue are placeholders. This is a technical proof of concept,
not the opening of the final story. Emerald's title screen and character introduction
remain for now. Existing Hoenn maps remain in the source but are not connected to
these demo maps. Building art reuses an Emerald house and its interior.

## Build

Follow the upstream `INSTALL.md` for your OS, then run:

```sh
make -j8
```

The output is `pokeemerald.gba`. No modifications to your Windows setup are needed
to play the supplied build. Use this demo's save only with compatible demo builds;
compatibility with vanilla Emerald or unrelated hacks is not supported.

## Credits

Based off RHH's pokeemerald-expansion 1.17.1:
https://github.com/rh-hideout/pokeemerald-expansion/
See `CREDITS.md` for upstream contributors and asset credits.
