#include <stdint.h>
#include <math.h>
#include "dc_arithmetic.h"


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

/* nth Fibonacci number mod m*/
uint64_t dc_fib_mod (uint64_t n, uint64_t m) {
	
	// TODO
	
	return 0;
}
