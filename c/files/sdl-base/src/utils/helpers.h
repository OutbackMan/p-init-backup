#define GAME_ASSERT(cond, msg) \
	if ((!cond)) { GAME_LOG_FATAL(msg); GAME_BREAKPOINT(); }

// .h
typedef enum  {
	LOG_INFO, 
	LOG_WARN, 
	LOG_FATAL,
	LOG__NUM_LOG_TYPES
} GAME_LOG_TYPE;

typedef enum {
	LOG_DEBUG,
	LOG_RELEASE
} GAME_LOG_MODES;

// need to include __VA_ARGS__ to support strerror(errno) for system errors
void game__log_log(
	GAME_LOG_TYPES log_level, 
	const char* restrict file_name, 
	const char* restrict function_name, 
	const int line_number, 
	const char restrict *message_fmt, ...
);

void game__log_init_debug_logging(void);
void game__log_init_release_logging(void);

#define GAME_LOG_INFO(msg, ...) \
	game__log_log((GAME_LOG_TYPE)LOG_INFO,  __FILE__, __func__, __LINE__, msg, __VA_ARGS__)
#define GAME_LOG_WARN(msg, ...) \
	game__log_log((GAME_LOG_TYPE)LOG_WARN,  __FILE__, __func__, __LINE__, msg, __VA_ARGS__)
#define GAME_LOG_FATAL(msg, ...) \
	game__log_log((GAME_LOG_TYPE)LOG_FATAL, __FILE__, __func__, __LINE__, msg, __VA_ARGS__)

// .c
GAME_INTERNAL struct {
	bool in_release_mode;	
	const char* level_names[LOG__NUM_LOG_LEVELS];
	const char* level_colours[LOG__NUM_LOG_LEVELS];
	FILE* log_file;
	lock_function
} __log = {
	.in_release_mode = false,	
	.level_names = {"INFO", "WARN", "FATAL"},
	.level_colours = {},
	.log_file = NULL,
	.lock_function = NULL
};
	// put inside ansi-colour-defs.h
	#define ANSI_COLOUR_CLEAR = "\x1b[0m";
	#define ANSI_COLOUR_GREEN = "\x1b[32m";
	#define ANSI_COLOUR_YELLOW = "\x1b[33m";
	#define ANSI_COLOUR_ORANGE = "\x1b[35m"; 
	#define ANSI_COLOUR_RED = "\x1b[31m"; 

GAME_INTERNAL void log_acquire_lock(void)
{
	if (__log.lock_function != NULL) {
		__log.lock_function();		
	}
}

GAME_INTERNAL void log_release_lock(void)
{
	if (__log.lock_function != NULL) {
		__log.lock_function();		
	}
}

void game__log_set_log_file(FILE* log_file)
{
	__log.log_file = log_file;	
}

void game__log_set_lock_function()
{
	
}

void game__log_init(GAME_LOG_MODE log_mode, FILE* log_file, lock_function)
{
	if (log_mode == LOG_DEBUG) {
		__log.in_release_mode = false; 	
	} else {
		__log.in_release_mode = true; 	
	}
	
	__log.lock_function = lock_function;
	__log.log_file = log_file;
}

void game__log_log(
	GAME_LOG_LEVEL log_level, 
	const char* restrict file_name, 
	const char* restrict function_name, 
	const int line_number, 
	const char* restrict message_fmt, ...
)
{
	if (__log.in_release_mode && log_type != LOG_FATAL) {
		return;		
	}

	log_acquire_lock();

	time_t current_time = time(NULL);	
	struct tm* local_time = localtime(&current_time);

	GAME_LOCAL_PERSIST const size_t TIME_STRING_BUF_SIZE = 32;
	char time_string_buf[TIME_STRING_BUF_SIZE] = GAME_DEFAULT_INITIALISER;

	GAME_LOCAL_PERSIST const char* TIME_FORMAT_STR = "%H:%M:%S";
	size_t time_string_length = strftime(
									time_string_buf,
									sizeof(time_string_buf), 
									TIME_FORMAT_STR, 
									local_time
								); 
	time_string_buf[time_string_length] = '\0';
	
	va_list args = GAME_DEFAULT_INITIALISER;

	if (__log.log_file != NULL) {
		fprintf(
			__log.log_file, 
			"%s %-5s %s:%s:%d ", 
			time_string_buf, 
			__log.type_names[log_type], 
			file_name, 
			function_name, 
			line_number
		);
		va_start(args, message_fmt);
		vfprintf(__log.log_file, message_format, args);
		va_end(args);
		fprintf(__log.log_file, "\n");
	} else {
		fprintf(
			stderr, 
			"%-8s %s%-5sANSI_COLOUR_CLEAR ANSI_COLOUR_GREY%s:%s:%sANSI_COLOUR_CLEAR ", 
			time_string_buf, 
			__log.type_colours[log_type], 
			__log.type_names[log_type], 
			file_name, 
			function_name, 
			line_number
		);
		va_start(args, message_fmt);
		vfprintf(stderr, message_fmt, args);
		va_end(args);
		fprintf(stderr, "\n");
	}

	log_release_lock();
}
