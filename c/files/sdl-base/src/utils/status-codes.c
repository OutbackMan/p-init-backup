#include "utils/misc/status-codes.h"

#include <stdbool.h>

#define EXPAND_GAME_STATUS_CODE_MAP_AS_CASE(status_code, str) \
	case status_code: return str; 	
const char* game_status_code_str(const game_status_code_t status_code)
{
	switch (status_code) {
		GAME_STATUS_CODE_MAP(EXPAND_GAME_STATUS_CODE_MAP_AS_CASE)				
	}		
	
	return "unknown status code";
}
#undef EXPAND_GAME_STATUS_CODE_MAP_AS_CASE

#define EXPAND_GAME_STATUS_CODE_MAP_AS_CASE(status_code, str) \
	case status_code: return #status_code; 	
const char* game_status_code_name(const game_status_code_t status_code)
{
	switch (status_code) {
		GAME_STATUS_CODE_MAP(EXPAND_GAME_STATUS_CODE_MAP_AS_CASE)				
	}		
	
	return "unknown status code";
}
#undef EXPAND_GAME_STATUS_CODE_MAP_AS_CASE
