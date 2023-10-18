#ifndef _DC_ARITHMETIC_H
#define _DC_ARITHMETIC_H

#include <stdint.h>
#include <stddef.h>


/* ntf/primes.c */
int dc_prime (uint64_t n);
int dc_miller (uint64_t n);
int dc_mr_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a);
int32_t dc_find_jacobi (uint64_t n);
int dc_lucas_p1 (uint64_t n, uint64_t Q);
int dc_bpsw (uint64_t n);

void er_sieve (int8_t *isprime, size_t limit);

uint64_t dc_pcf_approx (uint64_t x);

int mobius_f (int N, int *isprime);
void mobius_setup (int *mobius, int limit, int *primes, int primes_size);
void rec_mob_setup(int *mobius, int limit, int num, int i, int *primes, int primes_size);



/* ntf/modulo.c */
uint64_t dc_exp_mod (uint64_t base, uint64_t exp, uint64_t n);
#define dc_mul_mod(a, b, m) dc_muladd_mod(a, b, 0, m)
uint64_t dc_muladd_mod (uint64_t a, uint64_t b, uint64_t c, uint64_t m);
uint64_t dc_add_mod(uint64_t a, uint64_t b, uint64_t m);
uint64_t dc_montgomery_mul_mod(uint64_t a, uint64_t b);
void dc_montgomery_cached (uint64_t n, uint64_t *x);



/* ntf/fibonacci.c*/
#define log10_sqrt5 	0.349485002168009402393130552637753487L
#define log10_phi   	0.208987640249978733769272089237555417L

uint64_t dc_fib_digits (uint64_t n);
uint64_t dc_pisano (uint64_t n);
uint64_t dc_fib_mod (uint64_t n, uint64_t m);



/* ntf/divisibility.c */
#define is_odd(x) ((x) & 1)
#define is_even(x) (is_odd(x) == 0)

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

#define dc_mul_div(m, d, a, b) \
	do { \
		if (a < 2 * b) { \
			m = a - b, d = 1; \
		} else { \
			m = a % b, d = a / b; \
		} \
	} while (0)

uint64_t gcd (uint64_t m, uint64_t n);
uint64_t ext_gcd (uint64_t a, uint64_t b, int64_t* s, int64_t* t);



/* Malloc Macros */
#define malloc_sieve(is_prime, limit) \
	do { \
		is_prime = (int8_t *) malloc((limit)*sizeof(int8_t)); \
		er_sieve (is_prime, limit); \
	} while (0)


#define malloc_primes(is_prime, primes, N, limit) \
	do { \
		malloc_sieve(is_prime, limit); \
		primes = (typeof(primes)) malloc(dc_pcf_approx(limit) * sizeof(*primes)); \
		N = 0; \
		for (typeof(*primes) i = 2; i < (limit); i++) \
			if (is_prime[i]) primes[N++] = i; \
	} while (0)


#define malloc_factor_table(is_prime, primes, tablem, N, limit) \
	do { \
		table = (uint32_t *) malloc((limit)*sizeof(uint32_t)); \
		factor_table(is_prime, limit, primes, N, table); \
	} while (0)



#endif // _DC_ARITHMETIC_H
