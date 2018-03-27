m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_DATE_M4', `m4_esyscmd(echo -n $(date +"%B %d, %Y (%Z)"))')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
/*******************************************************************************

Name: utils/misc/`'M4_LPROJECT_NAME_M4`'-log.h	Date of Creation: M4_DATE_M4 

Maintainer: M4_GIT_USER_NAME_M4 <`'M4_GIT_USER_EMAIL_M4`'>

Developer Notes: 


*******************************************************************************/

#ifndef __utils_misc_`'M4_LPROJECT_NAME_M4`'_log_h__
#define __utils_misc_`'M4_LPROJECT_NAME_M4`'_log_h__

#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-config.h"

enum {
	`'M4_UPROJECT_NAME_M4`'_LOG_INFO,
	`'M4_UPROJECT_NAME_M4`'_LOG_WARN,
	`'M4_UPROJECT_NAME_M4`'_LOG_ERROR,
	`'M4_UPROJECT_NAME_M4`'_LOG_FATAL,
	`'M4_UPROJECT_NAME_M4`'_LOG__MAX
};

#if defined(`'M4_UPROJECT_NAME_M4`'_DEBUG_MODE) || defined(`'M4_UPROJECT_NAME_M4`'_LOGGING_MODE) 
#define `'M4_UPROJECT_NAME_M4`'_LOG_INFO(...) \
	`'M4_LPROJECT_NAME_M4`'_log_log(`'M4_UPROJECT_NAME_M4`'_LOG_INFO, __FILE__, __func__, __LINE__, __VA_ARGS__); 
#define `'M4_UPROJECT_NAME_M4`'_LOG_WARN(...) \
	`'M4_LPROJECT_NAME_M4`'_log_log(`'M4_UPROJECT_NAME_M4`'_LOG_WARN, __FILE__, __func__, __LINE__, __VA_ARGS__); 
#define `'M4_UPROJECT_NAME_M4`'_LOG_ERROR(...) \
	`'M4_LPROJECT_NAME_M4`'_log_log(`'M4_UPROJECT_NAME_M4`'_LOG_ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__); 
#define `'M4_UPROJECT_NAME_M4`'_LOG_FATAL(...) \
	`'M4_LPROJECT_NAME_M4`'_log_log(`'M4_UPROJECT_NAME_M4`'_LOG_FATAL, __FILE__, __func__, __LINE__, __VA_ARGS__); 

void `'M4_LPROJECT_NAME_M4`'_log_set_level(const int log_level);
void `'M4_LPROJECT_NAME_M4`'_log_log(const int log_level, const char file_name[restrict static 1],
		const char function_name[restrict static 1], 
		const int line_number,
		const char format_string[restrict static 1]);

#endif
