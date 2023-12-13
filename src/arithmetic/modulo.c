#include <stdint.h>
#include "dc_arithmetic.h"
#include "dc_montgomery.h"

#define MONEXP_USE_32BIT 1



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



/* Modular Exponentiation (base ^ exp) % m */
uint64_t dc_exp_mod (uint64_t base, uint64_t exp, uint64_t m)
{
	uint64_t x;

	if (m == 1) return 0;
	if (m & 1) return dc_monexp_mod(base, exp, m);

	if (m < 0x100000000) {
		for (x = 1, base %= m; exp != 0; exp >>= 1){
			if (exp & 1) x = (x * base) % m;
			base = (base * base) % m;
		}

		return x;
	}

	for (x = 1, base %= m; exp > 0; exp >>= 1){
		if (exp & 1) x = dc_mul_mod(x, base, m);
		base = dc_mul_mod(base, base, m);
	}

	return x;
}



/*	Montgomery Modular Exponentiation */
uint64_t dc_monexp_mod (uint64_t base, uint64_t exp, uint64_t m)
{
	uint64_t x, n_inv;

#if MONEXP_USE_32BIT == 1
	if (m < 0x100000000) {
		uint32_t b, x_32, n_inv;

		n_inv = dc_montgomery(32, m, &x);
		x_32 = x;
		b = dc_mul_mod(base, x, m);

		for (; exp > 0; exp >>= 1) {
			if (exp & 1) x_32 = dc_mul_redc_32(x_32, b, m, n_inv);
			b = dc_mul_redc_32(b, b, m, n_inv);
		}

		x_32 = dc_mul_redc_32(x_32, 1U, m, n_inv);

		return x_32;
	}
#endif

	n_inv = dc_montgomery(64, m, &x);
	base = dc_mul_mod(base, x, m);

	for (; exp > 0; exp >>= 1) {
		if (exp & 1) x = dc_mul_redc_64(x, base, m, n_inv);
		base = dc_mul_redc_64(base, base, m, n_inv);
	}

	x = dc_mul_redc_64(x, 1ULL, m, n_inv);

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
