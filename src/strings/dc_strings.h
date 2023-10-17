#ifndef _DC_STRINGS_H
#define _DC_STRINGS_H

#ifndef _STDINT_H
#include "stdint.h"
#endif

/* nstrings/permutations.c */
#define dc_is_permutation(x,y) (dc_digit_id(x) == dc_digit_id(y))
#define dc_is_palindrome(x) (x == reverse(x))

uint64_t dc_digit_id (uint64_t n);
uint64_t dc_reverse (uint64_t n);


#endif // _DC_STRINGS_H
