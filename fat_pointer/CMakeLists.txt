if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD is not defined for fat pointer.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

if (NOT DEFINED PROGRAM_C_STANDARD)
	message("PROGRAM_C_STANDARD is not defined for fat pointer.")
	set(PROGRAM_C_STANDARD "99")
	message("PROGRAM_C_STANDARD is defined as ${PROGRAM_C_STANDARD}.")
endif()

# library
add_library(
	fat_pointer STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/fat_pointer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/fat_pointer.h"
)
set_target_properties(
	fat_pointer PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	fat_pointer PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
)
target_link_libraries(
	fat_pointer
	safer_integer
)

add_library(
	fat_pointer_c99 STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/fat_pointer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/fat_pointer.h"
)
set_target_properties(
	fat_pointer_c99 PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	fat_pointer_c99 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
)
target_link_libraries(
	fat_pointer_c99
	safer_integer
)

# test programs
add_executable(
	fat_pointer_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/fat_pointer_tests.c"
)
set_target_properties(
	fat_pointer_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	fat_pointer_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	fat_pointer_tests
	fat_pointer
	safer_integer
	terminal_text_color
	unit_testing
)

add_executable(
	fat_pointer_tests_c99
	"${CMAKE_CURRENT_SOURCE_DIR}/fat_pointer_tests.c"
)
set_target_properties(
	fat_pointer_tests_c99 PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	fat_pointer_tests_c99 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	fat_pointer_tests_c99
	fat_pointer_c99
	safer_integer
	terminal_text_color
	unit_testing
)
