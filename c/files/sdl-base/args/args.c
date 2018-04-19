typedef enum {
	ARG_INT,
	ARG_REAL,
	ARG_FILE,
	ARG_STRING
} arg_type_t;

typedef struct {
	arg_type_t arg_type;	
	const char* short_arg;
	const char* long_arg;	
	/* assume only 1
	unsigned min_occurence_count;
	unsigned max_occurence_count;
	*/
	const char* help_message;
	union {
		intmax_t int_value;
		long double real_value;
		const char* str_value;
		const char* file_value;
	}
	size_t arg_count;
} ArgOption;

int arg__create_int_option()
{
	arg_option->arg_type = ARG_INT;

	if (short_arg != NULL) {
		arg_option->short_arg = calloc(sizeof(char), 1);
		if (arg_option->short_arg == NULL) {
			return FAILURE;		
		}
		strncpy(arg_option->short_arg, short_arg, 1);
	} else {
		arg_option->short_arg = NULL;
	}
		
	if (long_arg != NULL) {
		size_t long_arg_length = strlen(long_arg);
		arg_option->long_arg = calloc(sizeof(char), long_arg_length);
		if (arg_option->long_arg == NULL) {
			return FAILURE;		
		}
		strncpy(arg_option->long_arg, long_arg, long_arg_length);
	} else {
		arg_option->long_arg = NULL;
	}
			
	arg_option->min_occurence_count = min_occurence_count;
	arg_option->max_occurence_count = max_occurence_count;

	size_t help_message_length = strlen(help_message);
	arg_option->help_message = calloc(sizeof(char), help_message_length);
	if (arg_option->help_message == NULL) {
		return FAILURE;		
	}
	strncpy(arg_option->help_message, help_message, help_message_length);

	arg_option->int_value = 0;
	arg_option->arg_count = 0;

	return SUCCESS;
}

int arg_create_option(ArgOption* arg_option, arg_type_t arg_type, )
{
	/*
	if (min_occurence_count > max_occurence_count) {
		max_occurence_count = min_occurence_count;
	}
	*/
		
	switch (arg_type_t) {
	case ARG_INT:
		arg__create_int_option();	
		break;
	case ARG_REAL:
		break;
	case ARG_FILE:
		arg__create_int_option();	
		break;
	case ARG_STRING:
		
		break;
	default:
		break;
	};

	return SUCCESS;
}

int getopt()
{
	//  -W300
	while (--argc > 0 && (*++argv)[0] == '-') {
		for (char* s = argv[0] + 1; *s != '\0'; ++s) {
			switch (*s) {
			case 'W':
				int val = 0;
				while (isalnum(s)) {
					val *= 10;
					val += *s++ - '0';
				}	
			}		
		}
	}
	
}

// argp

// option = getopt("a:") --> optarg, optind, (opterror, optopt)
int args_parse_options(int argc, char* argv[argc + 1], size_t num_options, ArgOptions options[num_options])
{
	// parse short
}

int main(int argc, char** argv)
{
	// arg_parse_tagged/untaggged/check

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
