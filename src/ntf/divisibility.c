#include <stdint.h>
#include "ntf.h"


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

int factor_table (int *isprime, uint32_t limit, uint32_t *primes, uint32_t N, uint32_t *table) 
{
	uint32_t i, j, p;

	table[0] = 0, table[1] = 1;

	for (i = 2; i < limit; i++) {
		if (isprime[i]) {
			table[i] = i;
			continue;
		}

		for (j = 0; j < N; j++) {
			p = primes[j];
			if (i % p == 0) {
				table[i] = p;
				break;
			}
		}

		if (j == N) return 1;
	}
	return 0;
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

uint64_t ext_gcd (uint64_t a, uint64_t b, int64_t* s, int64_t* t)
{
	uint64_t q, old_r, new_r;
	int64_t old_s, new_s, tmp;

	new_s = 0, old_s = 1, new_r = b, old_r = a;

	while (new_r) {
		q = old_r / new_r;
		tmp = new_r;
		new_r = old_r - q * new_r;
		old_r = tmp;

		tmp = new_s;
		new_s = old_s - q * new_s;
		old_s = tmp;
	}

	if (b) {
		if (a > 4294967294 || b > 4294967294) {
			__int128 tmp = (__int128) old_r - old_s * (__int128) a;
			t[0] = tmp / b;
		} else {
			tmp = (int64_t) old_r - old_s * (int64_t) a;
			t[0] = tmp / (int64_t) b;
		}
	} else {
		t[0] = 0;
	}

	s[0] = old_s;

	return old_r;
}
