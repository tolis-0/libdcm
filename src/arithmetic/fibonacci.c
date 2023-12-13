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
	uint64_t f0, f1, tmp, mask;
	int arr_index;

	/*	Get result directly from array
		From now on we consider n >= 48 */
	if (n < 48) return dc_fib_ar[n] % m;

	if ((m & 1) && n > 0x1000)
		return dc_monfib_mod(n, m);

	/*	leading zeros (lz) are at most 58 because n > 32
		Mask would start at 2^(63-lz) for f0 = 0, f1 = 1
		But we skip 5 iterations by getting initial f0/f1 from array */
	arr_index = n >> (59 - __builtin_clzll(n));
	f0 = dc_fib_ar[arr_index] % m;
	f1 = dc_fib_ar[arr_index + 1] % m;
	mask = (1ULL << (58 - __builtin_clzll(n)));

	/*	Use the method for n & mask = 0
		And if it turns out that n & mask = 1
		do (f0, f1) <- (f1, f1 + f0) */
	if (m < 0x80000000) {
		for (; mask > 0; mask >>= 1) {
			tmp = ((2 * f1 + (m - f0)) * f0) % m;
			f1 = (f0 * f0 + f1 * f1) % m;
			f0 = (n & mask) ? f1 : tmp;
			f1 = (n & mask) ? f1 + tmp : f1;
			f1 = (f1 > m) ? f1 - m : f1;
		}
	}


	for (; mask > 0; mask >>= 1) {
		if (n & mask) {
			tmp = dc_radd_mod(dc_radd_mod(f0, f0, m), f1, m);
			tmp = dc_mul_mod(tmp, f1, m);
			f0 = dc_mul_mod(f0, f0, m);
			f0 = dc_muladd_mod(f1, f1, f0, m);
			f1 = tmp;
		} else {
			tmp = dc_radd_mod(dc_radd_mod(f1, f1, m), m - f0, m);
			tmp = dc_mul_mod(tmp, f0, m);
			f1 = dc_mul_mod(f1, f1, m);
			f1 = dc_muladd_mod(f0, f0, f1, m);
			f0 = tmp;
		}
	}

	return f0;
}


/*	Calculates nth Fibonacci number mod m with montgomery arithmetic
	Requires odd m */
uint64_t dc_monfib_mod (uint64_t n, uint64_t M)
{
	uint64_t f0, f1, tmp, tmp2, mask, Minv;

	Minv = dc_montgomery(64, M, &f0);
	f1 = f0;

	mask = (1ULL << (63 - __builtin_clzll(n))) >> 1;

	for (; mask > 0; mask >>= 1) {
		if (n & mask) {
			tmp = dc_radd_mod(f0, f0, M);
			tmp = dc_radd_mod(tmp, f1, M);
			tmp = dc_mul_redc_64(tmp, f1, M, Minv);
			tmp2 = dc_mul_redc_64(f0, f0, M, Minv);
			f0 = dc_mul_redc_64(f1, f1, M, Minv);
			f0 = dc_radd_mod(f0, tmp2, M);
			f1 = tmp;
		} else {
			tmp = dc_radd_mod(f1, f1, M);
			tmp = dc_radd_mod(tmp, M - f0, M);
			tmp = dc_mul_redc_64(tmp, f0, M, Minv);
			tmp2 = dc_mul_redc_64(f0, f0, M, Minv);
			f1 = dc_mul_redc_64(f1, f1, M, Minv);
			f1 = dc_radd_mod(f1, tmp2, M);
			f0 = tmp;
		}
	}

	return dc_mul_redc_64(f0, 1ULL, M, Minv);
}
