#: Author       "Russell Coight" <rj.coight@gmail.com>
#: Description  General C-based project configuration supporting CMake, CTest and CPack.
#: Usage        
#::   mkdir build/ && cd build/ && cmake .. 
#::   ctest <name>
#::   cpack <name>

##################################
## CMAKE CONFIGURATION
##################################
cmake_minimum_required(2.8 FATAL_ERROR)
project(
  name
  VERSION 0.0.1
  LANGUAGES C
)

## COMPILER CONFIGURATION
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU|Clang")
	# determine ARCH with supported compiler macros
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



# enable_language(ASM_MASM)
# properties and caches for access in subdirectories

# windows
# execute_process(COMMAND SET Process OUTPUT_VARIABLE WINDOWS_MACHINE) 
if (${GCC_MACHINE} MATCHES "x86.*")
	# Set ARCH_SUPPORT to Native, SSE, AVX, etc
	# Also set appropriate compiler flags
elseif (${GCC_MACHINE})

else ()

endif ()

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

configure_file(

)
