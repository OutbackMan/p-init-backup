if(DEFINED __find_available_simd_extensions_cmake__)
	return()
endif(DEFINED __find_available_simd_extensions_cmake__)
set(__find_available_simd_extensions_cmake__ TRUE)

# assume all cpus support sse (introduced 1997).
# assume all cpus support sse2 (introduced 2001).
# sse3 (introduced 2004)
# ssse3 (2006)
# https://software.intel.com/en-us/articles/intel-architecture-and-processor-identification-with-cpuid-model-and-family-numbers
# look at wiki pages for sse, sse2, etc. to find what architecture first supported
function(_parse_simd_extensions cpu_info)
	set(_available_simd_extensions PARENT_SCOPE)
	
	if(cpu_vendor STREQUAL "GenuineIntel")
		# pentium pro <---> skylake
		if(cpu_family STREQUAL "6")
			if(cpu_model EQUAL 0x3a)
			
			
		
		endif(cpu_family STREQUAL "6")
		
		# pentium
		if(cpu_family STREQUAL "5")
		
		endif(cpu_family STREQUAL "5")
		
		if(cpu_family STREQUAL "15")
		
		# netburst
		endif(cpu_family STREQUAL "15")
	
	
	endif(cpu_vendor STREQUAL "GenuineIntel")
	
	if(cpu_vendor STREQUAL "AuthenticAMD")
	
	

	string(REGEX MATCH "^.*(sse).*$" "\\1" _sse_there cpu_info)
	list(APPEND _available_simd_extensions _sse_there)

	string(REGEX MATCH "^.*(sse2).*$" "\\1" _sse2_there cpu_info)
	list(APPEND _available_simd_extensions _sse2_there)

	# SSE3 intel code name Prescott New Instructions
	string(REGEX MATCH "^.*(sse3|pni).*$" "\\1" _sse3_there cpu_info)
	list(APPEND _available_simd_extensions _sse3_there)

	string(REGEX MATCH "^.*(ssse3).*$" "\\1" _ssse3_there cpu_info)
	list(APPEND _available_simd_extensions _ssse3_there)

	# mac will have sse4.1
	string(REGEX MATCH "^.*(sse4_1).*$" "\\1" _sse4_1_there cpu_info)
	list(APPEND _available_simd_extensions _sse4_1_there)

	string(REGEX MATCH "^.*(sse4_2).*$" "\\1" _sse4_2_there cpu_info)
	list(APPEND _available_simd_extensions _sse4_2_there)

	string(REGEX MATCH "^.*(avx).*$" "\\1" _avx_there cpu_info)
	list(APPEND _available_simd_extensions _avx_there)

	string(REGEX MATCH "^.*(avx2).*$" "\\1" _avx2_there cpu_info)
	list(APPEND _available_simd_extensions _avx2_there)

	string(REGEX MATCH "^.*(avx512).*$" "\\1" _avx512_there cpu_info)
	list(APPEND _available_simd_extensions _avx512_there)

endfunction(_parse_simd_extensions)
	
# CPUID Signature Values of Of Recent Intel Microarchitectures
# skylake: 4E 5E -->

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	file(READ "/proc/cpuinfo" _cpu_info)
	string(REGEX MATCH ".*vendor_id[\t]*:[\t]+([a-zA-Z0-9_-]+).*" "\\1" _cpu_vendor _cpu_info)
	string(REGEX MATCH ".*cpu family[\t]*:[\t]+([a-zA-Z0-9_-]+).*" "\\1" _cpu_architecture_family_id _cpu_info)
	string(REGEX MATCH ".*model[\t]*:[\t]+([a-zA-Z0-9_-]+).*" "\\1" _cpu_model _cpu_info)
	string(REGEX MATCH ".*flags[\t]*:[\t]+([a-zA-Z0-9_-]+).*" "\\1" _cpu_flags _cpu_info)

	if(_cpu_vendor STREQUAL "GenuineIntel")

	endif()

	_parse_simd_extensions(_cpuinfo)

endif(CMAKE_SYSTEM_NAME MATCHES "Linux")


if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
	execute_process(COMMAND "sysctl -a | grep machdep.cpu.features" OUTPUT_VARIABLE _cpuinfo)

	_parse_simd_extensions(_cpuinfo)

endif(CMAKE_SYSTEM_NAME MATCHES "Darwin")


# refer to Intel SDM (software developers manual. this also contains ISA)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	execute_process(COMMAND "REG QUERY HKLM\\Hardware\\Description\\System\\CentralProcessor\\0 /v VendorIdentifier"
		OUTPUT_VARIABLE _cpu_vendor)
	execute_process(COMMAND "HKLM\\Hardware\\Description\\System\\CentralProcessor\\0 /v Identifier"
		OUTPUT_VARIABLE _cpu_id)

# assume sse and sse2 support

# CPUID signature values of architectures
# product comparison for instruction set extensions

# vendor_id (intel, amd)
# model (intel core i5-7200u @ 2.50GHz)
# family (determines architecture, code, 4000, 4th generation, Haswell)
# flags

# check for all others



endif(CMAKE_SYSTEM_NAME MATCHES "Windows")
















