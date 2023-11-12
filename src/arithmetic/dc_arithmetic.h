#ifndef _DC_ARITHMETIC_H
#define _DC_ARITHMETIC_H

#include <stdint.h>
#include <stddef.h>


/* arithmetic/primes */
int dc_prime (uint64_t n);
int dc_likely_prime (uint64_t n);
int dc_miller (uint64_t n);
int dc_mr_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a);
int32_t dc_find_jacobi (uint64_t n);
int dc_lucas_p1 (uint64_t n, uint64_t Q);
int dc_bpsw (uint64_t n);
int dc_selfridge_conjecture (uint64_t n);


/* arithmetic/ntf */
uint64_t dc_pcf_approx (uint64_t n);
uint64_t dc_primef_approx (uint64_t n);
uint64_t dc_sqrt (uint64_t n);



/* arithmetic/modulo */
uint64_t dc_exp_mod (uint64_t base, uint64_t exp, uint64_t n);
uint64_t dc_2exp_mod (uint64_t exp, uint64_t m);
#define dc_mul_mod(a, b, m) dc_muladd_mod(a, b, 0, m)
uint64_t dc_muladd_mod (uint64_t a, uint64_t b, uint64_t c, uint64_t m);
uint64_t dc_add_mod (uint64_t a, uint64_t b, uint64_t m);
uint64_t dc_radd_mod (uint64_t a, uint64_t b, uint64_t m);



/* arithmetic/montgomery */
uint64_t dc_montgomery_mul_mod (uint64_t a, uint64_t b);
void dc_montgomery_cached (uint64_t n, uint64_t *x);



/* arithmetic/fibonacci */
#define dc_log10_sqrt5 	0.349485002168009402393130552637753487L
#define dc_log10_phi   	0.208987640249978733769272089237555417L

uint64_t dc_fib_digits (uint64_t n);
uint64_t dc_pisano (uint64_t n);
uint64_t dc_fib_mod (uint64_t n, uint64_t m);



/* arithmetic/divisibility */
#define dc_mul_div(m, d, a, b) \
	do { \
		if (a < 2 * b) m = a - b, d = 1; \
		else m = a % b, d = a / b; \
	} while (0)

uint64_t dc_gcd (uint64_t m, uint64_t n);
uint64_t dc_ext_gcd (uint64_t a, uint64_t b, int64_t* s, int64_t* t);



/* arithmetic/alloc */
int8_t *dc_alloc_sieve (size_t limit);
void dc_free_sieve ();
uint32_t *dc_alloc_primes (size_t *size);
void dc_free_primes ();
uint32_t *dc_alloc_factors (size_t limit);
void dc_free_factors ();



#endif // _DC_ARITHMETIC_H
