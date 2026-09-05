#include "game.h"

void Game::_bind_methods() {
	ADD_SIGNAL(MethodInfo("decision_point",
			PropertyInfo(Variant::ARRAY, "legal_moves")));
	ADD_SIGNAL(MethodInfo("move_outcome",
			PropertyInfo(Variant::STRING_NAME, "outcome")));
}

void Game::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_READY: {
		} break;
		case NOTIFICATION_EXIT_TREE: {
		} break;
	}
}
