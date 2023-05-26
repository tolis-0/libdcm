#ifndef _NSTRINGS_H
#define _NSTRINGS_H


/* nstrings/permutations.c */
#define is_permut7(x,y) (digit_id7(x) == digit_id7(y))
#define is_permut(x,y) (digit_id63(x) == digit_id63(y))
#define is_palindrome(x) (x == reverse(x))

uint32_t digit_id7 (uint32_t n);
uint64_t digit_id (uint64_t n);
uint64_t reverse (uint64_t n);


#endif // _NSTRINGS_H
