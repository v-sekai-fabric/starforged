#include "register_types.h"

#include <cstddef>
#include <cstdint>

// Symbols filled in by game.gen.cpp (generated from game.gen.elf,
// generated from game.gd). Everything ships inside the godot binary;
// no external .elf on disk, no external .gd on disk. Model weights
// are fetched from a CDN (huggingface) at runtime — data only, not
// code.
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
