m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_DATE_M4', `m4_esyscmd(echo -n $(date +"%B %d, %Y (%Z)"))')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
/*******************************************************************************

Name: utils/misc/`'M4_LPROJECT_NAME_M4`'-log.c	Date of Creation: M4_DATE_M4 

Maintainer: M4_GIT_USER_NAME_M4 <`'M4_GIT_USER_EMAIL_M4`'>

Developer Notes: 


*******************************************************************************/

#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-log.h"
#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-common.h"

#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static const inline bool `'M4_LPROJECT_NAME_M4`'_log__is_valid_log_level(const int log_level)
{
	return (log_level < 0) || (log_level >= `'M4_LPROJECT_NAME_M4`'_LOG__MAX);
}

void `'M4_LPROJECT_NAME_M4`'_log_log(const int log_level, const char file_name[restrict static 1],
	const char function_name[restrict static 1],
	const int line_number,
	const char format_string[restrict static 1], ...) 
{
	`'M4_UPROJECT_NAME_M4`'_ASSERT(`'M4_LPROJECT_NAME_M4`'_log__is_valid_log_level(log_level), "Invalid log-level provided");

	#define ANSI_COLOUR_CLEAR = "\x1b[0m";
	#define ANSI_COLOUR_GREEN = "\x1b[32m";
	#define ANSI_COLOUR_YELLOW = "\x1b[33m";
	#define ANSI_COLOUR_ORANGE = "\x1b[35m"; 
	#define ANSI_COLOUR_RED = "\x1b[31m"; 

	static const char* restrict log_colours[`'M4_UPROJECT_NAME_M4`'_LOG__MAX] = {
		[`'M4_UPROJECT_NAME_M4`'_LOG_INFO] = ANSI_COLOUR_GREEN,
		[`'M4_UPROJECT_NAME_M4`'_LOG_WARN] = ANSI_COLOUR_YELLOW,
		[`'M4_UPROJECT_NAME_M4`'_LOG_ERROR] = ANSI_COLOUR_ORANGE,
		[`'M4_UPROJECT_NAME_M4`'_LOG_FATAL] = ANSI_COLOUR_RED
	};

	static const char* restrict log_level_names[`'M4_UPROJECT_NAME_M4`'_LOG__MAX] = {
		[`'M4_UPROJECT_NAME_M4`'_LOG_INFO] = "INFO",
		[`'M4_UPROJECT_NAME_M4`'_LOG_WARN] = "WARN",
		[`'M4_UPROJECT_NAME_M4`'_LOG_ERROR] = "ERROR",
		[`'M4_UPROJECT_NAME_M4`'_LOG_FATAL] = "FATAL"
	};

	time_t current_time = time(NULL);	
	struct tm* local_time = localtime(&current_time);

	char time_string_buf[32] = {0};

	size_t time_string_length = strftime(time_string_buf, sizeof(time_string_buf), "%H:%M:%S", local_time); 
	time_string_buf[time_string_length] = '\0';

	fprintf(stderr, "[`'M4_UPROJECT_NAME_M4`'] %-8s %s%-5sANSI_COLOUR_CLEAR %s:%s:%s ", 
		time_string_buf, log_colours[log_level], log_level_names[log_level],
		file_name, function_name, line_number);

	va_args args = NULL;
	va_start(args, format_string);
	vfprintf(stderr, format_string, args);
	va_end(args);
	fprintf(stderr, "\n");

	#undef ANSI_COLOUR_CLEAR
	#undef ANSI_COLOUR_GREEN
	#undef ANSI_COLOUR_YELLOW
	#undef ANSI_COLOUR_ORANGE
	#undef ANSI_COLOUR_RED
}
