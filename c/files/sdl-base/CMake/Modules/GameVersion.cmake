if(DEFINED __game_version_cmake__)
	return()
endif(DEFINED __game_version_cmake__)
set(__game_version_cmake__ TRUE)


find_package(Git)
if(GIT_FOUND AND EXISTS ${CMAKE_SOURCE_DIR}/.git)
	message(STATUS "Extracting project version information from 'git describe'")


endif(GIT_FOUND)
