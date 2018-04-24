
#if GAME_BUILD_MODE_DEBUG
#define GAME_LOG(msg) \
	game_log(msg, __FILE__, __line__
#define GAME_BREAKPOINT raise(SIGABRT);
#else
#define GAME_BREAKPOINT
#endif

// game_log(msg)

#define GAME_ASSERT(cond, msg) \
	if ((!cond)) { GAME_LOG(msg); GAME_BREAKPOINT; }
