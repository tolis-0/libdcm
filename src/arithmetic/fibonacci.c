#include <stdint.h>
#include <math.h>
#include "dc_arithmetic.h"

static uint32_t dc_fib_ar[10] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};

/* Number of digits of nth Fibonacci number */
uint64_t dc_fib_digits (uint64_t n) {
	long double log10_fib;

	if (n < 7) return 1L;
	log10_fib = n*log10_phi - log10_sqrt5;

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
// currently works for low values of m
uint64_t dc_fib_mod (uint64_t n, uint64_t m)
{
	uint64_t k, f_n0, f_n1, utmp;
	int64_t stmp;
	int method[64], i;

	if (n < 10) return dc_fib_ar[n] % m;

	for (k = n/2, i = 0; k > 8; k /= 2, i++)
		method[i] = (k & 1);

	f_n0 = (dc_fib_ar[k] > m) ? (dc_fib_ar[k] % m) : dc_fib_ar[k];
	f_n1 = (dc_fib_ar[k+1] > m) ? (dc_fib_ar[k+1] % m) : dc_fib_ar[k+1];

	for (i--; i >= 0; i--) {
		if (method[i]) {
			utmp = ((2 * f_n0 + f_n1) * f_n1) % m;
			f_n0 = (f_n0 * f_n0 + f_n1 * f_n1) % m;
			f_n1 = utmp;
		} else {
			stmp = 2 * (int64_t) f_n1 - (int64_t) f_n0;
			stmp = (stmp * (int64_t) f_n0) % (int64_t) m;
			if (stmp < 0) stmp += m;
			f_n1 = (f_n0 * f_n0 + f_n1 * f_n1) % m;
			f_n0 = (uint64_t) stmp;
		}
	}

	if (n & 1) return (f_n0 * f_n0 + f_n1 * f_n1) % m;

	stmp = 2 * (int64_t) f_n1 - (int64_t) f_n0;
	stmp = (stmp * (int64_t) f_n0) % (int64_t) m;
	if (stmp < 0) stmp += m;
	return (uint64_t) stmp;
}