#include <stdint.h>
#include <string.h>
#include <math.h>
#include "ntf.h"


int s3_prime (uint64_t n) 
{
	uint64_t root, p;

    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    else if (n % 2 == 0) return 0; // checks for multiples of 2
    else if (n % 3 == 0) return 0; // checks for multiples of 3

	root = (uint64_t) floorl(sqrtl(n));
	for (p = 5; p <= root; p += 4) {
		if (n % p == 0) return 0; // checks for multiples of 5+6n
		p += 2;
		if (n % p == 0) return 0; // checks for multiples of 7+6n
	}

	return 1;
}

// Miller–Rabin primality test
int mr_prime (uint64_t n) 
{
	uint64_t d;	// n = (2^s)*d+1
	uint32_t s;

	if (n < 2) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	
	for (d = n - 1, s = 0; d % 2 == 0; d >>= 1, s++);

	// Does simple Miller–Rabin tests for not very big values
	if (n < 3215031751){
		if (!mr_prime_test(n, d, s, 2)) return 0;
		if (n < 2047) return 1;
		if (!mr_prime_test(n, d, s, 3)) return 0;
		if (n < 1373653) return 1;
		if (!mr_prime_test(n, d, s, 5)) return 0;
		if (n < 25326001) return 1;
		if (!mr_prime_test(n, d, s, 7)) return 0;
		return 1;
	}

	// Does extended Miller–Rabin tests for big values
	if (!ext_mr_prime_test(n, d, s, 2)) return 0;
	if (!ext_mr_prime_test(n, d, s, 3)) return 0;
	if (!ext_mr_prime_test(n, d, s, 5)) return 0;
	if (!ext_mr_prime_test(n, d, s, 7)) return 0;
	if (!ext_mr_prime_test(n, d, s, 11)) return 0;
	if (n < 2152302898747) return 1;
	if (!ext_mr_prime_test(n, d, s, 13)) return 0;
	if (n < 3474749660383) return 1;
	if (!ext_mr_prime_test(n, d, s, 17)) return 0;
	if (n < 341550071728321) return 1;
	if (!ext_mr_prime_test(n, d, s, 19)) return 0;
	if (!ext_mr_prime_test(n, d, s, 23)) return 0;
	if (n < 3825123056546413051) return 1;
	if (!ext_mr_prime_test(n, d, s, 29)) return 0;
	if (!ext_mr_prime_test(n, d, s, 31)) return 0;
	if (!ext_mr_prime_test(n, d, s, 37)) return 0;
	return 1;
}

/* Chooses one of the 2 algorithms above based on how large n is */
int ef_prime (uint64_t n) 
{
	if (n < 350000) return s3_prime(n);
	return mr_prime(n);
}

/* Tests n with simple modulo exp algorithm (m^2 <= ULONG_MAX) */
int mr_prime_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a) 
{
	uint64_t base;
	uint32_t r;

	base = exp_mod(a, d, n);
	if (base == 1 || base == n-1) return 1;

	for (r = 1; r < s; r++) {
		base = (base * base) % n;
		if (base == 1) return 0;
		if (base == n-1) return 1;
	}

	return 0;
}


int ext_mr_prime_test(uint64_t n, uint64_t d, uint32_t s, uint32_t a) 
{
	uint64_t base;
	uint32_t r;

	base = ext_mod(a, d, n);
	if (base == 1 || base == n-1) return 1;

	for (r = 1; r < s; r++) {
		base = mul_mod(base, base, n);
		if (base == 1) return 0;
		if (base == n-1) return 1;
	}
	return 0;
}


uint64_t exp_mod (uint64_t base, uint64_t exp, uint64_t modulo) 
{
	uint64_t x = 1;

	for (base %= modulo; exp; exp >>= 1){
		if (exp & 1) x = (x * base) % modulo;
		base = (base * base) % modulo;
	}

	return x;
}


uint64_t ext_mod (uint64_t base, uint64_t exp, uint64_t modulo) 
{
	uint64_t x = 1;

	for(base %= modulo; exp; exp >>= 1){
		if (exp & 1) x = mul_mod(x, base, modulo);
		base = mul_mod(base, base, modulo);
	}

	return x;
}


uint64_t mul_mod (uint64_t a, uint64_t b, uint64_t m) 
{
	long double x;
	uint64_t c;
	int64_t r;
	if (a >= m) a %= m;
	if (b >= m) b %= m;
	x = a;
	c = x * b / m;
	r = (int64_t) (a * b - c * m) % (int64_t) m;
	if (r < 0) return r + m; 
	return r;
}



void er_sieve (int8_t *isprime, size_t limit) 
{
	size_t i, j;

	isprime[0] = 0, isprime[1] = 0;
	memset(&isprime[2], 1, limit - 2);

	for (i = 2; i * i < limit; i++) {
		if (!isprime[i]) continue;

		for (j = 2;; j++) {
			if (i * j >= limit) break;
			else isprime[i * j] = 0;
		}
	}
}


uint64_t pcf_approx (uint64_t x) 
{
	if (x < 2) return 0;
	return ceill(1.25506L*x/logl(x));
}


int mobius_f (int N, int* isprime) 
{
	int i, p = 0, N_ = N, sq = (int) floor(sqrt(N));

	if (isprime[N]) return -1;

	if (N%2 == 0){
		N >>= 1;
		if (N%2 == 0) return 0;
		p++;
	}

	// Check for prime factors > 2
	for (i = 3; N > 1 && i <= sq; i += 2){
		if (isprime[i] && N%i == 0) {
			N /= i;
			if (N%i == 0) return 0;
			p++;
		}
	}

	// Increasing p for primes that divide N above sqrt(N)
	for (; N > 1 && i <= N_; i += 2){
		if (isprime[i] && N%i == 0) {
			N /= i;
			p++;
		}
	}

	return (p%2)? -1 : 1;
}

// for 1 <= n < limit
// int mobius[limit] = {0};
// primes_size is the size of the array primes[]
// primes[] = {2,3,5,7,11,13,...}
void mobius_setup (int *mobius, int limit, int *primes, int primes_size) 
{
	mobius[1] = 1;
	int i;
	for (i = 0; i < primes_size; i++){
		mobius[primes[i]] = -1;
		rec_mob_setup(mobius, limit, primes[i], i, primes, primes_size);
	}
}

// recursive mobius setup
// num: 	number that called
// number is of type: p0*p1*p2*...pn (squarefree)
// i:		number of largest prime factor (pi) of caller number
void rec_mob_setup(int *mobius, int limit, int num, int i, int *primes, int primes_size) 
{
// n: 		new number generated
	long n;
	for (i++; i < primes_size; i++){
		n = ((long) num)*primes[i];
		if (n >= limit) return;
		mobius[(int) n] = -mobius[num];
		rec_mob_setup(mobius, limit, (int) n, i, primes, primes_size);
	}
}
