if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD is not defined.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

add_library(
	io STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/keyboard_input.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/keyboard_input.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/sleep.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/sleep.h"
)
set_target_properties(
	io PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	io PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

add_executable(
	keyboard_input_test
	"${CMAKE_CURRENT_SOURCE_DIR}/keyboard_input_test.c"
)
set_target_properties(
	keyboard_input_test PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	keyboard_input_test PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	keyboard_input_test
	io
)

add_executable(
	keyboard_input_test2
	"${CMAKE_CURRENT_SOURCE_DIR}/keyboard_input_test2.c"
)
set_target_properties(
	keyboard_input_test2 PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	keyboard_input_test2 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	keyboard_input_test2
	io
)
