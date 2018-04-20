int game__get_default_args(size_t game_args_num, GameArg* game_args)
{
	game_args = calloc(sizeof(GameArg), game_args_num);
	if (game_args == NULL) {
		return FAILURE;	
	}

				
}

enum {
	AGE_ARG,
	NAME_ARG,
	HELP_ARG
};

typedef struct {
	arg_type_t arg_type;
	const char* arg_help_message;
	union {
		int arg_int_value;
		const char* arg_str_value;
		bool arg_bool_value;
	}
} GameArg;

// init args
// free args

int game__parse_args(size_t game_args_num, GameArg game_args, int argc, char* argv[argc + 1])
{
	GAME_ASSERT(game_args != NULL, "msg");
	
	int leave_code = 0;

	
	if (game__get_default_args(game_args) != SUCCESS) {
		GAME_LEAVE(FAILURE);		
	}

#if defined(_WIN32)
	const char ARG_START = '\\';
#else
	const char ARG_START = '-';
#endif

	for (size_t arg_index = 1; arg_index < argc && argv[arg_index][0] == ARG_START; ++arg_index) {
		for (char* arg_char = argv[arg_index] + 1; *arg_char != '\0'; ++arg_char) {
			switch (*arg_char) {
			case 'I':	
				if (parse_int_arg(game_args[ARG_WIDTH], arg_char) != SUCCESS) {
					GAME_LEAVE(FAILURE);
				}
				break;
			case 'S':
				if (parse_str_arg(game_args->name, arg_char, 40) != SUCCESS) {
					GAME_LEAVE(FAILURE);		
				}
				break;
			case 'H':
				if (parse_bool_arg()) {
					if (++arg_char != '\0') // error 
				}
				break;
			default:

			}		
		}
	}
	// display errors
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

int main(int argc, char** argv)
{
	int leave_code = 0;

	GameArgs game_args = {0};
	if (game__parse_args(&game_args, argc, argv) != SUCCESS) {
		GAME_LEAVE(FAILURE);		
	}

	if (game_args.width ) {
		args_print_syntax(stdout, argument_list);
		puts("program description");
		args_print_glossary(argument_list);
	}

	game__free_args(&game_args);

	return 0;	
}
