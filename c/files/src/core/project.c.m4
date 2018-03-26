m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_DATE_M4', `m4_esyscmd(echo -n $(date +"%B %d, %Y (%Z)"))')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
/*******************************************************************************

Name: core/`'M4_LPROJECT_NAME_M4`'.c	Date of Creation: M4_DATE_M4

Maintainer: M4_GIT_USER_NAME_M4 <`'M4_GIT_USER_EMAIL_M4`'>

Developer Notes:


Credits:


*******************************************************************************/

#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-common.h"
#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-status-codes.h"
#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-args.h"
#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-log.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[argc + 1])
{
	int __leave_status_code = `'M4_UPROJECT_NAME_M4`'__ENTERED;

	`'M4_UPROJECT_NAME_M4`'_Args args = `'M4_LPROJECT_NAME_M4`'_default_args;

	`'M4_LPROJECT_NAME_M4`'_handle_args(&args, argc, argv);

	if (args.want_verbose) {
		`'M4_UPROJECT_NAME_M4`'_LOG_INFO("Welcome to `'M4_LPROJECT_NAME_M4`'!\n`'M4_PROJECT_DESCRIPTION_M4`'")
	} else {
		`'M4_UPROJECT_NAME_M4`'_LOG_INFO("Welcome to `'M4_LPROJECT_NAME_M4`'")
	}
		
	`'M4_UPROJECT_NAME_M4`'_LEAVE(EXIT_SUCCESS);

	__leave:
		return __leave_status_code; 
}
