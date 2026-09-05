extends Node
class_name Game

# Root node for the Starforged decision-point VN (RFD 1175).
#
# Compiled to a RISC-V ELF via godot-sandbox's native-compile toolchain
# rather than shipped as a C++ Godot module: sandbox lets us keep the
# game logic in GDScript, iterate at editor speed, and still get native
# perf where the sandbox JIT/AOT wants it. Same shape godot-vrm uses.

signal decision_point(legal_moves: Array)
signal move_outcome(outcome: StringName)


func _ready() -> void:
	pass


func _exit_tree() -> void:
	pass
