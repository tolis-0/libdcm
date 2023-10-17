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
int mobius_f (int N, int* isprime);
void mobius_setup (int *mobius, int limit, int *primes, int primes_size);
void rec_mob_setup(int *mobius, int limit, int num, int i, int *primes, int primes_size);



/* ntf/modulo.c */
uint64_t dc_exp_mod (uint64_t base, uint64_t exp, uint64_t n);

#define mul_mod(a, b, m) mul_modadd(a, b, 0, m)
#define mul_modadd(a, b, c, m) \
	(((unsigned __int128) (a) * (b) + (c)) % (uint64_t) (m))

#define add_mod(rem, a, b, m) \
	do { \
		unsigned __int128 tmp128; \
		tmp128 = (unsigned __int128) (a) + (b); \
		if (tmp128 >> 64) { \
			rem = tmp128 - m; \
		} else { \
			rem = tmp128; \
			if (rem > m) rem -= m; \
		} \
	} while (0)

#ifdef __x86_64__
/* rem = (a * b + d) % m */
#define fast_mul_mod(rem, a, b, m) fast_muladd_mod(rem, a, b, 0, m)

#define fast_muladd_mod(rem, a, b, d, m) \
	do { \
		unsigned __int128 c; \
		uint64_t result, low, high; \
		c = (unsigned __int128) ((a) > m ? ((a) % m) : (a)) * \
			((b) > m ? ((b) % m) : (b)) + (d); \
		high = c >> 64; \
		low = c; \
		if (high == 0) { \
			if (low >= m) rem = low % m; \
			else rem = low; \
		} else { \
			__asm__("divq %[v]" \
				: "=a"(result), "=d"(rem) \
				: [v] "r"(m), "a"(low), "d"(high)); \
		} \
	} while (0)

#else
#define fast_mul_mod(rem, a, b, m) rem = mul_mod(a, b, m)
#define fast_muladd_mod(rem, a, b, d, m) rem = mul_modadd(a, b, d, m)
#endif

#define montgomery_mul_mod(rem, a, b, rbit, r_1, n, n_) \
	do { \
		unsigned __int128 t, m; \
		t = (unsigned __int128) (a) * (b); \
		m = ((t & (r_1)) * (n_)) & (r_1); \
		rem = (t + m * (n)) >> (rbit); \
		if (rem >= (n)) rem -= (n); \
	} while (0)

#define montgomery_mul_mod_bit64(rem, a, b, n, n_) \
	do { \
		unsigned __int128 t, mn, rem128; \
		uint64_t m, t_0; \
		t = (unsigned __int128) (a) * (b); \
		m = (((t & 0xFFFFFFFFFFFFFFFF) * n_) & 0xFFFFFFFFFFFFFFFF); \
		mn = (unsigned __int128) m * (n); \
		t_0 = (t & 1); \
		t >>= 1, mn >>= 1; \
		rem128 = (t + mn) >> 63; \
		if (t_0) rem128++; \
		t_0 = rem128 >> 64; \
		if (t_0) rem = rem128 - n; \
		else { \
			rem = rem128; \
			if (rem >= (n)) rem -= (n); \
		} \
	} while (0)

void montgomery_cached (uint64_t n, uint64_t *un_i, uint64_t *rbit);



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

#define quick_mul_div(m, d, a, b) \
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
