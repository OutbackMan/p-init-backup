#ifndef __utils_status_codes_h__
#define __utils_status_codes_h__

#define GAME_STATUS_CODES_MAP(X-ENTRY) \
	X-ENTRY(SUCCESS, "generic game success") \
	X-ENTRY(FAILURE, "generic game failure") \
	X-ENTRY(FNOMEM, "not enough memory") \
	X-ENTRY(FARGINVAL, "invalid arguments") \

enum {
	#define EXPAND_GAME_STATUS_CODES_AS_ENUM(status_code, _) \
		GAME_##status_code;
	
	GAME_STATUS_CODES_MAP(EXPAND_GAME_STATUS_CODES_AS_ENUM)

	#undef EXPAND_GAME_STATUS_CODES_AS_ENUM
};

typedef int game_status_t;

const char* game_status_code_str(const game_status_t status_code);
const char* game_status_code_name(const game_status_t status_code);

#endif
