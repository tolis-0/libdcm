#include <stdint.h>
#include "ntf.h"

uint64_t exp_mod (uint64_t base, uint64_t exp, uint64_t modulo) 
{
	uint64_t x = 1;

	for (base %= modulo; exp; exp >>= 1){
		if (exp & 1) x = (x * base) % modulo;
		base = (base * base) % modulo;
	}

	return x;
}


uint64_t ext_mod (uint64_t base, uint64_t exp, uint64_t modulo) 
{
	uint64_t x = 1;

	for(base %= modulo; exp; exp >>= 1){
		if (exp & 1) x = mul_mod(x, base, modulo);
		base = mul_mod(base, base, modulo);
	}

	return x;
}


uint64_t mul_mod (uint64_t a, uint64_t b, uint64_t m) 
{
	long double x;
	uint64_t c;
	int64_t r;
	if (a >= m) a %= m;
	if (b >= m) b %= m;
	x = a;
	c = x * b / m;
	r = (int64_t) (a * b - c * m) % (int64_t) m;
	if (r < 0) return r + m; 
	return r;
}
