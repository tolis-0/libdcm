#include <stdint.h>
#include "ntf.h"

uint64_t exp_mod (uint64_t base, uint64_t exp, uint64_t modulo) 
{
	uint64_t x = 1;

	for (base %= modulo; exp != 0; exp >>= 1){
		if (exp & 1) x = ( x * base) % modulo;
		base = (base * base) % modulo;
	}

	return x;
}


uint64_t ext_mod (uint64_t base, uint64_t exp, uint64_t n) 
{
	uint64_t x, rbit, r_1, un_i;
	int64_t tmp, n_i;
	
	r_1 = 0x8000000000000000, rbit = 63;
	while ((r_1 & n) == 0) rbit--, r_1 >>= 1;
	rbit++;

	if (r_1 == 0x8000000000000000) {
		x = -n;
		fast_mul_mod(base, base, x, n);
		ext_gcd(n, x, &n_i, &tmp);
		un_i = tmp - n_i;

		for (; exp != 0; exp >>= 1) {
			if (exp & 1)
				montgomery_mul_mod_bit64(x, x, base, n, un_i);
			montgomery_mul_mod_bit64(base, base, base, n, un_i);
		}

		montgomery_mul_mod_bit64(x, x, 1, n, un_i);
	} else {
		r_1 <<= 1;
		x = r_1 - n;
		fast_mul_mod(base, base, x, n);
		ext_gcd(r_1, n, &tmp, &n_i);
		if (n_i < 0) un_i = - n_i; else un_i = r_1 - n_i;
		r_1--;

		for (; exp != 0; exp >>= 1) {
			if (exp & 1)
				montgomery_mul_mod(x, x, base, rbit, r_1, n, un_i);
			montgomery_mul_mod(base, base, base, rbit, r_1, n, un_i);
		}

		montgomery_mul_mod(x, x, 1, rbit, r_1, n, un_i);
	}

	return x;
}
