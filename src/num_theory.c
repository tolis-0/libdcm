#include "num_theory.h"
#include "dcmath.h"

// requires <math.h>
// Checks is n is divisible with 2, 3
// and all other natural numbers up to floor(sqrt(n))
// skips multiples of 2 and 3
// uses sqrtl() from <math.h> so only numbers that fit should be used
int s3_prime(unsigned long n){
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    else if (n%2 == 0) return 0;
    else if (n%3 == 0) return 0;

	unsigned long root, p = 5;

	root = (unsigned long) floorl(sqrtl(n));
	while (p <= root){
		if (n%p == 0) return 0;
		p += 2;
		if (n%p == 0) return 0;
		p += 4;
	}
	return 1;
}

// Miller–Rabin primality test
int mr_prime(unsigned long n){
	if (n < 2) return 0;
	if (n == 2) return 1;
	if (n%2 == 0) return 0;
	
	//	n = (2^s)*d+1
	//	two_s = 2^s
	unsigned long d = n-1;
	unsigned s = 0;
	while (d%2 == 0) d >>= 1, s++;

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

// Chooses one of the 2 algorithms above based on how large n is
// s3_prime is better for small numbers
// mr_prime is better for larger numers (maybe even the only choice if the number is too large)
int ef_prime(unsigned long n){
	if (n < 350000) return s3_prime(n);
	return mr_prime(n);
}

// Tests n with simple modulo exp algorithm (m^2 <= ULONG_MAX)
int mr_prime_test(unsigned long n, unsigned long d, unsigned s, unsigned a){
	unsigned long base;
	base = modulo_exp(a, d, n);
	if(base == 1 || base == n-1) return 1;
	for (unsigned r = 1; r < s; r++){
		base = (base*base)%n;
		if (base == 1) return 0;
		if (base == n-1) return 1;
	}
	return 0;
}

// Tests n with extended modulo exp and modulo multiplication algorithm 
// (m*2 <= ULONG_MAX)
int ext_mr_prime_test(unsigned long n, unsigned long d, unsigned s, unsigned a){
	unsigned long base;
	base = ext_modulo_exp(a, d, n);
	if(base == 1 || base == n-1) return 1;
	for (unsigned r = 1; r < s; r++){
		base = modulo_mul(base, base, n);
		if (base == 1) return 0;
		if (base == n-1) return 1;
	}
	return 0;
}

// It's safe for m^2 <= ULONG_MAX (4 294 967 295 on 64bit long)
unsigned long modulo_exp(unsigned long b, unsigned long e, unsigned long m){
	unsigned long x = 1;

	// starts by getting modulo of the base
	// checks if e > 0 and divides by 2 every iteration
	for(b %= m; e; e >>= 1){
		if (e&1) x = (x*b)%m;
		b = (b*b)%m;
	}

	return x;
}

// It's safe for m*2 <= ULONG_MAX (9 223 372 036 854 775 808 on 64bit long)
unsigned long ext_modulo_exp(unsigned long b, unsigned long e, unsigned long m){
	unsigned long x = 1;

	for(b %= m; e; e >>= 1){
		if (e&1) x = modulo_mul(x, b, m);
		b = modulo_mul(b, b, m);
	}

	return x;
}

// It's safe for m*2 <= ULONG_MAX (9 223 372 036 854 775 808 on 64bit long)
// safe for positive signed long numbers
unsigned long modulo_mul(unsigned long b, unsigned long a, unsigned long m){
	unsigned long x = 0;
	for (b %= m; a; a >>= 1){
		if (a&1) x = (x+b)%m;
		b = (b << 1)%m;
	}

	return x;
}

// ~~~~~~~ Sieve of Eratosthenes ~~~~~~~~
// Array which shows if a number is prime
void er_prime_sieve(int *isprime, int limit){
	int i, j;
	isprime[0] = 0, isprime[1] = 0;
    for (i = 2; i < limit; i++) isprime[i] = 1;
    for (i = 2; i*i < limit; i++){
        if (!isprime[i]) continue;
        for(j = 2;; j++){
            if (i*j >= limit) break;
            else isprime[i*j] = 0;
        }
    }
}



// 1 < N < limit
int mobius_f(int N){
	int i, p = 0, N_ = N, sq = (int) floor(sqrt(N));

	if (prime[N]) return -1;

	if (N%2 == 0){
		N >>= 1;
		if (N%2 == 0) return 0;
		p++;
	}

	// Check for prime factors > 2
	for (i = 3; N > 1 && i <= sq; i += 2){
		if (prime[i] && N%i == 0) {
			N /= i;
			if (N%i == 0) return 0;
			p++;
		}
	}

	// Increasing p for primes that divide N above sqrt(N)
	for (; N > 1 && i <= N_; i += 2){
		if (prime[i] && N%i == 0) {
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
void mobius_setup(){
	mobius[1] = 1;
	int i;
	for (i = 0; i < primes_size; i++){
		mobius[primes[i]] = -1;
		rec_mob_setup(primes[i],  i);
	}
}

// recursive mobius setup
// num: 	number that called
// number is of type: p0*p1*p2*...pn (squarefree)
// i:		number of largest prime factor (pi) of caller number
void rec_mob_setup(int num, int i){
// n: 		new number generated
	long n;
	for (i++; i < primes_size; i++){
		n = ((long) num)*primes[i];
		if (n >= limit) return;
		mobius[(int) n] = -mobius[num];
		rec_mob_setup((int) n, i);
	}
}
