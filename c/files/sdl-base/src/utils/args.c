enum {
	AGE_ARG,
	NAME_ARG,
	HELP_ARG
};

typedef struct {
	arg_type_t arg_type;
	union {
		int arg_int_value;
		const char* arg_str_value;
		bool arg_bool_value;
	}
	const char* arg_help_message;
} GameArg;

typedef struct {
	size_t num_args;
	GameArg* args;
} GameArgs;

int create_int_arg(GameArg* arg, int value, const char* msg)
{
	GAME_ASSERT(arg != NULL, "msg");

	arg->arg_type = ARG_INT;
	arg->arg_value = value;

	arg->arg_help_message = calloc(sizeof(char), strlen(msg));
	if (arg->arg_help_message == NULL) {
		SYS_ERROR_MSG()
		return FAILURE;		
	}
	strcpy(arg->arg_help_message, msg);

	return SUCCESS;
}

int game__create_default_args(GameArgs* game_args)
{
	GAME_ASSERT(game_args != NULL);

	int leave_code = DEFAULT_INITIALISER;

	const size_t NUM_ARGUMENTS = 5;
	game_args->num_args = NUM_ARGUMENTS;

	game_args->args = calloc(sizeof(GameArgs), NUM_ARGUMENTS);
	if (game_args->args == NULL) {
		GAME_LEAVE(FAILURE);	
	}
		
	int arg_status = DEFAULT_INITIALISER;
	// alternative looping as this will affect base pointer
	if ( (arg_status = create_arg(++game_args->args, type, value, help)) != SUCCESS ) {
		GAME_LEAVE(FAILURE);		
	}

	GAME_LEAVE(SUCCESS);
	
	__leave:
		if (arg_status == SUCCESS) destroy_arg(arg);
		if (game_args != NULL) free(game_args);
		return leave_code;
}

void game__destroy_default_args(GameArgs* game_args)
{
	GAME_ASSERT(game_args != NULL, "msg");

	for (size_t arg_index = 0; arg_index < game_args->num_args; ++arg_index) {
		destroy_arg(&game_args[arg_index]);
	}

	destroy_args(game_args);
}

int game__parse_args(GameArgs* game_args, int argc, char* argv[argc + 1])
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
					// Usage: game.exe [-H] [-Sstring] [-I80]
					// game description
					// -H display this help and exit	
					args_print_syntax(stdout, argument_list); 
					puts("program description");
					args_print_glossary(argument_list);
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

int main(int argc, char** argv)
{
	int leave_code = DEFAULT_INITIALISER;

	GameArgs game_args = DEFAULT_INTIALISER;
	if (game__handle_args(&game_args, argc, argv) != SUCCESS) {
		GAME_LEAVE(FAILURE);		
	}

	// accessed through
	game_args.age 


	game__free_args(&game_args);

	return 0;	
}
