#ifndef SAFER_C_LIBRARY_MACRO_STRINGIFY_H
#define SAFER_C_LIBRARY_MACRO_STRINGIFY_H

/** @brief Converts the macro argument to a read-only string */
#define SAFER_C_LIBRARY_STRINGIFY_(VALUE) #VALUE

/**
 * @brief Converts the macro argument to a read-only string
 *
 * If the macro argument is a preprocessor macro, it will be resolved to its value.
 */
#define SAFER_C_LIBRARY_STRINGIFY(VALUE)  SAFER_C_LIBRARY_STRINGIFY_(VALUE)

#ifdef SAFER_C_LIBRARY_MACRO_STRINGIFY_HAS_SHORT_NAME
#ifndef STRINGIFY
#define STRINGIFY(VALUE) SAFER_C_LIBRARY_STRINGIFY(VALUE)
#else
#error "STRINGIFY has been defined and shall not be redefined."
#endif
#endif

#endif
