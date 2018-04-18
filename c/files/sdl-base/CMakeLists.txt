#: Author       "Ryan McClue" <rj.coight@gmail.com>
#: Description  General C-based project configuration supporting CMake, CTest and CPack.
#: Usage        
#::   mkdir build/ && cd build/ && cmake .. 
#::   ctest <name>
#::   cpack <name>

# The data in the instruction like float x = y + 3; will be replicated a minimum of 4 times, and only one will be kept.
# This is due to SIMD. (SSE, AVX are 4 wide. This layout can waste pixels if iterating sequentially)
# The effort to decode instruction stream and decide how to operate on it, e.g can instructions be executed in parallel, i.e. pipelined,
# what circuits are available to use etc.

struct Color {
	int r, g, b, a;	
}

# SOA preferred for loading into SIMD register as intel doesn't support strided loading, e.g. load every 4th byte
struct Color {
	int* r;	
	int* g;	
	int* b;	
	int* a;	
}
# obtain SSE instructions from intel intrinsics (rotate integer)
emmintrin.h
__m128 value_a = __mm_set1_ps(1.0f); # set all 4 lanes to 1
__m128 value_b = __mm_set1_ps(2.0f);
__m128 sum = __mm_sum_ps(value_a, value_b);

# cpu will copy from memory->cache->registers, then registers->cache->memory
# cycle is the smallest unit of time for a CPU. L1, L2, L3 increasing cycle access count.
# the instructions from memory, i.e. produced from the compiler will be loaded and decoded to i-cache as microcode.
# each cycle, we access instruction stream from i-cache and issue the instruction, i.e. pass off to a unit, e.g. ALU, etc.
# this occurs out of order, to prevent latency from instructions depending on others
# issuing the instruction begins a pipeline, whereby each instruction is executed in stages. Each stage completes part of an instruction in parallel.
# this is to allow units to be free earlier
# instructions only care about throughput as we assume we are operating on many things at once so latency becomes less important.

# for every instruction, we would like to know what the latency (time from issue to completion) and throughput (how many can be done if pipelined) is.
# always care about memory bandwidth/throughput, i.e how much memory moved on bus to cpu
# prefetch to avoid cache misses which are costly due to memory latency (hyperthreading can also be used, i.e. swap between logical threads)
# so, small code size for i-cache
# high cache coherency
# know instruction stream to utilise pipelining

# 1. work out how many cycles we have to maintain frame rate (1 core, 1 cpu). In actuality, a 4 core cpu will each have the same clock speed.
# 2. gather statistics
# 3. make estimate regarding how fast it should be running
# 4. analyze efficiency and performance
# ----
# 1. focus in on most time spent
# 2. remove unecessary code
# 3. replace function calls with inline code (paste in location to flatten)
# 4. smarter ways of doing things (precomputing, operations bypassed with if)

##################################
## CMAKE CONFIGURATION
##################################
cmake_minimum_required(2.8 FATAL_ERROR)
project(
  name
  VERSION 0.0.1
  LANGUAGES C
)
# execute_process(COMMAND SET Process OUTPUT_VARIABLE WINDOWS_MACHINE) 
if (${GCC_MACHINE} MATCHES "x86.*")
	# Set ARCH_SUPPORT to Native, SSE, AVX, etc
	# Also set appropriate compiler flags
elseif (${GCC_MACHINE})

else ()

endif ()

# add flags for profiling
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


##################################
## CTEST CONFIGURATION
##################################
enable_testing()


##################################
## CPACK CONFIGURATION
##################################
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

