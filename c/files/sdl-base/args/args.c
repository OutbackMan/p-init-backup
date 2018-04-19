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
	unsigned min_occurence_count;
	unsigned max_occurence_count;
	const char* help_message;
	union {
		intmax_t int_value;
		long double real_value;
		const char* str_value;
		const char* file_value;
	}
	size_t arg_count;
} ArgOption;

int main(int argc, char** argv)
{
	const size_t NUM_ARGUMENTS = 1;

	ArgOption version = {0}; 

	if (arg_create_option(&version, ARG_INT, "v", "version", 0, 1, "display version information and exit") == FAILURE) {
		// handle error	
	}

	ArgOption argument_list[NUM_ARGUMENTS] = { version };

	// display errors
	args_parse_options(argument_list, NUM_ARGUMENTS);

	if (argument_list.version.count > 0) {
		args_print_syntax(stdout, argument_list);
		puts("program description");
		args_print_glossary(argument_list);
	}

	return 0;	
}
