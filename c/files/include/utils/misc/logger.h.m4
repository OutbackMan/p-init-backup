m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_CURRENT_YEAR_M4', `m4_esyscmd(echo -n $(date +"%Y"))')m4_dnl
m4_define(`M4_PROJECT_DESCRIPTION_M4`, `m4_esyscmd(echo -n $(curl https://api.github.com/users/`'M4_GITHUB_USER_NAME_M4`'/repos | jq '[] | select(.name == "`'M4_LPROJECT_NAME_M4`'") | .description')m4_dnl
/*******************************************************************************

Copyright (C) `'M4_CURRENT_YEAR_M4`', Ryan E. McClue

utils/misc/logger.h: 
	"Basic logging functionality to be used throughout `'M4_UPROJECT_NAME_M4`'."

`'M4_UPROJECT_NAME_M4`':
	"`'M4_PROJECT_DESCRIPTION_M4`'"

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/

#ifndef __utils_misc_logging_h__
#define __utils_misc_logging_h__

#include "utils/misc/config.h"

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
