#define GAME_ASSERT(cond, msg) \
	if ((!cond)) { GAME_LOG_FATAL(msg); GAME_BREAKPOINT(); }

// .h
typedef enum  {
	LOG_INFO, 
	LOG_WARN, 
	LOG_FATAL,
	LOG__NUM_LOG_TYPES
} GAME_LOG_TYPES;

// need to include __VA_ARGS__ to support strerror(errno) for system errors
void game__log_log(
	GAME_LOG_TYPES log_level, 
	const char* restrict file_name, 
	const char* restrict function_name, 
	const int line_number, 
	const char restrict *message
);

void game__log_init_debug_logging(void);
void game__log_init_release_logging(void);

#if defined(DEBUG_BUILD)
#define GAME_LOG_INFO(msg) \
	game__log_log((GAME_LOG_LEVEL)LOG_INFO,  __FILE__, __func__, __LINE__, msg)
#define GAME_LOG_WARN(msg) \
	game__log_log((GAME_LOG_LEVEL)LOG_WARN,  __FILE__, __func__, __LINE__, msg)
#define GAME_LOG_FATAL(msg) \
	game__log_log((GAME_LOG_LEVEL)LOG_FATAL, __FILE__, __func__, __LINE__, msg)
#elif
#define GAME_LOG_INFO(msg)
#define GAME_LOG_WARN(msg)
#define GAME_LOG_FATAL(msg)
#endif

// .c


GAME_INTERNAL struct {
	bool in_release_mode;	
	const char* level_names[LOG__NUM_LOG_LEVELS];
	const char* level_colours[LOG__NUM_LOG_LEVELS] 
} __log = {
	.in_release_mode = false,	
	.level_names = {"INFO", "WARN", "FATAL"},
	.level_colours = {}
};
	#define ANSI_COLOUR_CLEAR = "\x1b[0m";
	#define ANSI_COLOUR_GREEN = "\x1b[32m";
	#define ANSI_COLOUR_YELLOW = "\x1b[33m";
	#define ANSI_COLOUR_ORANGE = "\x1b[35m"; 
	#define ANSI_COLOUR_RED = "\x1b[31m"; 

inline void game__log_set_release_mode(void) 
{
	__log.in_release_mode = true; 
}

inline void game__log_set_debug_mode(void) 
{
	__log.in_release_mode = false;
}

void game__log_log(
	GAME_LOG_LEVEL log_level, 
	const char* restrict file_name, 
	const char* restrict function_name, 
	const int line_number, 
	const char restrict *message
)
{
	GAME_LOCAL_PERSIST const size_t TIME_STRING_BUF_SIZE = 32;

	time_t current_time = time(NULL);	
	struct tm* local_time = localtime(&current_time);

	char time_string_buf[TIME_STRING_BUF_SIZE] = GAME_DEFAULT_INITIALISER;

	size_t time_string_length = strftime(time_string_buf, sizeof(time_string_buf), "%H:%M:%S", local_time); 
	time_string_buf[time_string_length] = '\0';

	/* Log to file */
	if (__log.in_release_mode) {
			
	} else {
		

	fprintf(stderr, "[GAME LOG ${NAME}] %-8s %s%-5sANSI_COLOUR_CLEAR %s:%s:%s ", 
		time_string_buf, log_colours[log_level], log_level_names[log_level],
		file_name, function_name, line_number);
	fprintf(stderr, "\n");

	}
	
}

  if (L.fp) {
	FILE* game_log_file = fopen("game.log", "a");
	if (game_log_file != NULL) {
		switch (log_type) {
		
		}
		// write message()		
		// vfprintf()
	}
    char buf[32];
    buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';
    fprintf(L.fp, "%s %-5s %s:%d: ", buf, level_names[level], file, line);
    va_start(args, fmt);
    vfprintf(L.fp, fmt, args);
    va_end(args);
    fprintf(L.fp, "\n");
  }

  /* Release lock */
  unlock();
}


	
#endif

	// write message()
	// [date] (Status Code: code) file:func:line "message"
}
