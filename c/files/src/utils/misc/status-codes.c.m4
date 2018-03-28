m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_CURRENT_YEAR_M4', `m4_esyscmd(echo -n $(date +"%Y"))')m4_dnl
m4_define(`M4_PROJECT_DESCRIPTION_M4`, `m4_esyscmd(echo -n $(curl https://api.github.com/users/`'M4_GITHUB_USER_NAME_M4`'/repos | jq '[] | select(.name == "`'M4_LPROJECT_NAME_M4`'") | .description')m4_dnl
/*******************************************************************************

Copyright (C) `'M4_CURRENT_YEAR_M4`', Ryan E. McClue

utils/misc/status-codes.c: 
	"Status codes to be used by `'M4_UPROJECT_NAME_M4`' functions."

`'M4_UPROJECT_NAME_M4`':
	"`'M4_PROJECT_DESCRIPTION_M4`'"

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/

#include "utils/misc/status-codes.h"

#include <stdbool.h>

#define EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODE_MAP_AS_CASE(status_code, str) \
	case status_code: return str; 	
const char[static 1] `'M4_LPROJECT_NAME_M4`'_status_code_str(const `'M4_LPROJECT_NAME_M4`'_status_code_t status_code)
{
	switch (status_code) {
		`'M4_UPROJECT_NAME_M4`'_STATUS_CODE_MAP(EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODE_MAP_AS_CASE)				
	}		
	
	return "unknown status code";
}
#undef EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODE_MAP_AS_CASE

#define EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODE_MAP_AS_CASE(status_code, str) \
	case status_code: return #status_code; 	
const char[static 1] `'M4_LPROJECT_NAME_M4`'_status_code_name(const `'M4_LPROJECT_NAME_M4`'_status_code_t status_code)
{
	switch (status_code) {
		`'M4_UPROJECT_NAME_M4`'_STATUS_CODE_MAP(EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODE_MAP_AS_CASE)				
	}		
	
	return "unknown status code";
}
#undef EXPAND_`'M4_UPROJECT_NAME_M4`'_STATUS_CODE_MAP_AS_CASE
