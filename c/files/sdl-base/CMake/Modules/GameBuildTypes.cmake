if(DEFINED __GAME_BUILD_TYPES_CMAKE__)
  return()
endif(DEFINED __GAME_BUILD_TYPES_CMAKE__)
set(__GAME_BUILD_TYPES_CMAKE__ TRUE)


include(FindSIMD)

# The CACHE STRING is used to appear as configurable in cmake-gui
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra" CACHE STRING "Flags used by C compiler during release build.")

