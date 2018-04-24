#if GAME_BUILD_MODE_DEBUG
#define GAME_BREAKPOINT raise(SIGABRT);
#else
#define GAME_BREAKPOINT
#endif

#define GAME_ASSERT(cond, msg) \
	if ((!cond)) { GAME_LOG(msg); GAME_BREAKPOINT; }

#define GAME_LOG(type, msg) \
	game_log(type, msg, __FILE__, __func__, __LINE__, __VA_ARGS__)

void game_log(
	game_log_type_t log_type,
	const char* restrict file_name,
	const char* restrict function_name,
	const int line_number,
	const char* restrict msg,
	...
)
{
// have init_logging(log_level), i.e. static struct
#if defined(GAME_BUILD_MODE_RELEASE)
	FILE* game_log_file = fopen("game.log", "a");
	if (game_log_file != NULL) {
		switch (log_type) {
		
		}
		// write message()		
		// vfprintf()
	}
	
#endif

	// write message()
	// [date] (Status Code: code) file:func:line "message"
}

	#define ANSI_COLOUR_CLEAR = "\x1b[0m";
	#define ANSI_COLOUR_GREEN = "\x1b[32m";
	#define ANSI_COLOUR_YELLOW = "\x1b[33m";
	#define ANSI_COLOUR_ORANGE = "\x1b[35m"; 
	#define ANSI_COLOUR_RED = "\x1b[31m"; 

	static const char* restrict log_colours[GAME_LOG__MAX] = {
		[GAME_LOG_INFO] = ANSI_COLOUR_GREEN,
		[GAME_LOG_WARN] = ANSI_COLOUR_YELLOW,
		[GAME_LOG_ERROR] = ANSI_COLOUR_ORANGE,
		[GAME_LOG_FATAL] = ANSI_COLOUR_RED
	};

	static const char* restrict log_level_names[GAME_LOG__MAX] = {
		[GAME_LOG_INFO] = "INFO",
		[GAME_LOG_WARN] = "WARN",
		[GAME_LOG_ERROR] = "ERROR",
		[GAME_LOG_FATAL] = "FATAL"
	};

	time_t current_time = time(NULL);	
	struct tm* local_time = localtime(&current_time);

	char time_string_buf[32] = {0};

	size_t time_string_length = strftime(time_string_buf, sizeof(time_string_buf), "%H:%M:%S", local_time); 
	time_string_buf[time_string_length] = '\0';

	fprintf(stderr, "[GAME] %-8s %s%-5sANSI_COLOUR_CLEAR %s:%s:%s ", 
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

#if GAME_BUILD_MODE == GAME_BUILD_DEBUG_MODE
#define SYS_ERROR_MSG() \
	perror("System error incurred: "GAME_STRINGIFY(__FILE__)":"\
		GAME_STRINGIFY(__func__)":"GAME_STRINGIFY(__LINE__));
#else
#define SYS_ERROR_MSG() \
	fprintf(LOG_FILE, "System error incurred: "GAME_STRINGIFY(__FILE__)":"\
		GAME_STRINGIFY(__func__)":"GAME_STRINGIFY(__LINE__)". %s\n", strerror(errno));
#endif

enum {
	GAME_LOG_INFO,
	GAME_LOG_WARN,
	GAME_LOG_ERROR,
	GAME_LOG_FATAL,
	GAME_LOG__MAX
};

#if defined(GAME_DEBUG_MODE) || defined(GAME_LOGGING_MODE) 
#define GAME_LOG_INFO(...) \
	game_log_log(GAME_LOG_INFO, __FILE__, __func__, __LINE__, __VA_ARGS__); 
#define GAME_LOG_WARN(...) \
	game_log_log(GAME_LOG_WARN, __FILE__, __func__, __LINE__, __VA_ARGS__); 
#define GAME_LOG_ERROR(...) \
	game_log_log(GAME_LOG_ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__); 
#define GAME_LOG_FATAL(...) \
	game_log_log(GAME_LOG_FATAL, __FILE__, __func__, __LINE__, __VA_ARGS__); 

void game_log_set_level(const int log_level);
void game_log_log(const int log_level, const char file_name[restrict static 1],
		const char function_name[restrict static 1], 
		const int line_number,
		const char format_string[restrict static 1]);

#endif
