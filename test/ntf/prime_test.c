#include "../dctest.h"
#include <stdlib.h>

SEQUENCE_TEST_F(int32_t, mr_prime, uint64_t, isprime);
SEQUENCE_TEST_F(int32_t, s3_prime, uint64_t, isprime);
SEQUENCE_TEST_F(int32_t, ef_prime, uint64_t, isprime);

SEQUENCE_TEST_AF(int8_t, er_sieve, isprime);

SET_TEST_F(mr_prime, uint64_t, primes);
SET_TEST_F(s3_prime, uint64_t, primes);
SET_TEST_F(ef_prime, uint64_t, primes);

SET_TEST_FNS(mr_prime, uint64_t, primes26, set26, 472882048);
FALSE_TEST_FN(mr_prime, uint64_t, a074773, strps);
TRUE_TEST_FN(mr_prime, uint64_t, b049002, p2_2);
TRUE_TEST_FN(mr_prime, uint64_t, b056130, palb24);
TRUE_TEST_FN(mr_prime, uint64_t, b272061, sigtp);

int main () {
	int8_t *isprime_array;

	mr_prime_sequence_test();
	s3_prime_sequence_test();
	ef_prime_sequence_test();

	malloc_sieve(isprime_array, 100001);
	er_sieve_sequence_test(isprime_array);
	free(isprime_array);

	mr_prime_set_test();
	s3_prime_set_test();
	ef_prime_set_test();

	mr_prime_set26_test(); 	// The Twenty-sixth 1,000,000 Primes (from primes.utm.edu)
	mr_prime_strps_test(); 	// Strong pseudoprimes to bases 2, 3, 5 and 7.
	mr_prime_p2_2_test(); 	// Primes of form p^2-2, where p is prime.
	mr_prime_palb24_test(); // Palindromic primes in bases 2 and 4.
	//mr_prime_sigtp_test(); 	// 64bit of A272061 in oeis (Fails above 63bit)

}
