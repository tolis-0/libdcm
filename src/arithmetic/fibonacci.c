#include <stdint.h>
#include <math.h>
#include "dc_arithmetic.h"


static const uint32_t dc_fib_ar[48] = {0, 1, 1, 2, 3, 5, 8, 13,
	21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765,
	10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811,
	514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465,
	14930352, 24157817, 39088169, 63245986, 102334155, 165580141,
	267914296, 433494437, 701408733, 1134903170, 1836311903, 2971215073
};


/* Number of digits of nth Fibonacci number */
uint64_t dc_fib_digits (uint64_t n) {
	long double log10_fib;

	if (n < 7) return 1L;
	log10_fib = n * dc_log10_phi - dc_log10_sqrt5;

	return (uint64_t) ceill(log10_fib);
}


/* Pisano period of nth Fibonacci number */
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


/* nth Fibonacci number mod m */
uint64_t dc_fib_mod (uint64_t n, uint64_t m)
{
	uint64_t k, f_n0, f_n1, tmp, tmp2;
	int method[64], i;

	if (n < 48) return dc_fib_ar[n] % m;

	for (k = n/2, i = 0; k > 46; k /= 2, i++) method[i] = (k & 1);

	f_n0 = (dc_fib_ar[k] > m) ? (dc_fib_ar[k] % m) : dc_fib_ar[k];
	f_n1 = (dc_fib_ar[k+1] > m) ? (dc_fib_ar[k+1] % m) : dc_fib_ar[k+1];

	if (m < 0x80000000) {
		for (i--; i >= 0; i--) {
			if (method[i]) {
				tmp = ((2 * f_n0 + f_n1) * f_n1) % m;
				f_n0 = (f_n0 * f_n0 + f_n1 * f_n1) % m;
				f_n1 = tmp;
			} else {
				tmp = ((2 * f_n1 + (m - f_n0)) * f_n0) % m;
				f_n1 = (f_n0 * f_n0 + f_n1 * f_n1) % m;
				f_n0 = tmp;
			}
		}

		if (n & 1) return (f_n0 * f_n0 + f_n1 * f_n1) % m;
		return ((2 * f_n1 + (m - f_n0)) * f_n0) % m;
	}

	if ((m & 1) == 0 || n < 0x10000) {
		for (i--; i >= 0; i--) {
			if (method[i]) {
				tmp = dc_radd_mod(dc_radd_mod(f_n0, f_n0, m), f_n1, m);
				tmp = dc_mul_mod(tmp, f_n1, m);
				f_n0 = dc_mul_mod(f_n0, f_n0, m);
				f_n0 = dc_muladd_mod(f_n1, f_n1, f_n0, m);
				f_n1 = tmp;
			} else {
				tmp = dc_radd_mod(dc_radd_mod(f_n1, f_n1, m), m - f_n0, m);
				tmp = dc_mul_mod(tmp, f_n0, m);
				f_n1 = dc_mul_mod(f_n1, f_n1, m);
				f_n1 = dc_muladd_mod(f_n0, f_n0, f_n1, m);
				f_n0 = tmp;
			}
		}

		if (n & 1) {
			tmp = dc_mul_mod(f_n0, f_n0, m);
			f_n0 = dc_muladd_mod(f_n1, f_n1, tmp, m);
		} else {
			tmp = dc_radd_mod(dc_radd_mod(f_n1, f_n1, m), m - f_n0, m);
			f_n0 = dc_mul_mod(tmp, f_n0, m);
		}

		return f_n0;
	}

	dc_montgomery_cached(m, &tmp);
	f_n0 = dc_mul_mod(f_n0, tmp, m);
	f_n1 = dc_mul_mod(f_n1, tmp, m);

	for (i--; i >= 0; i--) {
		if (method[i]) {
			tmp = dc_radd_mod(f_n0, f_n0, m);
			tmp = dc_radd_mod(tmp, f_n1, m);
			tmp = dc_redc_64bit(tmp, f_n1);
			tmp2 = dc_redc_64bit(f_n0, f_n0);
			f_n0 = dc_redc_64bit(f_n1, f_n1);
			f_n0 = dc_radd_mod(f_n0, tmp2, m);
			f_n1 = tmp;
		} else {
			tmp = dc_radd_mod(f_n1, f_n1, m);
			tmp = dc_radd_mod(tmp, m - f_n0, m);
			tmp = dc_redc_64bit(tmp, f_n0);
			tmp2 = dc_redc_64bit(f_n0, f_n0);
			f_n1 = dc_redc_64bit(f_n1, f_n1);
			f_n1 = dc_radd_mod(f_n1, tmp2, m);
			f_n0 = tmp;
		}
	}

	if (n & 1) {
		f_n1 = dc_redc_64bit(f_n1, f_n1);
		f_n0 = dc_redc_64bit(f_n0, f_n0);
		f_n0 = dc_radd_mod(f_n0, f_n1, m);
	} else {
		tmp = dc_radd_mod(f_n1, f_n1, m);
		tmp = dc_radd_mod(tmp, m - f_n0, m);
		f_n0 = dc_redc_64bit(tmp, f_n0);
	}

	return dc_redc_64bit(f_n0, 1);
}
