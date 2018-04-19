if(DEFINED __find_available_simd_extensions_cmake__)
	return()
endif(DEFINED __find_available_simd_extensions_cmake__)
set(__find_available_simd_extensions_cmake__ TRUE)

function(_parse_simd_extensions cpu_info)
	set(_available_simd_extensions PARENT_SCOPE) 

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
	
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	execute_process(COMMAND "grep 'flags' /proc/cpuinfo" OUTPUT_VARIABLE _cpuinfo)

	_parse_simd_extensions(_cpuinfo)

endif(CMAKE_SYSTEM_NAME MATCHES "Linux")


if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
	execute_process(COMMAND "sysctl -a | grep machdep.cpu.features" OUTPUT_VARIABLE _cpuinfo)

	_parse_simd_extensions(_cpuinfo)

endif(CMAKE_SYSTEM_NAME MATCHES "Darwin")



if(CMAKE_SYSTEM_NAME MATCHES "Windows")

endif(CMAKE_SYSTEM_NAME MATCHES "Windows")
