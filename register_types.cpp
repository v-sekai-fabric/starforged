#include "register_types.h"

#include <cstddef>
#include <cstdint>

// Symbols filled in by game.gen.cpp. When SCsub ran godot-sandbox's
// bintr mode (emit_binary_translation), game.gen.cpp is native C
// source translated from game.gd's RISC-V ELF form — loaded via
// Sandbox::load_binary_translation at native speed. When the fallback
// path ran, game.gen.cpp holds the ELF as a byte array and libriscv
// interprets it. Either way the game logic ships inside the single
// godot binary; model weights (and any peer modules' compiled ELFs
// that don't ride in the binary) live in the release-side sqlar.
extern "C" const uint8_t game_gen_elf[];
extern "C" const size_t game_gen_elf_len;
extern "C" const uint8_t game_gen_elf[];
extern "C" const size_t game_gen_elf_len;

void initialize_game_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	// Hand `game_gen_elf` / `game_gen_elf_len` to the sandbox module.
	// The sandbox module owns the libriscv machine; this module just
	// declares which embedded program to boot.
	//
	// Wiring lands in a follow-up commit once the sandbox module's
	// "load embedded program" API is stable across versions we track.
}

void uninitialize_game_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
