#include <stdint.h>
#include "dc_arithmetic.h"


/* (a * b + c) % m */
uint64_t dc_muladd_mod (uint64_t a, uint64_t b, uint64_t c, uint64_t m)
{
	unsigned __int128 full;
	uint64_t rem;

	if (m <= 0x100000000)
		return ((a > m ? (a % m) : a) *
				(b > m ? (b % m) : b) +
				(c > 0x1FFFFFFFF ? (c % m) : c)) % m;

	full = (unsigned __int128) a * b + c;
	rem = (uint64_t) (full % m);

	return rem;
}


/* (a + b) % m */
uint64_t dc_add_mod (uint64_t a, uint64_t b, uint64_t m)
{
	uint64_t rem, high_bit;
	unsigned __int128 tmp128;

	if (m < 0x8000000000000000) {
		rem = (a >= m ? (a % m) : a)
			+ (b >= m ? (b % m) : b);
		if (rem >= m) rem -= m;
	} else {
		tmp128 = (unsigned __int128) (a >= m ? (a % m) : a) +
			(b >= m ? (b % m) : b);
		high_bit = tmp128 >> 64;
		if (high_bit > 0) {
			rem = (uint64_t) (tmp128 - m);
		} else {
			rem = (uint64_t) tmp128;
			if (rem > m) rem -= m;
		}
	}

	return rem;
}


/* (a + b) % m, 0 <= a < m, 0 <= b < m */
uint64_t dc_radd_mod (uint64_t a, uint64_t b, uint64_t m)
{
	uint64_t rem;
	int overflow;

	if (m < 0x8000000000000000) {
		rem = a + b;
		if (rem >= m) rem -= m;
	} else {
		overflow = __builtin_add_overflow(a, b, &rem);
		if (overflow || rem >= m) rem -= m;
	}

	return rem;
}


/* (a ^ b) % m */
uint64_t dc_exp_mod (uint64_t base, uint64_t exp, uint64_t m)
{
	uint64_t x;

	if (m <= 0x100000000) {
		if (m == 1) return 0;

		for (x = 1, base %= m; exp != 0; exp >>= 1){
			if (exp & 1) x = (x * base) % m;
			base = (base * base) % m;
		}

		return x;
	}

	if ((m & 1) == 0) {
		for (x = 1, base %= m; exp > 0; exp >>= 1){
			if (exp & 1) x = dc_mul_mod(x, base, m);
			base = dc_mul_mod(base, base, m);
		}

		return x;
	}

	dc_montgomery_cached(m, &x);
	base = dc_mul_mod(base, x, m);

	for (; exp > 0; exp >>= 1) {
#ifdef _dc_arch_x86_64
		if (exp & 1) base = dc_montgomery_dmul_mod(&x, base);
		else base = dc_montgomery_mul_mod(base, base);
#else
		if (exp & 1) x = dc_montgomery_mul_mod(x, base);
		base = dc_montgomery_mul_mod(base, base);
#endif
	}

	x = dc_montgomery_mul_mod(x, 1);

	return x;
}


/* (2 ^ b) % m */
uint64_t dc_2exp_mod (uint64_t exp, uint64_t m)
{
	uint64_t n, k;

	n = 0;
	k = 1;

	while (exp > 1) {
		if (exp & 1) {
			exp--;
			n += k;
		} else {
			if (k == 32) break;
			exp >>= 1;
			k <<= 1;
		}
	}

	/* (2^n)*(2^k)^exp mod m */
	if (exp == 1) return dc_mul_mod (1ULL << n, 1ULL << k, m);
	return dc_mul_mod (1ULL << n, dc_exp_mod(1ULL << k, exp, m), m);
}
