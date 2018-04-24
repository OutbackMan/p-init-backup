#@ Author       "Ryan McClue" <mcclue.ryan@gmail.com>
#@ Description  Cross platform 2D SDL game.
#@ Usage: 
#@	 mkdir build/ && cd build/ && cmake .. 
#@   ctest <name>
#@   cpack <name>

################################################################################
# CMAKE CONFIGURATION                                                          #
################################################################################
cmake_minimum_required(3.0 FATAL_ERROR)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(WARNING "Prefer out-of-tree CMake builds.")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

project(name)
enable_language(C)

list(INSERT CMAKE_MODULE_PATH 0 "${name_SOURCE_DIR}/cmake/modules")

include(GameBuildTypes)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
	message(STATUS "Build type not specified, defaulting to Debug")
endif()

# set version via git
include(GameSetVersion)

# find_package
$ENV{MY_VAR} to the HINTS


set(CMAKE_C_FLAGS_DEBUG "-ggdb3 -g3 -O0")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -ffast-math -DNDEBUG -s -fmerge-all-constants")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O3 -ffast-math -DNDEBUG -ggdb3 -g3 -fmerge-all-constants")
set(CMAKE_C_FLAGS_RELEASE "-O3 -ffast-math -DNDEBUG -fmerge-all-constants")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")
set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-s")
if (GCC_VERSION VERSION_GREATER 4.6 OR GCC_VERSION VERSION_EQUAL 4.6)
    set(GCC_FLTO_FLAGS "-flto -fdata-sections -ffunction-sections")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${GCC_FLTO_FLAGS}")
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} ${GCC_FLTO_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,--gc-sections")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -Wl,--gc-sections")
  endif (GCC_VERSION VERSION_GREATER 4.6 OR GCC_VERSION VERSION_EQUAL 4.6)

  # Enable "unsafe" loop optimizations on recent versions.
  if (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -funsafe-loop-optimizations")
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -funsafe-loop-optimizations")
  endif (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)

  # Check for undefined behaviour when debugging.
  if (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=undefined")
  endif (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)

  # Use fat LTO objects.
  if (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffat-lto-objects")
  endif (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9)
endif (${CMAKE_C_COMPILER_ID} MATCHES GNU)

## COMPILER CONFIGURATION
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU|Clang")
	execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpmachine
		OUTPUT_VARIABLE NAME_ARCH
	)

	### GCC SPECIFIC
	if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	
	### CLANG SPECIFIC
	else ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	
	endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	
	
endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU|Clang")

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")

endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")

## OPTION CONFIGURATION

## FILE CONFIGURATION


################################################################################
# CTEST CONFIGURATION                                                          #
################################################################################
enable_testing()
# consider creating a library to avoid re-compilation

set(_game_test_suites
	collision physics
)
# specify the tests for the suites
set(collision_tests 1 2 3 4)

# ensure at least one test for each suite
foreach(game_test_suite ${_game_test_suites})
	if(NOT DEFINED "${game_test_suite}_tests")
		set(${game_test_suite}_tests "1")
	endif(NOT DEFINED "${game_test_suite}_tests")
endforeach(game_test_suite)

# aggregate test suite source files
foreach(game_test_suite ${_game_test_suites))
	set(_game_test_suite_sources ${_game_test_suite_sources} ${game_test_suite}TestSuite.c)
endforeach(game_test_suite)
int collisionTestSuite(int argc, char** argv)
{
	if (my_strcmp(argv[1], "test_name")) {
		test_name();		
	} else if () {
		// ...		
	}
	return 0;
}

int my_strcmp(const char* s1, const char* s2)
{
	while (*s1 != NULL && (*s1 == *s2)) {
		++s1;
		++s2;
	}	

	return (*s1 - *s2);
}

create_test_sourcelist(project_source_files test_driver_name test_suite_source_files)
add_executable(test_driver_name ${project_source_files} obtest.c??)
# ./test_driver_name will now run all the test suites

# generate test cases
foreach(game_test_suite ${_game_test_suites})
	foreach(game_test ${${game_test_suite}_tests})
		add_test(NAME ${game_test_suite}_${game_test}
			COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_driver_name ${game_test_suite}TestSuite ${game_test})
		)
	endforeach(game_test)
endforeach(game_test_suite)


# then run with: ctest -R collisions


################################################################################
# CPACK CONFIGURATION                                                          #
################################################################################
# May have to consider handling uninstall
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "name")
set(CPACK_PACKAGE_VENDOR "Ryan McClue")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Example")
set(CPACK_PACKAGE_VERSION "1.0.0") # version of installer
set(CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "ExampleDir")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/icon.ico")
include(CPack)
include(CPackIFW)

target_include_directories(name PUBLIC
	"${name_SOURCE_DIR}/include"
)

configure_file(
	"${name_SOURCE_DIR}/include/config.h.in"
)

# set CMAKE_PREFIX_PATH appropriatley.
# unfortunately cannot do code coverage
find_package(easy_profiler REQUIRED)
target_link_libraries(name easy_profiler)
# refer to easy_profiler github readme to compile with msvc not using visual studio
# for actual profiler use remotery. remotery is only useful if program has a 'main-loop'.

# enable_language(ASM_MASM)
# properties and caches for access in subdirectories

