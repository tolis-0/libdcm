#ifndef NUM_THEORY_H
#define NUM_THEORY_H

int s3_prime(unsigned long n);
int mr_prime(unsigned long n);
int ef_prime(unsigned long n);

void er_prime_sieve(int *isprime, int limit);

unsigned long modulo_exp(unsigned long b, unsigned long e, unsigned long m);
unsigned long ext_modulo_exp(unsigned long b, unsigned long e, unsigned long m);
unsigned long modulo_mul(unsigned long b, unsigned long a, unsigned long m);

int mr_prime_test(unsigned long n, unsigned long d, unsigned s, unsigned a);
int ext_mr_prime_test(unsigned long n, unsigned long d, unsigned s, unsigned a);

int mobius_f(int N, int* isprime);
void mobius_setup(int *mobius, int limit, int *primes, int primes_size);
void rec_mob_setup(int *mobius, int limit, int num, int i, int *primes, int primes_size);

#endif // NUM_THEORY_H
