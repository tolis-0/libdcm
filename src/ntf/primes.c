#include <stdint.h>
#include <string.h>
#include <math.h>
#include "ntf.h"


/* Skips multiples of 2 and 3 */
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


/* Skips multiples of 2, 3 and 5 but starts with 97 for ef_prime */
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


/* Miller–Rabin primality test */
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
		fast_mul_mod(base, base, base, n);
		if (base == 1) return 1;
		if (base == n-1) return 0;
	}

	return 1;
}

// bpsw has to check 5 and 11 because it returns 0
int32_t find_D_jacobi (uint64_t n)
{
	uint64_t root, p, a, rem;
	uint32_t D;
	int32_t res;

	for (D = 5;; D += 2) {
		if (D == 19) {
			root = (uint64_t) floorl(sqrtl(n));
			if (root * root == n) return 0;
		}

		res = 1;
		a = n % D;
		p = D;

		for (; a; a %= p) {

			while (a % 2 == 0) {
				a >>= 1;
				rem = p % 8;
				if (rem == 3 || rem == 5) res = -res;
			}

			rem = p;
			p = a;
			a = rem;

			if (a % 4 == 3 && p % 4 == 3) res = -res;
		}

		if (res == -1 && p == 1) break;
		if (p != 1) return 0;
	}

	return (D & 2) ? - D : D;
}


/* test for P = 1 */
int lucas_prime_P1 (uint64_t n, uint64_t Q)
{
	uint64_t bit, U0, U1, Utmp1, Utmp2, const_2, un_i, rbit, r_1;

	bit = 0x8000000000000000;
	while ((n & bit) == 0) bit >>= 1;

	U0 = 0;
	if (n < 0x100000000) {
		U1 = 1;
		for (; bit; bit >>= 1) {
			if (n & bit) {
				Utmp1 = (U1 * U1) % n;
				Utmp2 = (U0 * Q) % n;
				U1 = (Utmp2 * ((2 * U1) % n) + Utmp1) % n;
				U0 = (Utmp1 + Utmp2 * U0) % n;
			} else {
				Utmp1 = (U0 * U0) % n;
				Utmp2 = (U1 * U0) % n;
				Utmp2 = 2 * Utmp2 + (n - Utmp1);
				U1 = ((U1 * U1) % n + Q * Utmp1) % n;
				U0 = Utmp2 % n;
			}
		}
	} else if (n < 0x8000000000000000) {
		montgomery_cached(n, &un_i, &rbit);

		r_1 = 1ULL << rbit;
		U1 = r_1 - n;
		const_2 = 2ULL * U1;
		if (const_2 > n) const_2 -= n;
		fast_mul_mod(Q, Q, r_1, n);
		r_1--;

		for (; bit; bit >>= 1) {
			if (n & bit) {
				montgomery_mul_mod(Utmp1, U1, U1, rbit, r_1, n, un_i);
				montgomery_mul_mod(Utmp2, U0, Q, rbit, r_1, n, un_i);
				montgomery_mul_mod(U1, const_2, U1, rbit, r_1, n, un_i);
				montgomery_mul_mod(U1, Utmp2, U1, rbit, r_1, n, un_i);
				U1 += Utmp1; if (U1 > n) U1 -= n;
				montgomery_mul_mod(U0, Utmp2, U0, rbit, r_1, n, un_i);
				U0 += Utmp1; if (U0 > n) U0 -= n;
			} else {
				montgomery_mul_mod(Utmp1, U0, U0, rbit, r_1, n, un_i);
				montgomery_mul_mod(Utmp2, U1, U0, rbit, r_1, n, un_i);
				montgomery_mul_mod(U0, Utmp2, const_2, rbit, r_1, n, un_i);
				U0 += n - Utmp1; if (U0 > n) U0 -= n;
				montgomery_mul_mod(U1, U1, U1, rbit, r_1, n, un_i);
				Utmp2 = U1;
				montgomery_mul_mod(U1, Utmp1, Q, rbit, r_1, n, un_i);
				U1 += Utmp2; if (U1 > n) U1 -= n;
			}
		}

		montgomery_mul_mod(U1, U1, 1ULL, rbit, r_1, n, un_i);
	} else {
		// FIXME: 64bit is not working correctly
		unsigned __int128 tmp128;
		montgomery_cached(n, &un_i, &rbit);

		U1 = -n;
		if (U1 & 0x8000000000000000) {
			const_2 = (unsigned __int128) U1 * 2 - n;
		} else {
			const_2 = U1 * 2ULL;
		}
		fast_mul_mod(Q, Q, U1, n);

		for (; bit; bit >>= 1) {
			if (n & bit) {
				montgomery_mul_mod_bit64(Utmp1, U1, U1, n, un_i);
				montgomery_mul_mod_bit64(Utmp2, U0, Q, n, un_i);
				montgomery_mul_mod_bit64(U1, const_2, U1, n, un_i);
				montgomery_mul_mod_bit64(U1, Utmp2, U1, n, un_i);
				tmp128 = U1 + Utmp1;
				if (tmp128 >> 64) U1 = tmp128 - n;
				else {U1 = tmp128; if (U1 > n) U1 -= n;}
				montgomery_mul_mod_bit64(U0, Utmp2, U0, n, un_i);
				tmp128 = U0 + Utmp1;
				if (tmp128 >> 64) U0 = tmp128 - n;
				else {U0 = tmp128; if (U0 > n) U0 -= n;}
			} else {
				montgomery_mul_mod_bit64(Utmp1, U0, U0, n, un_i);
				montgomery_mul_mod_bit64(Utmp2, U1, U0, n, un_i);
				montgomery_mul_mod_bit64(U0, Utmp2, const_2, n, un_i);
				tmp128 = U0 + (n - Utmp1);
				if (tmp128 >> 64) U0 = tmp128 - n;
				else {U0 = tmp128; if (U0 > n) U0 -= n;}
				montgomery_mul_mod_bit64(U1, U1, U1, n, un_i);
				Utmp2 = U1;
				montgomery_mul_mod_bit64(U1, Utmp1, Q, n, un_i);
				tmp128 = U1 + Utmp2;
				if (tmp128 >> 64) U1 = tmp128 - n;
				else {U1 = tmp128; if (U1 > n) U1 -= n;}
			}
		}

		montgomery_mul_mod_bit64(U1, U1, 1ULL, n, un_i);
	}

	return (U1 == 0);
}


