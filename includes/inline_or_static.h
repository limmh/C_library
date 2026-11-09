#ifndef SAFER_C_LIBRARY_INLINE_OR_STATIC_H
#define SAFER_C_LIBRARY_INLINE_OR_STATIC_H

#ifdef INLINE_OR_STATIC
#error "INLINE_OR_STATIC has been defined and shall not be redefined."
#endif

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
