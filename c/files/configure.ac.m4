# Setup
AC_PREREQ([2.69])
AC_INIT([`'M4_LPROJECT_NAME_M4`', [0.0.1], [https://github.com/`'M4_GIT_USER_NAME_M4`'/`'M4_LPROJECT_NAME_M4`'/issues])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects 1.15])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([include/utils/misc/config.h])

# OS Specific Operations
AC_CANONICAL_HOST
AS_CASE([$host_os], [mingw*], [AC_DEFINE([`'M4_UPROJECT_NAME_M4`'_BINARY_NAME], ["`'M4_LPROJECT_NAME_M4`'.exe"], [])],
	[AC_DEFINE([`'M4_UPROJECT_NAME_M4`'_BINARY_NAME], ["./`'M4_LPROJECT_NAME_M4`'"], [])])

# Argument Handling
AC_ARG_ENABLE([release], [AS_HELP_STRING([--enable-release], [Configure `'M4_LPROJECT_NAME_M4`' to compile in release mode])],
	[], [AC_DEFINE([`'M4_UPROJECT_NAME_M4`'_DEBUG_MODE], [], [])])

AC_ARG_ENABLE([logging], [AS_HELP_STRING([--enable-logging], [Configure `'M4_LPROJECT_NAME_M4`' to compile with logging features])],
	[], [AC_DEFINE([`'M4_UPROJECT_NAME_M4`'_LOGGING_MODE], [], [])])

# Compiler Handling
AC_PROG_CC([gcc])

## Core Flags
AX_CHECK_COMPILE_FLAG([-std=gnu11], [AX_APPEND_FLAG([-std=gnu11])], [AC_MSG_WARN([-std=gnu11 flag wanted for `'M4_LPROJECT_NAME_M4`' core compilation, but it is not supported by the current gcc compiler.])])

AX_CHECK_COMPILE_FLAG([-Werror], [AX_APPEND_FLAG([-Werror])], [AC_MSG_WARN([-Werror flag wanted for `'M4_LPROJECT_NAME_M4`' core compilation, but it is not supported by the current gcc compiler.])])

AX_CHECK_COMPILE_FLAG([-Wall], [AX_APPEND_FLAG([-Wall])], [AC_MSG_WARN([-Wall flag wanted for `'M4_LPROJECT_NAME_M4`' core compilation, but it is not supported by the current gcc compiler.])])

AX_CHECK_COMPILE_FLAG([-Wextra], [AX_APPEND_FLAG([-Wextra])], [AC_MSG_WARN([-Wextra flag wanted for `'M4_LPROJECT_NAME_M4`' core compilation, but it is not supported by the current gcc compiler.])])

AX_CHECK_COMPILE_FLAG([-Wno-unused-parameter], [AX_APPEND_FLAG([-Wno-unused-parameter])], [AC_MSG_WARN([-Wno-unused-parameter flag wanted for `'M4_LPROJECT_NAME_M4`' core compilation, but it is not supported by the current gcc compiler.])])

AX_CHECK_COMPILE_FLAG([-Wstrict-prototypes], [AX_APPEND_FLAG([-Wstrict-prototypes])], [AC_MSG_WARN([-Wstrict-prototypes flag wanted for `'M4_LPROJECT_NAME_M4`' core compilation, but it is not supported by the current gcc compiler.])])

## Release and Debug Flags: 
AS_IF([test "x$enable_release" = xyes], 
	[AX_CHECK_COMPILE_FLAG([-O3], [AX_APPEND_FLAG([-O3])], [AC_MSG_WARN([-O3 flag wanted for `'M4_LPROJECT_NAME_M4`' release mode compilation, but it is not supported by current gcc compiler.])])], 
	[AX_CHECK_COMPILE_FLAG([-Og], [AX_APPEND_FLAG([-Og])], [AC_MSG_WARN([-Og flag wanted for `'M4_LPROJECT_NAME_M4`' debug mode compilation, but it is not supported by current gcc compiler.])])])

# Shared Library Checking

# 3rd Party Program Checking
AC_CHECK_PROGS([SPHINXBUILD], [sphinx-build sphinx-build2], [no])

# Output
AC_OUTPUT
