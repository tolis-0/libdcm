#ifndef _NTF_H
#define _NTF_H

#include <stdint.h>
#include <stddef.h>


/* ntf/primes.c */
int s3_prime (uint64_t n);
int mr_prime (uint64_t n);
int ef_prime (uint64_t n);
int mr_prime_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a);
int ext_mr_prime_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a);
int bpsw_prime (uint64_t n);

void er_sieve (int8_t *isprime, size_t limit);

uint64_t pcf_approx (uint64_t x);
int mobius_f (int N, int* isprime);
void mobius_setup (int *mobius, int limit, int *primes, int primes_size);
void rec_mob_setup(int *mobius, int limit, int num, int i, int *primes, int primes_size);



/* ntf/modulo.c */
uint64_t exp_mod (uint64_t base, uint64_t exp, uint64_t modulo);
uint64_t ext_mod (uint64_t base, uint64_t exp, uint64_t modulo);

#define mul_mod(a, b, m) (((unsigned __int128) (a) * (b)) % (m))



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

uint64_t gcd (uint64_t m, uint64_t n);


/* Malloc Macros */
#define malloc_sieve(is_prime, limit) \
	do { \
		is_prime = (int8_t *) malloc((limit)*sizeof(int8_t)); \
		er_sieve (is_prime, limit); \
	} while (0)


#define malloc_primes(is_prime, primes, N, limit) \
	do { \
		malloc_sieve(is_prime, limit); \
		primes = (typeof(primes)) malloc(pcf_approx(limit) * sizeof(*primes)); \
		N = 0; \
		for (typeof(*primes) i = 2; i < (limit); i++) \
			if (is_prime[i]) primes[N++] = i; \
	} while (0)


#define malloc_factor_table(is_prime, primes, tablem, N, limit) \
	do { \
		table = (uint32_t *) malloc((limit)*sizeof(uint32_t)); \
		factor_table(is_prime, limit, primes, N, table); \
	} while (0);



#endif // _NTF_H
