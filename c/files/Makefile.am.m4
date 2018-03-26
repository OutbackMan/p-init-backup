AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/lib

bin_PROGRAMS = `'M4_LPROJECT_NAME_M4`' 

`'M4_LPROJECT_NAME_M4`'_SOURCES = $(top_srcdir)/src/core/`'M4_LPROJECT_NAME_M4`'.c \
								$(top_srcdir)/include/utils/misc/`'M4_LPROJECT_NAME_M4`'-common.h \
								$(top_srcdir)/src/utils/misc/`'M4_LPROJECT_NAME_M4`'-status-codes.c \
								$(top_srcdir)/include/utils/misc/`'M4_LPROJECT_NAME_M4`'-status-codes.h \
								$(top_srcdir)/src/utils/misc/`'M4_LPROJECT_NAME_M4`'-log.c \
								$(top_srcdir)/include/utils/misc/`'M4_LPROJECT_NAME_M4`'-log.h \
								$(top_srcdir)/src/utils/misc/`'M4_LPROJECT_NAME_M4`'-args.c \
								$(top_srcdir)/include/utils/misc/`'M4_LPROJECT_NAME_M4`'-args.h

`'M4_LPROJECT_NAME_M4`'_CPPFLAGS = @CPPFLAGS@
`'M4_LPROJECT_NAME_M4`'_CFLAGS = @CFLAGS@
`'M4_LPROJECT_NAME_M4`'_LDFLAGS = @LIBS@

TESTS = 
check_PROGRAMS = tests/
