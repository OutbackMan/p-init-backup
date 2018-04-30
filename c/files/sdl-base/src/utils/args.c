typedef enum {
	ARG_INT,
	ARG_STR,
	ARG_BOOL
} GAME_ARG_TYPE;

typedef struct {
	GAME_ARG_TYPE arg_type;
	char option_char;
	union {
		int default_value;
		const char* default_value;
		bool default_value;
	}
	const char* help_message;
} GAME__ArgInstance;

typedef struct {
	size_t length;
	GAME__ArgInstance arg_help;
	GAME__ArgInstance arg_version;
} GAME_ArgTable;

#define GAME_ARG_TABLE_ITERATE(arg_index, arg) \
	for ( \
			size_t arg_index = 1; \
			GAME__ArgInstance arg = game_args_arg_table[arg_index]; \
			arg_index < arg_table.length; \
			++arg_index \
		)

GAME_ArgTable game_args_arg_table = {
	.length = 4,
	.arg_help = {
		.type = ARG_BOOL,
		.option_char = 'H',
		.default_value = false,
		.help_message = "Display this help and exit"
	},
	.arg_version = {
		.type = ARG_BOOL,
		.option_char = 'V',
		.default_value = false,
		.help_message = "Display version information and exit"
	},
	.save_file = {
		.type = ARG_STR,
		.option_char = 'S',
		.default_value = GAME_LNAME".sav",
		.help_message = "Specify location of save file"
	},
	.game_width = {
		.type = ARG_INT,
		.option_char = 'W',
		.default_value = 640,
		.help_message = "Specify width of "GAME_LNAME" screen in pixels"
	},
	.game_height = {
		.type = ARG_INT,
		.option_char = 'H',
		.default_value = 480,
		.help_message = "Specify height of "GAME_LNAME" screen in pixels"
	}
};

void game_args_print_syntax(FILE* output_stream)
{
	// calloc() takes sizeof(space) to zero, so consider using malloc if speed is a consideration
	GAME_ASSERT(output_stream != NULL, "msg");

	char arg_syntax_buf[512] = "Usage: "GAME_BINARY_STRING" ";

	GAME_ARG_TABLE_ITERATE(_, arg) {
		char arg_option_char_buf[32] = GAME_DEFAULT_INITIALISER;	

		snprintf(arg_option_char_buf, sizeof(arg_option_char_buf), "[-%c%s] ", arg.option_char, game_args__get_arg_type_string(arg.type));

		strcat(arg_syntax_buf, arg_option_char_buf);
	}	

	fprintf(output_stream, "%s\n", arg_syntax_buf);
}

static const char* game_args__get_arg_type_string(GAME_ARG_TYPE arg_type)
{
	GAME_ASSERT(arg != NULL, "msg");

	if (arg_type == ARG_BOOL) {
		return "";
	} else if (arg_type == ARG_INT) {
		return "<int>"; 	
	} else {
		return "<string>";
	}
}

void game_args_print_glossary(FILE* output_stream)
{
	GAME_ASSERT(output_stream != NULL, "msg");

	for (size_t arg_index = 1; arg_index < game_args_default_arg_table.length; ++arg_index) {
		fprintf(
			output_stream, 
			"%-25s %s.\n", 
			game_args_default_arg_table[arg_index].option_char,
			game_args_default_arg_table[arg_index].help_message
		);
	}
}


int game_args_handle(int argc, char* argv[argc + 1])
{
#if defined(_WIN32)
	const char ARG_START = '\\';
#else
	const char ARG_START = '-';
#endif

	for (size_t arg_index = 1; arg_index < argc && argv[arg_index][0] == ARG_START; ++arg_index) {
		for (char* arg_char = argv[arg_index] + 1; *arg_char != '\0'; ++arg_char) {
			GAME_ARG_TABLE_ITERATE(arg_index, arg) {
				if (*arg_char == arg.option_char) {
					game_args__parse_arg(&args);	
				} else {
					fprintf(stderr, "Illegal option %c\n", *arg_char);
					fprintf(stderr, "Try '%s -H' for more information.\n", GAME_BINARY_STRING);
					argc = -1; // or return;
				}
			}	
		}
	}

	// have to handle args like help outside function to faciliate memory cleanup
		// perform		
		// logic		
		// perform any actions, e.g. print help
}

int handle_int_arg(int* int_arg, int int_arg_min_value, int int_arg_max_value, char* arg_char)
{
	// for arguments that cannot be null, use asserts to invoke undefined behaviour and to keep user honest
	GAME_ASSERT(arg_char != NULL, "msg");

	// we specifically handle the argument values that we document the function supports
	if (min_int_value > max_int_value) {
		max_int_value = min_int_value;		
	}

	while (isdigit(*arg_char)) {
		*int_arg *= 10;
		*int_arg += *arg_char - '0';
		++arg_char;
	}	
	
	if (*int_arg < min_int_value || *int_arg > max_int_value) {
		printf("GAME: invalid option %s. Try running PROG -H for more information\n");
		return EARG_INVAL;
	} else {
		return SUCCESS;		
	}
}

int handle_str_arg(const char* str_arg, size_t str_arg_max_length, char* arg_char)
{
	GAME_ASSERT(arg_char != NULL, "msg");

	const char* str_arg_start = arg_char;
	size_t str_arg_length = 0;

	while (isalnum(*arg_char) || *arg_char == '_') {
		++arg_char;
		++str_arg_length;
	}	
		
	str_arg = calloc(sizeof(char), str_arg_length + 1);
	if (str_arg == NULL) {
		// perror()
		return ENO_MEM;		
	}

	strncpy(str_arg, str_arg_start, str_arg_length);
	str_arg[str_arg_length] = '\0';

	return SUCCESS;
}
