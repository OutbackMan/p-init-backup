#ifndef __utils_wrappers_sdl_log_h__
#define __utils_wrappers_sdl_log_h__

#include "common.h"

#include <SDL2/SDL.h>

void init_logging(void)
{
// check SDL_RWOps
#if defined(GAME_BUILD_MODE_DEBUG)
	SDL_LogSetAllPriority(SDL_LOG_CATEGORY_APPLICATION);
#else
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_CRITICAL);
	if (log_file != NULL) {
		SDL_LogSetOutputFunction(release_log, log_file);	
	} else {
		SDL_LogSetOutputFunction(no_log, log_file);	
	}
#endif
}

void file_log(void* log_file, int log_category, SDL_LogPriority log_priority, const char* log_message)
{
	FILE* log_file_handle = (FILE *)log_file;		

			
}

void no_log(void* log_file, int log_category, SDL_LogPriority log_priority, const char* log_message)
{
	return;	
}

// assert.[hc]
#include "common.h"
#include "utils/wrappers/sdl-log.h"

#if defined(GAME_BUILD_MODE_DEBUG)
// handle va_args
void assert(bool cond, const char* msg, ...)
{
	if (!cond) {
		SDL_LogCritical(SDL_LOG_CATEGORY_ASSERT, msg);
		raise(SIGABRT);
	} else {
		return;		
	}
}
#else
void assert(bool cond, const char* msg)
{
	return;
}

// game.log
//					GAME LOG
// Generated: date
// Please send any inquiries to <email> inluding related log snippet(s).

// [date] (Status Code: code) file:func:line "message"

// HOLD OFF UNTIL AWARE OF SDL_LOG FUNCTIONALITY (SDL_LogSetOutputFunction)
#if GAME_BUILD_MODE == GAME_BUILD_RELEASE_MODE
// open log file
int open_log_file(void) {
	
}
// log_file_routine

#if GAME_BUILD_MODE == GAME_BUILD_DEBUG_MODE
#define SYS_ERROR_MSG() \
	perror("System error incurred: "GAME_STRINGIFY(__FILE__)":"\
		GAME_STRINGIFY(__func__)":"GAME_STRINGIFY(__LINE__));
#else
#define SYS_ERROR_MSG() \
	fprintf(LOG_FILE, "System error incurred: "GAME_STRINGIFY(__FILE__)":"\
		GAME_STRINGIFY(__func__)":"GAME_STRINGIFY(__LINE__)". %s\n", strerror(errno));
#endif

#endif
