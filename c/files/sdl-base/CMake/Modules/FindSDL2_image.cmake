find_path(SDL2_IMAGE_INCLUDE_DIR
	NAMES SDL_image.h
	HINTS ENV SDL2_IMAGE_DIR SDL2_DIR
	PATH_SUFFIXES SDL2 include/SDL2 include
)

find_library(SDL2_LIBRARY_TEMP
	NAMES SDL2
	HINTS ENV SDL2_DIR
	PATH_SUFFIXES lib lib64 lib/x64
)

if(APPLE)
	set(SDL2_LIBRARY ${SDL2_LIBRARY_TEMP} "-framework Cocoa")
endif(APPLE)

if(NOT APPLE)
	find_package(Threads)
	set(SDL_LIBRARY ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
endif(NOT APPLE)

set(SDL2_LIBRARIES ${SDL2_LIBRARY})
set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2 DEFAULT_MSG
	REQUIRED_VARS SDL2_LIBRARIES SDL2_INCLUDE_DIRS
)
