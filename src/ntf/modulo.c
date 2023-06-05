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
		if (exp & 1) x = mul_mod(x, base, modulo);
		base = mul_mod(base, base, modulo);
	}

	return x;
}

