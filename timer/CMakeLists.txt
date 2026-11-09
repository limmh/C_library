if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD was not defined for timer.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

if (NOT DEFINED PROGRAM_C_STANDARD)
	message("PROGRAM_C_STANDARD was not defined for timer.")
	set(PROGRAM_C_STANDARD "99")
	message("PROGRAM_C_STANDARD is defined as ${PROGRAM_C_STANDARD}.")
endif()

# library
add_library(
	timer STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/tick_count.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/tick_count.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/timer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/timer.h"
)
set_target_properties(
	timer PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	timer PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
)
target_link_libraries(
	timer
	safer_integer
)

add_executable(
	timer_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/timer_tests.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/timer.h"
)
set_target_properties(
	timer_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	timer_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	timer_tests
	timer
	terminal_text_color
	unit_testing
)
add_test(
	NAME timer_tests
	COMMAND $<TARGET_FILE:timer_tests>
)
set_tests_properties(
	timer_tests
	PROPERTIES
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
	LABELS "unit"
	TIMEOUT 1
)

add_executable(
	tick_count_demo
	"${CMAKE_CURRENT_SOURCE_DIR}/tick_count_demo.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/tick_count.h"
)
set_target_properties(
	tick_count_demo PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	tick_count_demo PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	tick_count_demo
	timer
)
