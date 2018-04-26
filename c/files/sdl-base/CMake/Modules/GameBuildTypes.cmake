if(DEFINED __GAME_BUILD_TYPES_CMAKE__)
  return()
endif(DEFINED __GAME_BUILD_TYPES_CMAKE__)
set(__GAME_BUILD_TYPES_CMAKE__ TRUE)


if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU|Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -std=c99 -msse2 -msse3 -mavx -march=native")

	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG_BUILD -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")
	
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb3 -g3 -O0")
	  set(CMAKE_C_FLAGS_MINSIZEREL "-Os -ffast-math -DRELEASE_BUILD -s -fmerge-all-constants")
	  set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O3 -ffast-math -DRELEASE_BUILD -ggdb3 -g3 -fmerge-all-constants")
	  set(CMAKE_C_FLAGS_RELEASE "-O3 -ffast-math -DRELEASE_BUILD -fmerge-all-constants")

	  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")
	  set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-s")

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto -fdata-sections -ffunction-sections -mtune=cpu-type")
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -flto -fdata-sections -ffunction-sections -mtune=cpu-type")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,--gc-sections")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -Wl,--gc-sections")

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -funsafe-loop-optimizations")
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -funsafe-loop-optimizations")

	if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		_check_adding_compiler_flag("-fsanitize=leak" DEBUG)
	
	else("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		_check_adding_compiler_flag("-fsanitize=dataflow" DEBUG)
		_check_adding_compiler_flag("-fsanitize=safe-stack" DEBUG)
	
	endif("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D__SSE2__ /D__SSE3__ /arch:AVX")

endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")

# Build RelWithDebInfo by default so builds are fast out of the box
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)


















# The CACHE STRING is used to appear as configurable in cmake-gui
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra" CACHE STRING "Flags used by C compiler during release build.")

set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O3 -ffast-math -DNDEBUG -ggdb3 -g3 -fmerge-all-constants")

set(CMAKE_C_FLAGS_MINSIZEREL "-Os -ffast-math -DNDEBUG -s -fmerge-all-constants")
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

