#ifndef MACRO_STRINGIFY_H
#define MACRO_STRINGIFY_H

/** @brief Converts the macro argument to a read-only string */
#define STRINGIFY_(VALUE) #VALUE

/**
 * @brief Converts the macro argument to a read-only string
 *
 * If the macro argument is a preprocessor macro, it will be resolved to its value.
 */
#define STRINGIFY(VALUE)  STRINGIFY_(VALUE)

#endif
