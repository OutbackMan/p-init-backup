m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_CURRENT_YEAR_M4', `m4_esyscmd(echo -n $(date +"%Y"))')m4_dnl
m4_define(`M4_PROJECT_DESCRIPTION_M4`, `m4_esyscmd(echo -n $(curl https://api.github.com/users/`'M4_GITHUB_USER_NAME_M4`'/repos | jq '[] | select(.name == "`'M4_LPROJECT_NAME_M4`'") | .description')m4_dnl
/*******************************************************************************

Copyright (C) `'M4_CURRENT_YEAR_M4`', Ryan E. McClue

utils/misc/status-codes.h: 
	"Status codes to be used by`'M4_UPROJECT_NAME_M4`' functions."

`'M4_UPROJECT_NAME_M4`':
	"`'M4_PROJECT_DESCRIPTION_M4`'"

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/

#ifndef __utils_misc_status_codes_h__
#define __utils_misc_status_codes_h__

#include <stdint.h>

#define `'M4_UPROJECT_NAME_M4`'_STATUS_CODES_MAP(X-ENTRY) \
	X-ENTRY(SUCCESS, "generic `'M4_LPROJECT_NAME_M4`' success") \
	X-ENTRY(ERROR, "generic `'M4_LPROJECT_NAME_M4`' error")
	X-ENTRY(ENOMEM, "not enough memory") \
	X-ENTRY(EARGINVAL, "invalid arguments") \

typedef struct {
	#define EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODES_AS_SIZE_STRUCT(status_code, _) \
		uint8_t `'M4_UPROJECT_NAME_M4`'_##status_code;
	
	`'M4_UPROJECT_NAME_M4`'_STATUS_CODES_MAP(EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODES_AS_SIZE_STRUCT)

	#undef EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODES_AS_SIZE_STRUCT
} `'M4_LPROJECT_NAME_M4`'_status_code_length_t;

enum {
	#define EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODES_AS_ENUM(status_code, _) \
		`'M4_UPROJECT_NAME_M4`'_##status_code;
	
	`'M4_UPROJECT_NAME_M4`'_STATUS_CODES_MAP(EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODES_AS_ENUM)

	#undef EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODES_AS_ENUM
};

const char[static 1] `'M4_LPROJECT_NAME_M4`'_status_code_str(const int status_code);
const char[static 1] `'M4_LPROJECT_NAME_M4`'_status_code_name(const int status_code);

#endif
