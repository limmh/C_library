if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD was not defined for timer.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

# library
add_library(
	timer STATIC
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
