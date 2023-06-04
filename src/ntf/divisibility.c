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

uint64_t gcd (uint64_t m, uint64_t n) {
    uint64_t rem;

    while (n) {
        rem = m % n;
        m = n;
        n = rem;
    }

    return m;
}