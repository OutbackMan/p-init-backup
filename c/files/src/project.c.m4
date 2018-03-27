m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_DATE_M4', `m4_esyscmd(echo -n $(date +"%B %d, %Y (%Z)"))')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
m4_define(`M4_PROJECT_DESCRIPTION_M4`, `m4_esyscmd(echo -n $(curl https://api.github.com/users/`'M4_GITHUB_USER_NAME_M4`'/repos | jq '[] | select(.name == "`'M4_LPROJECT_NAME_M4`'") | .description')m4_dnl
/*******************************************************************************

Copyright (C) 2018, `'M4_GIT_USER_NAME_M4`' <`'M4_GIT_USER_EMAIL_M4`'>

src/`'M4_LPROJECT_NAME_M4`'.c: 
	"`'M4_UPROJECT_NAME_M4`' entry point."

`'M4_UPROJECT_NAME_M4`':
	"`'M4_PROJECT_DESCRIPTION_M4`'"

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/

#include "utils/misc/common.h"
#include "utils/misc/status-codes.h"
#include "utils/misc/args.h"
#include "utils/misc/logger.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[argc + 1])
{
	`'M4_UPROJECT_NAME_M4`'_Args args = `'M4_LPROJECT_NAME_M4`'_default_args;

	`'M4_LPROJECT_NAME_M4`'_parse_args(&args, argc, argv);

	if (args.want_verbose) {
		`'M4_UPROJECT_NAME_M4`'_LOG_INFO("Welcome to `'M4_LPROJECT_NAME_M4`'!\n`'M4_PROJECT_DESCRIPTION_M4`'")
	} else {
		`'M4_UPROJECT_NAME_M4`'_LOG_INFO("Welcome to `'M4_LPROJECT_NAME_M4`'")
	}
		
	return EXIT_SUCCESS;
}
