#ifndef NUMBER_STRINGS_H
#define NUMBER_STRINGS_H

int is_permut(unsigned int a, unsigned int b);
int are_permut(unsigned int a, unsigned int b, unsigned int c);

int is_permutl(unsigned long a, unsigned long b);
int are_permutl(unsigned long a, unsigned long b, unsigned long c);

int digit_id(unsigned int n);
long digit_idl(unsigned long n);

int is_palindrome(unsigned int num);
int is_palindromel(unsigned long num);

int reverse(unsigned int num);
long reversel(unsigned long num);

#endif // NUMBER_STRINGS_H
