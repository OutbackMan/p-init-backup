m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_DATE_M4', `m4_esyscmd(echo -n $(date +"%B %d, %Y (%Z)"))')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
/*******************************************************************************

Name: utils/misc/`'M4_LPROJECT_NAME_M4`'-status-codes.c	Date of Creation: M4_DATE_M4

Maintainer: M4_GIT_USER_NAME_M4 <`'M4_GIT_USER_EMAIL_M4`'>

Developer Notes:


Credits:


*******************************************************************************/

#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-status-codes.h"

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
