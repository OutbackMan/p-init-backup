m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_CURRENT_YEAR_M4', `m4_esyscmd(echo -n $(date +"%Y"))')m4_dnl
m4_define(`M4_PROJECT_DESCRIPTION_M4`, `m4_esyscmd(echo -n $(curl https://api.github.com/users/`'M4_GITHUB_USER_NAME_M4`'/repos | jq '[] | select(.name == "`'M4_LPROJECT_NAME_M4`'") | .description')m4_dnl
/*******************************************************************************

Copyright (C) `'M4_CURRENT_YEAR_M4`', Ryan E. McClue

utils/misc/args.c: 
	"Command line argument handling."

`'M4_UPROJECT_NAME_M4`':
	"`'M4_PROJECT_DESCRIPTION_M4`'"

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/
#include "utils/misc/args.h"
#include "utils/misc/config.h"
#include "utils/misc/common.h"

#include "argtable3/argtable3.h"

#include <stddef.h>
#include <stdbool.h>

const `'M4_UPROJECT_NAME_M4`'_Args `'M4_UPROJECT_NAME_M4`'_default_args = {
	.want_verbose = false,	
};

void `'M4_LPROJECT_NAME_M4`'_args_handle_args(`'M4_UPROJECT_NAME_M4`'_Args args, int argc, char* argv[argc + 1])
{ 
	const static size_t ERROR_BUF_SIZE = 20;

	struct arg_lit* help_arg = arg_litn("h", "help", 0, 1, "Display this help output and exit");
	struct arg_lit* version_arg = arg_litn("V", "version", 0, 1, `'M4_UPROJECT_NAME_M4`'_VERSION);
	struct arg_lit* verbose_arg = arg_litn("v", "verbose", 0, 1, "Make `'M4_LPROJECT_NAME_M4`' provide more detailed output");
	struct arg_end* end_arg = arg_end(ERROR_BUF_SIZE);

	void* argtable[] = {help_arg, version_arg, verbose_arg, end_arg};

	size_t num_errors = arg_parse(argc, argv, argtable);

	// Printing help takes precedence over error handling.
	if (help_arg->count > 0) {
		printf("Usage: `'M4_LPROJECT_NAME_M4`'");
		arg_print_syntax(stdout, argtable, "\n");
		printf("`'M4_PROJECT_DESCRIPTION_M4`'\n");
		arg_print_glossary(stdout, argtable, "%-25s %s\n");
		`'M4_UPROJECT_NAME_M4`'_LEAVE();
	}

	if (num_errors > 0) {
		arg_print_errors(stderr, end_arg, PROGRAM_NAME);
		fprintf(stderr, "Try `'M4_LPROJECT_NAME_M4`' --help for more information\n");
		`'M4_UPROJECT_NAME_M4`'_LEAVE();
	}

	if (verbose_arg->count > 0) {
		args.want_verbose = true;				
	}

	`'M4_UPROJECT_NAME_M4`'_LEAVE();
	
	_leave:
		arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));
		return; 
}
