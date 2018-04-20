// default_arguments
typedef struct {
	int width;
	const char* name;
	FILE* config;	
} GameArgs;

// init args
// free args

int game__parse_args(GameArgs* game_args, int argc, char* argv[argc + 1])
{
	int leave_code = 0;

#if defined(_WIN32)
	const char ARG_START = '\\';
#else
	const char ARG_START = '-';
#endif

	for (size_t arg_index = 1; arg_index < argc && argv[arg_index][0] == ARG_START; ++arg_index) {
		for (char* arg_char = argv[arg_index] + 1; *arg_char != '\0'; ++arg_char) {
			switch (*arg_char) {
			case 'W':	
				if (handle_int_arg(&(game_args->width), *arg_char, max, min) != SUCCESS) {
					GAME_LEAVE(FAILURE);
				}
				break;
			case 'H':
				handle_int_arg(*arg_char, max, min);
				break;
			default:

			}		
		}
	}
}

int handle_int_arg(int* int_arg, char* arg_char, int max_int_value, int min_int_value)
{
	// for arguments that cannot be null, use asserts to invoke undefined behaviour and to keep user honest
	GAME_ASSERT(int_arg != NULL, "msg");
	GAME_ASSERT(arg_char != NULL, "msg");

	// we specifically handle the argument values that we document the function supports
	if (min_int_value > max_int_value) {
		max_int_value = min_int_value;		
	}

	while (isdigit(arg_char)) {
		*int_arg *= 10;
		*int_arg += *arg_char++ - '0';
	}	
	
	if (*int_arg < min_int_value || *int_arg > max_int_value) {
		return EARG_INVAL;
	} else {
		return SUCCESS;		
	}
}

				int val = 0;
			case 'S':
			// start
				while (isalnum(s) || *s == '-') {
					++s;		
				}
			// end
		}
	}
}

int main(int argc, char** argv)
{
	const size_t NUM_ARGUMENTS = 1;

	ArgOption version = {0}; 

	if (arg_create_option(&version, ARG_INT, "v", "version", 0, 1, "display version information and exit") == FAILURE) {
		// handle error	
	}

	ArgOption argument_list[NUM_ARGUMENTS] = { version };

	// display errors
	args_parse_options(NUM_ARGUMENTS, argument_list);

	if (argument_list.version.count > 0) {
		args_print_syntax(stdout, argument_list);
		puts("program description");
		args_print_glossary(argument_list);
	}

	return 0;	
}
