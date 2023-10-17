#include <stdint.h>
#include <math.h>
#include "dc_arithmetic.h"

uint64_t digits_fib (uint64_t n) {
	long double log10_fib;

	if (n < 7) return 1L;
	log10_fib = n*log10_phi - log10_sqrt5;

	return (uint64_t) ceill(log10_fib);
}

uint32_t pisano (uint64_t n) {
	uint64_t fib1, fib2, fib3;
	uint32_t i;

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

uint64_t fib_mod (uint64_t n, uint64_t modulo) {
	
	// TODO
	
	return 0;
}
