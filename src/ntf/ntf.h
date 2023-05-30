#ifndef _NTF_H
#define _NTF_H

#ifndef _STDINT_H
#include "stdint.h"
#endif

#ifndef _MATH_H
#include "math.h"
#endif

/* ntf/primes.c */
int s3_prime (uint64_t n);
int mr_prime (uint64_t n);
int ef_prime (uint64_t n);
int mr_prime_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a);
int ext_mr_prime_test(uint64_t n, uint64_t d, uint32_t s, uint32_t a);

uint64_t exp_mod (uint64_t base, uint64_t exp, uint64_t modulo);
uint64_t ext_mod (uint64_t base, uint64_t exp, uint64_t modulo);
uint64_t mul_mod (uint64_t a, uint64_t b, uint64_t m);

void er_sieve (int *isprime, uint32_t limit);

uint64_t pcf_approx (uint64_t x);
int mobius_f (int N, int* isprime);
void mobius_setup (int *mobius, int limit, int *primes, int primes_size);
void rec_mob_setup(int *mobius, int limit, int num, int i, int *primes, int primes_size);




/* ntf/fibonacci.c*/
#define log10_sqrt5 	0.349485002168009402393130552637753487L
#define log10_phi   	0.208987640249978733769272089237555417L

uint64_t digits_fib (uint64_t n);
uint32_t pisano (uint64_t n);
uint64_t fib_mod (uint64_t n, uint64_t modulo);


/* ntf/divisibility.c */
#define max_factors_i 9
typedef struct {
	uint32_t prime;
	uint16_t exp;
} factor_i;

#define max_factors_l 15
typedef struct {
	uint64_t prime;
	uint16_t exp;
} factor_l;

uint16_t factoring_ft (uint32_t n, factor_i *factors, uint32_t *table);

int factor_table (int *isprime, uint32_t limit, uint32_t *primes, uint32_t N, uint32_t *table);


/* Malloc Macros */

#define malloc_sieve(IS_PRIME, LIMIT) \
	IS_PRIME = (int *) malloc((LIMIT)*sizeof(int)); \
	er_sieve (IS_PRIME, LIMIT);


#define malloc_primes(IS_PRIME, TYPE_1, PRIMES, TYPE_2, N, LIMIT) \
	malloc_sieve(IS_PRIME, LIMIT); \
	PRIMES = (TYPE_2 *) malloc(pcf_approx(LIMIT) * sizeof(TYPE_2)); \
	N = 0; \
	for (TYPE_2 p_alloc_i = 2; p_alloc_i <= LIM; p_alloc_i++) \
		if (IS_PRIME[p_alloc_i]) PRIMES[N++] = p_alloc_i;


#define malloc_primes_i(IS_PRIME, PRIMES, N, LIMIT) \
	malloc_primes(IS_PRIME, uint32_t, PRIMES, uint32_t, N, LIMIT)


#define malloc_factor_table(IS_PRIME, LIMIT, PRIMES, N, TABLE) \
	TABLE = (uint32_t *) malloc((LIMIT)*sizeof(uint32_t)); \
	factor_table(IS_PRIME, LIMIT, PRIMES, N, TABLE);


#endif // _NTF_H
