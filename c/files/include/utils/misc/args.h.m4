m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4',`m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
m4_define(`GITHUB_USER_NAME', `m4_esyscmd(echo -n $(cat ~/.working-with))')m4_dnl
m4_define(`GITHUB_USER_API_URL', `https://api.github.com/users`'GITHUB_USER_NAME`'/repos')m4_dnl
m4_define(`M4_PROJECT_DESCRIPTION_M4', `m4_esyscmd(echo -n $(curl `'GITHUB_USER_API_URL`' | jq '[] | select(.name == `'M4_LPROJECT_NAME_M4`') | .description')m4_dnl
/*******************************************************************************

utils/misc/args.h: 
	Handle command line argument parsing.

`'M4_UPROJECT_NAME_M4`':
	`'M4_PROJECT_DESCRIPTION_M4`'

Copyright (C) 2018, `'M4_GIT_USER_NAME_M4`' <`'M4_GIT_USER_EMAIL_M4`'>

License:
	This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package.

*******************************************************************************/

#ifndef __utils_misc_args_h__
#define __utils_misc_args_h__

typedef struct {
	bool want_verbose;
} `'M4_UPROJECT_NAME_M4`'_Args;

extern const `'M4_UPROJECT_NAME_M4`'_Args `'M4_LPROJECT_NAME_M4`'_default_args; 

void `'M4_LPROJECT_NAME_M4`'_parse_args(`'M4_UPROJECT_NAME_M4`'_Args args, int argc, char* argv[argc + 1]);

#endif
