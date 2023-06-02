#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <gmp.h>
#include "../dctest.h"

void mr_prime_gmp_test (uint64_t total, uint64_t bits) {
	uint64_t i, j, passed, input, rand_num;
	int output, expected;
	mpz_t gmp_input;

	srand(clock());
	mpz_init(gmp_input);

	for (i = 0, passed = 0; i < total;) {
		
		for (input = 0, j = 0; j < 5; j++){
			input <<= 15;
			rand_num = 0x7FFF & rand();
			input |= rand_num;
		}
		input &= 0xFFFFFFFFFFFFFFFF >> (64 - bits);
		input |= 1;
		mpz_set_ui(gmp_input, input);

		expected = mpz_probab_prime_p(gmp_input, 50);
		if (expected == 2) expected = 1;

		output = mr_prime(input);
		_test_check(uint64_t, int, input, expected, output);
		i++;
	}

	_print_test_result2(mr_prime, gmp, i, passed, " %3$dbit", bits);
}

int main () 
{
	int test;

	for (test = 54; test < 64; test++) {
		mr_prime_gmp_test(50000, test);
	}

	return 0;
}
