#include <string.h>
#include <stdlib.h>
#include "dc_arithmetic.h"

/* Allocates an array with the characteristic function of primes */
int8_t *dc_alloc_sieve (size_t limit)
{
	int8_t *is_prime;
	size_t i, j;

	is_prime = (int8_t *) malloc(limit * sizeof(int8_t));

	is_prime[0] = 0;
	is_prime[1] = 0;
	memset(is_prime + 2, 1, limit - 2);

	for (i = 2; i * i < limit; i++) {
		if (!is_prime[i]) continue;

		for (j = i * i; j <= limit; j += i)
			is_prime[j] = 0;
	}

	return is_prime;
}