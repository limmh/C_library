#ifndef MACRO_CONCATENATE_H
#define MACRO_CONCATENATE_H

/** @brief Combines two macro arguments into a single name */
#define CONCATENATE_(A, B) A##B

/**
 * @brief Combines two macro arguments into a single name
 *
 * If either macro argument is a preprocessor macro itself, it will be resolved to its value.
 */
#define CONCATENATE(A, B)  CONCATENATE_(A, B)

#endif
