# Stage-1 bootstrap: smallest godot that can run modules/game's bintr
# driver. Only the modules the translator needs are enabled; every
# other module is disabled to keep the build small and the compile
# fast. This godot never ships to players — it exists to translate
# RISC-V ELFs into native C source via godot-sandbox's
# emit_binary_translation. The stage-2 build embeds the translated
# C source and ships to players.
#
# Usage from the godot source root:
#
#   scons profile=modules/game/bootstrap/custom.py \
#         platform=<linuxbsd|windows|macos> \
#         target=editor \
#         tools=no dev_build=no
#
# Ship the resulting binary as $GODOT_BINTR, then run scons again
# with the default profile to build the game binary; the game
# module's SCsub will invoke $GODOT_BINTR to translate ELFs into
# real gen.cpp files.

# Only these modules stay enabled in stage 1 — everything else
# below flips off.
KEEP = {"sandbox", "game", "gdscript", "text_server_fb", "svg"}

# Godot's stock module set as of 4.7-beta. Anything not in KEEP
# gets module_<name>_enabled = "no".
STOCK_MODULES = [
    "astcenc", "basis_universal", "bcdec", "betsy", "bmp", "camera",
    "csg", "cvtt", "dds", "enet", "etcpak", "fbx", "freetype",
    "glslang", "gltf", "godot_physics_2d", "godot_physics_3d",
    "gridmap", "hdr", "interactive_music", "jolt_physics", "jpg",
    "jsonrpc", "ktx", "lightmapper_rd", "mbedtls", "meshoptimizer",
    "minimp3", "mobile_vr", "mono", "msdfgen", "multiplayer",
    "navigation", "noise", "ogg", "openxr", "opus", "raycast",
    "regex", "squish", "svg", "text_server_adv", "text_server_fb",
    "theora", "tga", "tinyexr", "upnp", "vhacd", "vorbis",
    "webp", "webrtc", "websocket", "webxr", "xatlas", "zip",
]

for m in STOCK_MODULES:
    if m not in KEEP:
        globals()["module_" + m + "_enabled"] = "no"

# Editor is not needed — headless is enough to run the bintr script.
tools = "no"

# Shave more surface: no 3D physics, no advanced text server, no
# extra shaders. The bintr driver is a pure headless script.
disable_3d = "yes"
disable_advanced_gui = "yes"
disable_navigation = "yes"

# Deterministic + small.
lto = "none"
optimize = "size"
debug_symbols = "no"
dev_build = "no"
production = "no"

# No accessibility, no touch, no advanced text — nothing the
# translator itself needs.
accessibility = "none"
