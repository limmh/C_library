#ifndef INLINE_OR_STATIC_H
#define INLINE_OR_STATIC_H

/**
 * @brief Macro to suggest that the compiler should inline a function
 *
 * The compiler may or may not inline a function marked with this macro.
 */

#if defined(__cplusplus)
#define INLINE_OR_STATIC inline
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define INLINE_OR_STATIC static inline
#else
#define INLINE_OR_STATIC static
#endif

#endif
