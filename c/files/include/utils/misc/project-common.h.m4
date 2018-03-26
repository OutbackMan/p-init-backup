m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_DATE_M4', `m4_esyscmd(echo -n $(date +"%B %d, %Y (%Z)"))')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
/*******************************************************************************

Name: utils/misc/`'M4_LPROJECT_NAME_M4`'-common.h	Date of Creation: M4_DATE_M4 

Maintainer: M4_GIT_USER_NAME_M4 <`'M4_GIT_USER_EMAIL_M4`'>

Developer Notes: 


*******************************************************************************/

#ifndef __utils_misc_`'M4_LPROJECT_NAME_M4`'_common_h__
#define __utils_misc_`'M4_LPROJECT_NAME_M4`'_common_h__

#include "utils/misc/`'M4_LPROJECT_NAME_M4`'-log.h"

#include <signal.h>

#if defined(`'M4_UPROJECT_NAME_M4`'_DEBUG_MODE)
#define `'M4_UPROJECT_NAME_M4`'_ASSERT(cond, msg) \
	if (!(cond)) { \
		`'M4_UPROJECT_NAME_M4`'_LOG_FATAL(msg) \
		raise(SIGABRT); \
	} 
#else
#define `'M4_UPROJECT_NAME_M4`'_ASSERT(cond)
#endif

#define PROJECT_CLEANUP(func)	\
	__attribute__((cleanup(func)))	

#define PROJECT_DEFINE_CLEANUP_FUNC(type, func)	\
	static inline void __#func(type* p)	\
	{	\
		if (p != NULL) {	\
			func(p);	\
		}	\
	}

#define max(a, b)	\
	({	\
	__auto_type_ _a = (a);	\
	__auto_type_ _b = (b);	\
	(void) (&_a == &_b);	\
	(_a > _b ? _a : _b);	\
	})	

#define PROJECT_PURE         __attribute__((pure))
#define PROJECT_CONST        __attribute__((const))
#define PROJECT_COLD     __attribute__((cold))
#define PROJECT_HOT     __attribute__((hot))
#define PROJECT_CHECK __attribute__((warn_unused_result))
#define PROJECT_DEPRECATED   __attribute__((deprecated))
#define PROJECT_USED         __attribute__((used))
#define PROJECT_UNUSED       __attribute__((unused))
#define PROJECT_PACKED       __attribute__((packed))
#define PROJECT_LIKELY(x)    __builtin_expect(!!(x), 1) // only use if 99% sure on outcome
#define PROJECT_UNLIKELY(x)  __builtin_expect(!!(x), 0)
#define PROJECT_DESIGNATED __attribute__((designated_init))
#define PROJECT_FLATTEN __attribute__((flatten))

#define tostring(s) #s
#define stringify(s) tostring(s)

#endif

#endif
