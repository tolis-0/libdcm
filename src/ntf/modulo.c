#include <stdint.h>
#include "ntf.h"

uint64_t exp_mod (uint64_t base, uint64_t exp, uint64_t modulo) 
{
	uint64_t x = 1;

	for (base %= modulo; exp; exp >>= 1){
		if (exp & 1) x = ( x * base) % modulo;
		base = (base * base) % modulo;
	}

	return x;
}


uint64_t ext_mod (uint64_t base, uint64_t exp, uint64_t modulo) 
{
	uint64_t x = 1;

	for (base %= modulo; exp; exp >>= 1){
		if (exp & 1) x = (((unsigned __int128) x * base) % modulo);
		base = (((unsigned __int128) base * base) % modulo);
	}

	return x;
}


uint64_t mul_mod (uint64_t a, uint64_t b, uint64_t m) 
{
	return (uint64_t) (((unsigned __int128) a * b) % m);
}
