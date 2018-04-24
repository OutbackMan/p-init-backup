if(DEFINED __game_version_cmake__)
	return()
endif(DEFINED __game_version_cmake__)
set(__game_version_cmake__ TRUE)

find_package(Git)
if(GIT_FOUND AND EXISTS ${CMAKE_SOURCE_DIR}/.git)
	message(STATUS "Extracting project version information from 'git describe'")
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags
        OUTPUT_VARIABLE GIT_DESCRIBE OUTPUT_STRIP_TRAILING_WHITESPACE
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
	# git describe works on annotated tags (git add . && git commit && git tag -a v0.1 -m "msg" && git push)

	string(REGEX MATCH "^v([0-9]+)[.]([0-9]+)[.]([0-9]+)$" "\\1" CMAKE_MAJOR_VERSION GIT_DESCRIBE)
	string(REGEX MATCH "^v([0-9]+)[.]([0-9]+)[.]([0-9]+)$" "\\2" CMAKE_MINOR_VERSION GIT_DESCRIBE)
	string(REGEX MATCH "^v([0-9]+)[.]([0-9]+)[.]([0-9]+)$" "\\3" CMAKE_PATCH_VERSION GIT_DESCRIBE)

else(GIT_FOUND)
	message(WARNING "Unable to get version number due to the absence of git")
endif(GIT_FOUND)
