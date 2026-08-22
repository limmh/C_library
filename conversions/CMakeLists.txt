if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD is not defined.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

if (NOT DEFINED PROGRAM_C_STANDARD)
	message("PROGRAM_C_STANDARD is not defined.")
	set(PROGRAM_C_STANDARD "99")
	message("PROGRAM_C_STANDARD is defined as ${PROGRAM_C_STANDARD}.")
endif()

add_library(
	conversions STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/integer_to_string.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/integer_to_string.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/string_to_integer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/string_to_integer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/string_to_integer_error_codes.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/string_info_type.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/string_info_type.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/char_utils.h"
)
set_target_properties(
	conversions PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	conversions PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
)
target_link_libraries(
	conversions
	safer_integer
)

add_executable(
	integer_to_string_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/integer_to_string_tests.c"
)
set_target_properties(
	integer_to_string_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	integer_to_string_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	integer_to_string_tests
	conversions
	safer_integer
	terminal_text_color
	unit_testing
)
add_test(
	NAME integer_to_string_tests
	COMMAND $<TARGET_FILE:integer_to_string_tests>
)
set_tests_properties(
	integer_to_string_tests
	PROPERTIES
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
	LABELS "unit"
	TIMEOUT 1
)

add_executable(
	string_to_integer_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/string_to_integer_tests.c"
)
set_target_properties(
	string_to_integer_tests PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	string_to_integer_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	string_to_integer_tests
	conversions
	safer_integer
	terminal_text_color
	unit_testing
)
add_test(
	NAME string_to_integer_tests
	COMMAND $<TARGET_FILE:string_to_integer_tests>
)
set_tests_properties(
	string_to_integer_tests
	PROPERTIES
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
	LABELS "unit"
	TIMEOUT 1
)