int bpsw_prime (uint64_t n)
{
	uint64_t d, s, negQ;
	int64_t tmp;
	int32_t D;

	if (n < 2) return 0;
	if (n == 2 || n == 11) return 1;
	if (n % 2 == 0) return 0;

	for (d = n - 1, s = 0; d % 2 == 0; d >>= 1, s++);

	if (d < (1UL << s)) {
		if (n == 5) return 1;
		D = find_D_jacobi(n);
		if (D == 0) return 0;
		if (D < 0) D += n;
		if (n < 4294967295){
			if (exp_mod(D, (n-1)/2, n) == n - 1) return 1;
		} else {
			if (ext_mod(D, (n-1)/2, n) == n - 1) return 1;
		}
		return 0;
	}

	/* Miller–Rabin test base 2 */
	if (n < 4294967295) {
		if (mr_prime_test(n, d, s, 2)) return 0;
	} else {
		if (ext_mr_prime_test(n, d, s, 2)) return 0;
	}


	D = find_D_jacobi(n);
	if (D == 0) return 0;

	tmp = (1 - D) / 4;
	if (tmp > 0) {
		if (n % tmp == 0) return 0;
		negQ = n - tmp;
	} else {
		negQ = -tmp;
	}

	return lucas_prime_P1(n, negQ);
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
	if (n < 4000000000) return mr_prime(n);
	return bpsw_prime(n);
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
