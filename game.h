#ifndef GAME_H
#define GAME_H

#include "scene/main/node.h"

// Game — root node for the Starforged decision-point VN.
//
// Design in README.md (from RFD 1175):
//   - Native window, VRM portrait framed like a video call
//   - Taskweft planner supplies legal moves at each decision point
//   - Outcome fires a VRM expression blendshape (~1.6 s envelope)
//   - Motion-bricks (ggml/Vulkan) generates body motion between decisions
//   - Same binary --headless --write-movie captures the video head
//
// The scaffolding here registers Game as a Node subclass and exposes a
// signal for decision-point events; the loop wiring lives in a scene
// (.tscn) using this node as the root, plus per-model GDScript adapters.
class Game : public Node {
	GDCLASS(Game, Node);

protected:
	static void _bind_methods();

	void _notification(int p_what);

public:
	// Emitted when the planner has surfaced a new set of legal moves.
	// Payload: Array of move descriptors (planner-defined).
	//
	// Emitted when a move outcome is resolved (strong-hit / weak-hit / miss).
	// Payload: StringName outcome.
	//
	// Wired up in the .tscn; the C++ side just declares the surface.

	Game() {}
	~Game() {}
};

#endif // GAME_H
