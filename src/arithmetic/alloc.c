#include <string.h>
#include <stdlib.h>
#include "dc_arithmetic.h"


static int8_t   *dc_sieve_ar = NULL;
static size_t    dc_sieve_size = 0;
static uint32_t *dc_prime_ar = NULL;
static size_t    dc_prime_size = 0;
static uint32_t *dc_factor_ar = NULL;
static size_t    dc_factor_size = 0;


/* Allocates an array with the characteristic function of primes */
int8_t *dc_alloc_sieve (size_t limit)
{
	size_t i, j;

	dc_sieve_ar = (int8_t *) malloc(limit * sizeof(int8_t));

	dc_sieve_ar[0] = 0;
	dc_sieve_ar[1] = 0;
	memset(dc_sieve_ar + 2, 1, limit - 2);

	for (i = 2; i * i < limit; i++) {
		if (!dc_sieve_ar[i]) continue;

		for (j = i * i; j <= limit; j += i)
			dc_sieve_ar[j] = 0;
	}

	dc_sieve_size = limit;
	return dc_sieve_ar;
}


void dc_free_sieve ()
{
	free(dc_sieve_ar);
	dc_sieve_ar = NULL;
	dc_sieve_size = 0;
}


/* Allocates an array with the prime numbers up to size */
uint32_t *dc_alloc_primes (size_t *size)
{
	size_t i, j;

	if (dc_sieve_ar == NULL) {
		if (size == NULL || size[0] == 0) return NULL;

		dc_alloc_sieve(dc_primef_approx(size[0]));
		dc_sieve_ar = (int8_t *) malloc(size[0] * sizeof(int8_t));

		for (j = 0, i = 2; j < size[0]; i++)
			if (dc_sieve_ar[i]) dc_prime_ar[j++] = i;

		dc_free_sieve();
	} else {
		dc_prime_ar = (uint32_t *) malloc(
			dc_pcf_approx(dc_sieve_size) * sizeof(uint32_t));

		for (j = 0, i = 2; i < dc_sieve_size; i++)
			if (dc_sieve_ar[i]) dc_prime_ar[j++] = i;

		size[0] = dc_prime_size = j;

		dc_prime_ar = (uint32_t *) realloc (
			dc_prime_ar, dc_prime_size * (sizeof(uint32_t)));
	}

	return dc_prime_ar;
}


void dc_free_primes ()
{
	free(dc_prime_ar);
	dc_prime_ar = NULL;
	dc_prime_size = 0;
}


/* 	Allocates a table with the smallest factor of each number.
    Use simple division to get the rest                        */
uint32_t *dc_alloc_factors (size_t limit)
{
	size_t i, j;

	dc_factor_ar = (uint32_t *) malloc(limit * sizeof(uint32_t));

	memset(dc_factor_ar, 0, limit * sizeof(uint32_t));

	for (i = 2; i * i < limit; i++) {
		if (dc_factor_ar[i] > 0) continue;
		dc_factor_ar[i] = i;

		for (j = i * i; j <= limit; j += i)
			if (dc_factor_ar[j] == 0) dc_factor_ar[j] = i;
	}

	dc_factor_size = limit;
	return dc_factor_ar;
}


void dc_free_factors ()
{
	free(dc_factor_ar);
	dc_factor_ar = NULL;
	dc_factor_size = 0;
}
