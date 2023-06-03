#include <stdint.h>
#include <string.h>
#include <math.h>
#include "ntf.h"


// Skips multiples of 2 and 3
int s3_prime (uint64_t n)
{
	uint64_t root, p;

	if (n < 2) return 0;
	if (n == 2 || n == 3) return 1;
	else if (n % 2 == 0 || n % 3 == 0) return 0;

	root = (uint64_t) floorl(sqrtl(n));

	for (p = 5; p <= root; p += 4) {
		if (n % p == 0) return 0; // checks for 5+6n
		p += 2;
		if (n % p == 0) return 0; // checks for 7+6n
	}

	return 1;
}

int s5_prime_st97 (uint64_t n)
{
	uint64_t root, p;

	if (n < 2) return 0;
	if (n < 9409) return 1;
	if (n % 97 == 0) return 0;

	root = (uint64_t) floorl(sqrtl(n));

	for (p = 101; p <= root; p += 4) {
		if (n % p == 0) return 0; 
		p += 2; if (n % p == 0) return 0; 
		p += 4; if (n % p == 0) return 0; 
		p += 2; if (n % p == 0) return 0; 
		p += 4; if (n % p == 0) return 0; 
		p += 6; if (n % p == 0) return 0; 
		p += 2; if (n % p == 0) return 0; 
		p += 6; if (n % p == 0) return 0; 
	}

	return 1;
}

// Miller–Rabin primality test
int mr_prime (uint64_t n)
{
	uint64_t d;
	uint32_t s;

	if (n < 2) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	
	/* n = (2^s)*d+1 */
	for (d = n - 1, s = 0; d % 2 == 0; d >>= 1, s++);

	if (n < 9080191) {
		if (n == 31 || n == 73) return 1;
		if (mr_prime_test(n, d, s, 31)) return 0;
		if (mr_prime_test(n, d, s, 73)) return 0;
		return 1;
	}

	if (n < 4759123141) {
		if (n < 4294967295) {
			if (mr_prime_test(n, d, s, 7)) return 0;
			if (mr_prime_test(n, d, s, 2)) return 0;
			if (mr_prime_test(n, d, s, 61)) return 0;
			return 1;
		}
		if (ext_mr_prime_test(n, d, s, 7)) return 0;
		if (ext_mr_prime_test(n, d, s, 2)) return 0;
		if (ext_mr_prime_test(n, d, s, 61)) return 0;
		return 1;
	}

	if (n < 1122004669633) {
		if (ext_mr_prime_test(n, d, s, 13)) return 0;
		if (ext_mr_prime_test(n, d, s, 2)) return 0;
		if (ext_mr_prime_test(n, d, s, 23)) return 0;
		if (ext_mr_prime_test(n, d, s, 1662803)) return 0;
		return 1;
	}

	if (ext_mr_prime_test(n, d, s, 11)) return 0;
	if (ext_mr_prime_test(n, d, s, 7)) return 0;
	if (ext_mr_prime_test(n, d, s, 5)) return 0;
	if (ext_mr_prime_test(n, d, s, 3)) return 0;
	if (ext_mr_prime_test(n, d, s, 2)) return 0;
	if (n < 2152302898747) return 1;
	if (ext_mr_prime_test(n, d, s, 13)) return 0;
	if (n < 3474749660383) return 1;
	if (ext_mr_prime_test(n, d, s, 17)) return 0;
	if (n < 341550071728321) return 1;
	if (ext_mr_prime_test(n, d, s, 19)) return 0;
	if (ext_mr_prime_test(n, d, s, 23)) return 0;
	if (n < 3825123056546413051) return 1;
	if (ext_mr_prime_test(n, d, s, 29)) return 0;
	if (ext_mr_prime_test(n, d, s, 31)) return 0;
	if (ext_mr_prime_test(n, d, s, 37)) return 0;
	return 1;
}


int ef_prime (uint64_t n)
{
	if (n % 2 == 0) return n == 2;
	if (n % 3 == 0) return n == 3;
	if (n % 5 == 0) return n == 5;
	if (n % 7 == 0) return n == 7;
	if (n % 11 == 0) return n == 11;
	if (n % 13 == 0) return n == 13;
	if (n % 17 == 0) return n == 17;
	if (n % 19 == 0) return n == 19;
	if (n % 23 == 0) return n == 23;
	if (n % 29 == 0) return n == 29;
	if (n % 31 == 0) return n == 31;
	if (n % 37 == 0) return n == 37;
	if (n % 41 == 0) return n == 41;
	if (n % 43 == 0) return n == 43;
	if (n % 47 == 0) return n == 47;
	if (n % 53 == 0) return n == 53;
	if (n % 59 == 0) return n == 59;
	if (n % 61 == 0) return n == 61;
	if (n % 67 == 0) return n == 67;
	if (n % 71 == 0) return n == 71;
	if (n % 73 == 0) return n == 73;
	if (n % 79 == 0) return n == 79;
	if (n % 83 == 0) return n == 83;
	if (n % 89 == 0) return n == 89;

	if (n < 130000) return s5_prime_st97(n);
	return mr_prime(n);
}


/* Returns 1 if n is definitely composite */
int mr_prime_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a)
{
	uint64_t base;
	uint32_t r;

	base = exp_mod(a, d, n);

	if (base == 1 || base == n-1) return 0;

	for (r = 1; r < s; r++) {
		base = (base * base) % n;
		if (base == 1) return 1;
		if (base == n-1) return 0;
	}

	return 1;
}


int ext_mr_prime_test (uint64_t n, uint64_t d, uint32_t s, uint32_t a)
{
	uint64_t base;
	uint32_t r;

	base = ext_mod(a, d, n);

	if (base == 1 || base == n-1) return 0;

	for (r = 1; r < s; r++) {
		base = (((unsigned __int128) base * base) % n);
		if (base == 1) return 1;
		if (base == n-1) return 0;
	}

	return 1;
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
