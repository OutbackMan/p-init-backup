if(DEFINED __find_available_simd_extensions_cmake__)
	return()
endif(DEFINED __find_available_simd_extensions_cmake__)
set(__find_available_simd_extensions_cmake__ TRUE)

# assume all cpus support sse (introduced 1997).
# assume all cpus support sse2 (introduced 2001).
# sse3 (introduced 2004)
# ssse3 (2006)

# http://users.atw.hu/instlatx64/CPU_chart_v191.png
# https://github.com/Maratyszcza/cpuinfo/blob/master/src/x86/uarch.c
# https://software.intel.com/en-us/articles/intel-architecture-and-processor-identification-with-cpuid-model-and-family-numbers
#  CPUID Signature Values of Of Recent Intel Microarchitectures 
# (https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-optimization-manual.pdf)

# look at wiki pages for sse, sse2, etc. to find what architecture first supported
function(_parse_simd_extensions cpu_vendor_str cpu_arch_family_num cpu_arch_model_num)
	set(_available_simd_extensions PARENT_SCOPE)
	list(APPEND _available_simd_extensions sse)
	list(APPEND _available_simd_extensions sse2)
	list(APPEND _available_simd_extensions sse3)
	
	if(cpu_vendor_str STREQUAL "GenuineIntel")
		if(cpu_arch_family_num STREQUAL "6")
			# Skylake
			if(cpu_arch_model_num STREQUAL "58")
			# Broadwell
			if(cpu_arch_model_num STREQUAL "58")
			# Haswell
			if(cpu_arch_model_num STREQUAL "58")
			# IvyBridge
			if(cpu_arch_model_num STREQUAL "58")

				list(APPEND _available_simd_extensions sse3)
			# SandyBridge
			elseif(cpu_arch_model_num STREQUAL "42" OR cpu_arch_model_num STREQUAL "46")

			# Westmere 
			elseif(cpu_arch_model_num STREQUAL "37" OR cpu_arch_model_num STREQUAL "44" OR cpu_arch_model_num STREQUAL "47")

			# Nehalem
			elseif(cpu_arch_model_num STREQUAL "37" OR cpu_arch_model_num STREQUAL "44" OR cpu_arch_model_num STREQUAL "47")
				

			# Enhanced Core
			elseif(cpu_arch_model_num STREQUAL "37" OR cpu_arch_model_num STREQUAL "44" OR cpu_arch_model_num STREQUAL "47") 
		else(cpu_family STREQUAL "6")
			message(WARNING "Your Intel CPU architecture is not supported. Defaulting to 'sse', 'sse2' and 'sse3' extensions.")
		endif(cpu_family STREQUAL "6")
	
	elseif(cpu_vendor_str STREQUAL "AuthenticAMD")
		if(cpu_arch_family_num EQUAL 15 AND cpu_arch_model_num GREATER 64)
			message(STATUS "Detected AMD K8 CPU architecture. Supports 'sse', 'sse2', 'sse3'")
			list(APPEND _available_simd_extensions sse)

		elseif(cpu_arch_family_num STREQUAL "16")
			message(STATUS "Detected AMD K10 CPU architecture.")

		elseif(cpu_arch_family_num STREQUAL "20")
			message(STATUS "Detected AMD Bobcat CPU architecture.")

		elseif(cpu_arch_family_num STREQUAL "21")
			message(STATUS "Detected AMD Bulldozer CPU architecture.")

		elseif(cpu_arch_family_num STREQUAL "22")
			message(STATUS "Detected AMD Jaguar CPU architecture.")

		elseif(cpu_arch_family_num STREQUAL "23")
			message(STATUS "Detected AMD Zen CPU architecture.")
			# ryzen

		else(cpu_arch_family_num STREQUAL "15")
			message(WARNING "Your AMD CPU architecture is not supported. Defaulting to 'sse', 'sse2' and 'sse3' extensions.")
		endif(cpu_arch_family_num STREQUAL "15")
		
	else(cpu_vendor_str STREQUAL "GenuineIntel")
		message(WARNING "CPU vendor is not either of the supported Intel or AMD vendors. Defaulting to 'sse', 'sse2' and 'sse3' extensions.")
	endif(cpu_vendor_str STREQUAL "GenuineIntel")
endfunction(_parse_simd_extensions)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")

	file(READ "/proc/cpuinfo" _cpu_info)
	string(REGEX MATCH ".*vendor_id[\t]*:[\t]+([a-zA-Z0-9_-]+).*" "\\1" _cpu_vendor_str _cpu_info)
	string(REGEX MATCH ".*cpu family[\t]*:[\t]+([a-zA-Z0-9_-]+).*" "\\1" _cpu_arch_family_num _cpu_info)
	string(REGEX MATCH ".*model[\t]*:[\t]+([a-zA-Z0-9_-]+).*" "\\1" _cpu_arch_model_num _cpu_info)

elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")

	execute_process(COMMAND "sysctl -n machdep.cpu.vendor" OUTPUT_VARIABLE _cpu_vendor_str)
    execute_process(COMMAND "sysctl -n machdep.cpu.family" OUTPUT_VARIABLE _cpu_arch_family_num)
    execute_process(COMMAND "sysctl -n machdep.cpu.model"  OUTPUT_VARIABLE _cpu_arch_model_num)

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")

	execute_process(COMMAND "REG QUERY HKLM\\Hardware\\Description\\System\\CentralProcessor\\0 /v VendorIdentifier"
		OUTPUT_VARIABLE _cpu_vendor_str)
	execute_process(COMMAND "REG QUERY HKLM\\Hardware\\Description\\System\\CentralProcessor\\0 /v Identifier"
		OUTPUT_VARIABLE _cpu_id)
	string(REGEX MATCH ".* Family ([0-9]+).*" "\\1" _cpu_arch_family_num _cpu_id)
	string(REGEX MATCH ".* Model ([0-9]+).*" "\\1" _cpu_arch_model_num _cpu_id)

else(CMAKE_SYSTEM_NAME MATCHES "Linux")

	message(WARNING "OS is not either of the supported OS's Linux, Mac or Windows")

endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

_parse_simd_extensions(_cpu_vendor_str _cpu_arch_family_num _cpu_arch_model_num)

foreach(simd_extension ${_available_simd_extensions})
	CheckCCompilerFlag(simd_extension supports_simd_extension)
	if(supports_simd_extension)
		message(WARNING "Compiler doesn't support simd extension: '${simd_extension}'")
	else(supports_simd_extension)
		# add compiler flag
	endif(supports_simd_extension)

endforeach()












