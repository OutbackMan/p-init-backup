if(DEFINED __GAME_BUILD_TYPES_CMAKE__)
  return()
endif(DEFINED __GAME_BUILD_TYPES_CMAKE__)
set(__GAME_BUILD_TYPES_CMAKE__ TRUE)

include(FindSIMD)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU|Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -maccumulate-outgoing-args -std=c99")

	foreach(simd_extension ${_available_simd_extensions})
		if(simd_extension STREQUAL "sse2")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
		elseif(simd_extension STREQUAL "sse3")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse3")
		elseif(simd_extension STREQUAL "ssse3")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mssse3")
		elseif(simd_extension STREQUAL "sse4.1")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
		elseif(simd_extension STREQUAL "sse4.2")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
		elseif(simd_extension STREQUAL "avx")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
		elseif(simd_extension STREQUAL "avx2")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
	endforeach(simd_extension)
# if lower versions don't support, then axe them
	_check_adding_compiler_flag("-fno-omit-frame-pointer" DEBUG)
	_check_adding_compiler_flag("-fsanitize=address" DEBUG)
	_check_adding_compiler_flag("-fsanitize=undefined" DEBUG)
	
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb3 -g3 -O0")
	  set(CMAKE_C_FLAGS_MINSIZEREL "-Os -ffast-math -DNDEBUG -s -fmerge-all-constants")
	  set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O3 -ffast-math -DNDEBUG -ggdb3 -g3 -fmerge-all-constants")
	  set(CMAKE_C_FLAGS_RELEASE "-O3 -ffast-math -DNDEBUG -fmerge-all-constants")

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

  if (${CEN64_ARCH_SUPPORT} MATCHES "SSE2")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D__SSE2__")
  elseif (${CEN64_ARCH_SUPPORT} MATCHES "SSSE3")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D__SSE2__ /D__SSE3__ /D__SSSE3__")
  elseif (${CEN64_ARCH_SUPPORT} MATCHES "SSE3")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D__SSE2__ /D__SSE3__")
  elseif (${CEN64_ARCH_SUPPORT} MATCHES "SSE4.1")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D__SSE2__ /D__SSE3__ /D__SSSE3__ /D__SSE4_1__")
  elseif (${CEN64_ARCH_SUPPORT} MATCHES "AVX")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D__SSE2__ /D__SSE3__ /D__SSSE3__ /D__SSE4_1__ /arch:AVX")
  endif ()

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

