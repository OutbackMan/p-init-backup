#ifndef __utils_status_h__
#define __utils_status_h__

#define GAME_STATUS_MAP(X-ENTRY) \
	X-ENTRY(ENTERED, "entered function") \
	X-ENTRY(SUCCESS, "generic game success") \
	X-ENTRY(FAILURE, "generic game failure") \
	X-ENTRY(SDL_FAILURE, "generic sdl failure") \
	X-ENTRY(FNOMEM, "not enough memory") \
	X-ENTRY(FARGINVAL, "invalid arguments") \

typedef enum {
	#define EXPAND_GAME_STATUS_AS_ENUM(status, _) \
		status_code;
	
	GAME_STATUS_MAP(EXPAND_GAME_STATUS_AS_ENUM)

	#undef EXPAND_GAME_STATUS_AS_ENUM
} GAME_STATUS;

const char* game_status_str(GAME_STATUS status);
const char* game_status_name(GAME_STATUS status);

#endif
