#include <stdint.h>
#include <math.h>
#include "dc_arithmetic.h"
#include "dc_montgomery.h"


static const uint32_t dc_fib_ar[48] = {0, 1, 1, 2, 3, 5, 8, 13,
	21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765,
	10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811,
	514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465,
	14930352, 24157817, 39088169, 63245986, 102334155, 165580141,
	267914296, 433494437, 701408733, 1134903170, 1836311903, 2971215073
};


/*	Number of digits of nth Fibonacci number */
uint64_t dc_fib_digits (uint64_t n) {
	long double log10_fib;

	if (n < 7) return 1L;
	log10_fib = n * dc_log10_phi - dc_log10_sqrt5;

	return (uint64_t) ceill(log10_fib);
}


/*	Pisano period of nth Fibonacci number */
uint64_t dc_pisano (uint64_t n) {
	uint64_t i, fib1, fib2, fib3;

	if (n == 1) return 1;
	fib1 = 0, fib2 = 1;

	for (i = 1;; i++) {
		fib3 = (fib1 + fib2) % n;
		if (fib2 == 0 && fib3 == 1) break;
		fib1 = fib2;
		fib2 = fib3;
	}

	return i;
}


/*	nth Fibonacci number mod m */
uint64_t dc_fib_mod (uint64_t n, uint64_t m)
{
	uint64_t e, mask, t_inv, k, k_inv, r, neg;
	uint64_t a_mont, b_mont, c_mont, a, b, c, ret;

	if (n < 2) return n % m;

	// m = t*k with k odd and t=2^e
	e = __builtin_ctzll(m);
	k = m >> e;
	mask = (1ull << e) - 1ull;

	r = (-k) % k;
	k_inv = dc_modinv_2pow64(k);
	neg = k - r; // -1 in montgomery form

	unsigned __int128 _t = (unsigned __int128) k * k_inv + 1;
	_t >>= e;
	t_inv = (uint64_t) (_t % k);

	c_mont = dc_radd_mod(r, r, k);
	c_mont = dc_radd_mod(r, c_mont, k);
	a_mont = (n & 1ull) ? r : 0ull;
	b_mont = (n & 1ull) ? neg : r;

	c = 3ull;
	a = (n & 1ull) ? 1ull : 0ull;
	b = (n & 1ull) ? -1ull : 1ull;

	// becomes -2 in montgomery form
	neg = dc_radd_mod(neg, neg, k);

	for (n >>= 1; n > 1ull; n >>= 1) {
		if (n & 1ull) {
			a = b + a*c;
			a_mont = dc_mul_redc_64(a_mont, c_mont, k, k_inv);
			a_mont = dc_radd_mod(b_mont, a_mont, k);
		} else {
			b = a + b*c;
			b_mont = dc_mul_redc_64(b_mont, c_mont, k, k_inv);
			b_mont = dc_radd_mod(a_mont, b_mont, k);
		}
		c = c*c - 2ull;
		c_mont = dc_mul_redc_64(c_mont, c_mont, k, k_inv);
		c_mont = dc_radd_mod(c_mont, neg, k);
	}

	a = (b + a*c) & mask;
	a_mont = dc_mul_redc_64(a_mont, c_mont, k, k_inv);
	a_mont = dc_radd_mod(b_mont, a_mont, k);

	ret = dc_mul_redc_64(a_mont, 1ull, k, k_inv);
	__int128 res = (((__int128)ret - (__int128)a) * t_inv) % (__int128) k;
	if (res < 0) res += (__int128)k;
	ret = res;

	return a + (ret << e);
}
