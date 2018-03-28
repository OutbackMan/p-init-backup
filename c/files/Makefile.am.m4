AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/lib

bin_PROGRAMS = `'M4_LPROJECT_NAME_M4`' 

`'M4_LPROJECT_NAME_M4`'_SOURCES = $(top_srcdir)/src/core/`'M4_LPROJECT_NAME_M4`'.c \
								$(top_srcdir)/include/utils/misc/config.h \
								$(top_srcdir)/include/utils/misc/common.h \
								$(top_srcdir)/src/utils/misc/status-codes.c \
								$(top_srcdir)/include/utils/misc/status-codes.h \
								$(top_srcdir)/src/utils/misc/logger.c \
								$(top_srcdir)/include/utils/misc/logger.h \
								$(top_srcdir)/src/utils/misc/args.c \
								$(top_srcdir)/include/utils/misc/args.h

`'M4_LPROJECT_NAME_M4`'_CPPFLAGS = @CPPFLAGS@
`'M4_LPROJECT_NAME_M4`'_CFLAGS = @CFLAGS@
`'M4_LPROJECT_NAME_M4`'_LDFLAGS = @LIBS@

# Add tests
TESTS = 
check_PROGRAMS = tests/
