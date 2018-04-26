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

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
	message(FATAL_ERROR "Only allow builds for x64.")
	return()
endif(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(WARNING "Prefer out-of-tree CMake builds.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

list(INSERT "${CMAKE_MODULE_PATH}" 0 "${CMAKE_SOURCE_DIR}/CMake/Modules")

project(name)
enable_language(C)

include(SetVersion)
include(HandleBuildType)

configure_file(
	"${PROJECT_SOURCE_DIR}/include/common.h.in"
	"${PROJECT_BINARY_DIR}/include/common.h"
)

set(CORE_SOURCES
	${PROJECT_SOURCE_DIR}/src/core/file.c
	${PROJECT_SOURCE_DIR}/src/core/file2.c
)

add_executable(name
	${CORE_SOURCES}
	${OTHER_SOURCE}
)

target_include_directories(name PUBLIC
	"${PROJECT_SOURCE_DIR}/include"
)

find_package(SDL2 REQUIRED)
target_include_directories(name ${SDL2_INCLUDE_DIRS})
target_link_libraries(name ${SDL2_LIBRARIES})

################################################################################
# CTEST CONFIGURATION                                                          #
################################################################################
enable_testing()

set(_game_test_suites
	collision physics
)
# specify the tests for the suites
set(collision_tests 1 2 3 4)
set(physics_tests "inertia" 2 3 4)

# aggregate test suite source files
foreach(game_test_suite ${_game_test_suites))
	set(_game_test_suite_sources ${_game_test_suite_sources} test/${game_test_suite}TestSuite.c)
endforeach(game_test_suite)
int collisionTestSuite(int argc, char** argv)
{
	if (game_strcmp(argv[1], "test_name")) {
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
add_executable(test_driver_name ${project_source_files} src/utils/helpers.c)

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

