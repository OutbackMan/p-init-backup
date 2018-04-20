#ifndef __utils_misc_status_codes_h__
#define __utils_misc_status_codes_h__

#include <stdint.h>

#define GAME_STATUS_CODES_MAP(X-ENTRY) \
	X-ENTRY(SUCCESS, "generic game success") \
	X-ENTRY(ERROR, "generic game error")
	X-ENTRY(ENOMEM, "not enough memory") \
	X-ENTRY(EARGINVAL, "invalid arguments") \

typedef struct {
	#define EXPAND_GAME_STATUS_CODES_AS_SIZE_STRUCT(status_code, _) \
		uint8_t GAME_##status_code;
	
	GAME_STATUS_CODES_MAP(EXPAND_GAME_STATUS_CODES_AS_SIZE_STRUCT)

	#undef EXPAND_GAME_STATUS_CODES_AS_SIZE_STRUCT
} game_status_code_length_t;

enum {
	#define EXPAND_GAME_STATUS_CODES_AS_ENUM(status_code, _) \
		GAME_##status_code;
	
	GAME_STATUS_CODES_MAP(EXPAND_GAME_STATUS_CODES_AS_ENUM)

	#undef EXPAND_GAME_STATUS_CODES_AS_ENUM
};

const char* game_status_code_str(const int status_code);
const char* game_status_code_name(const int status_code);

#endif
