#include <stdint.h>
#include <math.h>
#include "dc_arithmetic.h"

static uint32_t dc_fib_ar[10] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};

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

	if (n < 10) return dc_fib_ar[n] % m;

	for (k = n/2, i = 0; k > 8; k /= 2, i++) method[i] = (k & 1);

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
				tmp = dc_add_mod(dc_add_mod(f_n0, f_n0, m), f_n1, m);
				tmp = dc_mul_mod(tmp, f_n1, m);
				f_n0 = dc_mul_mod(f_n0, f_n0, m);
				f_n0 = dc_add_mod(dc_mul_mod(f_n1, f_n1, m), f_n0, m);
				f_n1 = tmp;
			} else {
				tmp = dc_add_mod(dc_add_mod(f_n1, f_n1, m), m - f_n0, m);
				tmp = dc_mul_mod(tmp, f_n0, m);
				f_n1 = dc_mul_mod(f_n1, f_n1, m);
				f_n1 = dc_add_mod(dc_mul_mod(f_n0, f_n0, m), f_n1, m);
				f_n0 = tmp;
			}
		}

		if (n & 1) {
			tmp = dc_mul_mod(f_n0, f_n0, m);
			f_n0 = dc_add_mod(dc_mul_mod(f_n1, f_n1, m), tmp, m);
		} else {
			tmp = dc_add_mod(dc_add_mod(f_n1, f_n1, m), m - f_n0, m);
			f_n0 = dc_mul_mod(tmp, f_n0, m);
		}

		return f_n0;
	}

	dc_montgomery_cached(m, &tmp);
	f_n0 = dc_mul_mod(f_n0, tmp, m);
	f_n1 = dc_mul_mod(f_n1, tmp, m);

	for (i--; i >= 0; i--) {
		if (method[i]) {
			tmp = dc_add_mod(f_n0, f_n0, m);
			tmp = dc_add_mod(tmp, f_n1, m);
			tmp = dc_montgomery_mul_mod(tmp, f_n1);
			tmp2 = dc_montgomery_mul_mod(f_n0, f_n0);
			f_n0 = dc_montgomery_mul_mod(f_n1, f_n1);
			f_n0 = dc_add_mod(f_n0, tmp2, m);
			f_n1 = tmp;
		} else {
			tmp = dc_add_mod(f_n1, f_n1, m);
			tmp = dc_add_mod(tmp, m - f_n0, m);
			tmp = dc_montgomery_mul_mod(tmp, f_n0);
			tmp2 = dc_montgomery_mul_mod(f_n0, f_n0);
			f_n1 = dc_montgomery_mul_mod(f_n1, f_n1);
			f_n1 = dc_add_mod(f_n1, tmp2, m);
			f_n0 = tmp;
		}
	}

	if (n & 1) {
		f_n1 = dc_montgomery_mul_mod(f_n1, f_n1);
		f_n0 = dc_montgomery_mul_mod(f_n0, f_n0);
		f_n0 = dc_add_mod(f_n0, f_n1, m);
	} else {
		tmp = dc_add_mod(f_n1, f_n1, m);
		tmp = dc_add_mod(tmp, m - f_n0, m);
		f_n0 = dc_montgomery_mul_mod(tmp, f_n0);
	}

	return dc_montgomery_mul_mod(f_n0, 1);
}
