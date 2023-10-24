#include <stdint.h>
#include "dc_arithmetic.h"


uint16_t factoring_ft (uint32_t n, factor_i *factors, uint32_t *table) 
{
	uint16_t no_pf;	// number of prime factors
	uint32_t factor, new_factor, rem_n;

	factor = table[n];
	factors[0].prime = factor;
	factors[0].exp = 1;

	if (n == factor) return 1;
	rem_n = n/factor;
	no_pf = 0;

	while (rem_n > 1) {
		new_factor = table[rem_n];
		
		if (new_factor == factor) {
			factors[no_pf].exp++;
		} else {
			no_pf++;
			factors[no_pf].prime = new_factor;
			factors[no_pf].exp = 1;
			factor = new_factor;
		}

		rem_n = n/factor;
	}

	return no_pf + 1;
}


uint64_t gcd (uint64_t a, uint64_t b)
{
	uint64_t rem;

	while (b) {
		rem = a % b;
		a = b;
		b = rem;
	}

	return a;
}


uint64_t fast_ext_gcd (uint64_t a, uint64_t b, int64_t* s, int64_t* t) {
	uint64_t a2, a3, c0, c1, g;

	dc_mul_div(a2, c0, a, b);

	if (a2 < 1) {
		s[0] = 1;
		t[0] = 0;
		return b;
	}

	dc_mul_div(a3, c1, b, a2);

	if (a3 < 1) {
		s[0] = -c0;
		t[0] = 1;
		return a2;
	}

	g = fast_ext_gcd (a2, a3, s, t);
	t[0] -= c1 * s[0];
	s[0] -= c0 * t[0];

	return g;
}


uint64_t ext_gcd (uint64_t a, uint64_t b, int64_t* s, int64_t* t)
{
	if (a == 0) {
		s[0] = 0;
		if (b == 0) t[0] = 0;
		else t[0] = 1;
		return b;
	}

	if (b == 0) {
		s[0] = 1, t[0] = 0;
		return a;
	}

	if (a > b) return fast_ext_gcd(a, b, t, s);
	else return fast_ext_gcd(b, a, s, t);
}
