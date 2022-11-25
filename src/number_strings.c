#include "number_strings.h"
#include "dcmath.h"

// for numbers up to 7 digits
int is_permut(unsigned int a, unsigned int b){
	return digit_id(a) == digit_id(b);
}

int are_permut(unsigned int a, unsigned int b, unsigned int c){
	int digit_id_a = digit_id(a);
	if (digit_id_a != digit_id(b)) return 0;
	return digit_id_a == digit_id(c);
}



// for numbers that can go above 7 digits
int is_permutl(unsigned long a, unsigned long b){
	return digit_idl(a) == digit_idl(b);
}

int are_permutl(unsigned long a, unsigned long b, unsigned long c){
	long digit_id_a = digit_idl(a);
	if (digit_id_a != digit_idl(b)) return 0;
	return digit_id_a == digit_idl(c);
}



// Calculating digit id
// numbers that have the same digits but in different order will have the same digit id
int digit_id(unsigned int n){
	long ret = 0;
	while(n) ret += 1<<((n%10)*3), n /= 10;
	return ret;
}

long digit_idl(unsigned long n){
	long ret = 0;
	while(n) ret += 1LL<<((n%10)*6), n /= 10;
	return ret;
}



int is_palindrome(unsigned int num){
    int n = num, rev = 0;
	while (n) rev = rev*10 + (n%10), n /= 10;
	return num == rev;
}

int is_palindromel(unsigned long num){
	long n = num, rev = 0;
	while (n) rev = rev*10 + (n%10), n /= 10;
	return num == rev;
}



int reverse(unsigned int num){
	int n = num, rev = 0;
	while (n) rev = rev*10 + (n%10), n /= 10;
	return rev;
}

long reversel(unsigned long num){
	long n = num, rev = 0;
	while (n) rev = rev*10 + (n%10), n /= 10;
	return rev;
}



