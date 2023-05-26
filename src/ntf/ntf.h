#ifndef _NTF_H
#define _NTF_H


/* ntf/primes.c */
int s3_prime (uint64_t n);
int mr_prime (uint64_t n);
int ef_prime (uint64_t n);
int mr_prime_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a);
int ext_mr_prime_test(uint64_t n, uint64_t d, uint32_t s, uint32_t a);

uint64_t exp_mod (uint64_t base, uint64_t exp, uint64_t modulo);
uint64_t ext_mod (uint64_t base, uint64_t exp, uint64_t modulo);
uint64_t mul_mod (uint64_t a, uint64_t b, uint64_t m);

void er_sieve (int *isprime, int limit);

int mobius_f (int N, int* isprime);
void mobius_setup (int *mobius, int limit, int *primes, int primes_size);
void rec_mob_setup(int *mobius, int limit, int num, int i, int *primes, int primes_size);

#endif // _NTF_H
