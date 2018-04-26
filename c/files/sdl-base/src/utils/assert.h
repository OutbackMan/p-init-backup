#define GAME_ASSERT(cond, msg) \
	if ((!cond)) { GAME_LOG_FATAL(msg); GAME_BREAKPOINT(); }
