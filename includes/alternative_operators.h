#ifndef SAFER_C_LIBRARY_ALTERNATIVE_OPERATORS_H
#define SAFER_C_LIBRARY_ALTERNATIVE_OPERATORS_H

#ifndef __cplusplus

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L)
#include <iso646.h>
#else
#define and     &&
#define and_eq  &=
#define bitand  &
#define bitor   |
#define compl   ~
#define not     !
#define not_eq  !=
#define or      ||
#define or_eq   |=
#define xor     ^
#define xor_eq  ^=
#endif

#endif /* __cplusplus */

#endif
