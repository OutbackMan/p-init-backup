m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_DATE_M4', `m4_esyscmd(echo -n $(date +"%B %d, %Y (%Z)"))')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
m4_define(`M4_PROJECT_DESCRIPTION_M4`, `m4_esyscmd(echo -n $(curl https://api.github.com/users/`'M4_GITHUB_USER_NAME_M4`'/repos | jq '[] | select(.name == "`'M4_LPROJECT_NAME_M4`'") | .description')m4_dnl
/*******************************************************************************

Copyright (C) 2018, `'M4_GIT_USER_NAME_M4`' <`'M4_GIT_USER_EMAIL_M4`'>

utils/misc/common.h: 
	"Common macro definitions."

`'M4_UPROJECT_NAME_M4`':
	"`'M4_PROJECT_DESCRIPTION_M4`'"

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/

#ifndef __utils_misc_common_h__
#define __utils_misc_common_h__

#include "utils/misc/config.h"
#include "utils/misc/logger.h"

#include <signal.h>

#define `'M4_UPROJECT_NAME_M4`'_TOSTRING(value) #value
#define `'M4_UPROJECT_NAME_M4`'_STRINGIFY(value) `'M4_UPROJECT_NAME_M4`'_TOSTRING(value)

#if defined(`'M4_UPROJECT_NAME_M4`'_DEBUG_MODE)
#define `'M4_UPROJECT_NAME_M4`'_ASSERT(cond, msg) \
	if (!(cond)) { \
		`'M4_UPROJECT_NAME_M4`'_LOG_FATAL(msg) \
		raise(SIGABRT); \
	} 
#else
#define `'M4_UPROJECT_NAME_M4`'_ASSERT(cond)
#endif

#define `'M4_UPROJECT_NAME_M4`'_CLEANUP(func)	\
	__attribute__((cleanup(func)))	

#define `'M4_UPROJECT_NAME_M4`'_DEFINE_CLEANUP_FUNC(type, func)	\
	static inline void __#func(type* p)	\
	{	\
		if (p != NULL) {	\
			func(p);	\
		}	\
	}

#define `'M4_UPROJECT_NAME_M4`'_PURE __attribute__((pure))
#define `'M4_UPROJECT_NAME_M4`'_CONST __attribute__((const))
#define `'M4_UPROJECT_NAME_M4`'_COLD __attribute__((cold))
#define `'M4_UPROJECT_NAME_M4`'_HOT __attribute__((hot))
#define `'M4_UPROJECT_NAME_M4`'_CHECK __attribute__((warn_unused_result))
#define `'M4_UPROJECT_NAME_M4`'_DEPRECATED __attribute__((deprecated))
#define `'M4_UPROJECT_NAME_M4`'_USED __attribute__((used))
#define `'M4_UPROJECT_NAME_M4`'_UNUSED __attribute__((unused))
#define `'M4_UPROJECT_NAME_M4`'_PACKED __attribute__((packed))
#define `'M4_UPROJECT_NAME_M4`'_LIKELY(value) __builtin_expect(!!(value), 1)
#define `'M4_UPROJECT_NAME_M4`'_UNLIKELY(value) __builtin_expect(!!(value), 0)
#define `'M4_UPROJECT_NAME_M4`'_DESIGNATED __attribute__((designated_init))
#define `'M4_UPROJECT_NAME_M4`'_FLATTEN __attribute__((flatten))

#define max(a, b)	\
	({	\
	__auto_type_ _a = (a);	\
	__auto_type_ _b = (b);	\
	(void) (&_a == &_b);	\
	(_a > _b ? _a : _b);	\
	})	

#endif
