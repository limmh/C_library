#ifndef SAFER_C_LIBRARY_MACRO_CONCATENATE_H
#define SAFER_C_LIBRARY_MACRO_CONCATENATE_H

/** @brief Combines two macro arguments into a single name */
#define SAFER_C_LIBRARY_CONCATENATE_(A, B) A##B

/**
 * @brief Combines two macro arguments into a single name
 *
 * If either macro argument is a preprocessor macro itself, it will be resolved to its value.
 */
#define SAFER_C_LIBRARY_CONCATENATE(A, B)  SAFER_C_LIBRARY_CONCATENATE_(A, B)

#ifdef SAFER_C_LIBRARY_MACRO_CONCATENATE_HAS_SHORT_MACRO
#ifdef CONCATENATE
#define CONCATENATE(A, B) SAFER_C_LIBRARY_CONCATENATE(A, B)
#else
#error "CONCATENATE has been defined and shall not be redefined."
#endif
#endif

#endif
