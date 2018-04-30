typedef enum {
	ARG_INT,
	ARG_STR,
	ARG_BOOL
} GAME_ARG_TYPE;

typedef struct {
	GAME_ARG_TYPE arg_type;
	union {
		int arg_int_value;
		const char* arg_str_value;
		bool arg_bool_value;
	}
	const char* arg_help_message;
} GAME__ArgInstance;

typedef struct {
	GAME__ArgInstance arg_help;
	GAME__ArgInstance arg_version;
} GAME_ArgTable;

GAME_ArgTable game_arg_table_default_arg_table = {
	.arg_help = {
		.arg_type = ARG_BOOL,
		.arg_bool_value = false,
		.arg_help_message = "Display this help message and quit."
	},
	.arg_version = {
		.arg_type = ARG_BOOL,
		.arg_bool_value = false,
		.arg_help_message = "Display version."
	},
	.save_file = {
		
	}
};

void game_args_print_syntax(void)
{
	fprintf(stderr, "Usage: %s [-H] [-V]\n", GAME_BINARY_STRING);
}

void game_args_print_glossary(void)
{
	fprintf(stderr, "-H display this help and exit.");
}


int game_args_handle(GAME_ArgTable* arg_table, int argc, char* argv[argc + 1])
{
	GAME_ASSERT(arg_table != NULL, "msg");
	
#if defined(_WIN32)
	const char ARG_START = '\\';
#else
	const char ARG_START = '-';
#endif

	for (size_t arg_index = 1; arg_index < argc && argv[arg_index][0] == ARG_START; ++arg_index) {
		for (char* arg_char = argv[arg_index] + 1; *arg_char != '\0'; ++arg_char) {
			switch (*arg_char) {
			case 'H':	
				arg_table->arg_help.value = true;
				break;
			case 'V':
				arg_table->arg_version.value = true;
				break;
			default:
				fprintf(stderr, "Illegal option %c\n", *arg_char);
				argc = -1;
				break;
			}		
		}
	}

	if (argc == -1) {
		// usage ...
		return;
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
