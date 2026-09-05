# Stage-1 bootstrap

Smallest godot that can translate `game.gen.elf` into
`game.gen.cpp` via godot-sandbox's `emit_binary_translation`. This
godot never ships to players.

## Build

From the godot source root (`entities-godot-sandbox/`):

    scons profile=modules/game/bootstrap/custom.py \
          platform=$(uname | tr A-Z a-z) \
          target=editor \
          -j$(nproc)

Only `sandbox`, `game`, `gdscript`, `text_server_fb`, and `svg`
modules stay enabled. Every other stock module is disabled;
`tools=no`, `disable_3d=yes`, `disable_advanced_gui=yes`,
`optimize=size`. Build time is minutes, not tens of minutes.

## Use

    export GODOT_BINTR=$PWD/bin/godot.linuxbsd.editor.x86_64
    scons -j$(nproc)   # stage 2 — game module SCsub picks up GODOT_BINTR
                       # and translates ELFs into real gen.cpp before
                       # linking the shipping godot binary.

The stage-2 build sees the translated C source and links it in
place of the interpretation-fallback stub. Result: one shipping
godot binary that runs game logic at native speed.

## Why two stages

`Sandbox::emit_binary_translation` is a Godot class method — it
needs a working Godot to call. Stage 1 provides that Godot. The
alternative (a standalone `libriscv-tr` tool linked against
libriscv only) would work but drops the `Sandbox` project settings
that `emit_binary_translation` reads (nbit-as, register-caching).
The two-stage shape keeps those knobs.
