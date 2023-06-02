#include <stdint.h>
#include <gmp.h>
#include "../dctest.h"

void mul_mod_gmp_test (uint64_t total, uint64_t bits) {
	uint64_t i, passed, a, b, m, output, expected;
	mpz_t gmp_num;
	char input[70];

	set_rand();
	mpz_init(gmp_num);

	for (i = 0, passed = 0; i < total; i++) {
		a = rand_bit(64);
		b = rand_bit(64);
		m = rand_bit(bits);
		
		mpz_set_ui(gmp_num, a);
		mpz_mul_ui(gmp_num, gmp_num, b);
		expected = mpz_mod_ui(gmp_num, gmp_num, m);

		output = mul_mod(a, b, m);
		snprintf(input, 70, "%llu, %llu, %llu", a, b, m);
		_test_check(string, uint64_t, input, expected, output);
	}

	_print_test_result2(mul_mod, gmp, i, passed, " %3$dbit", bits);
}

int main () 
{
	int test;

	for (test = 60; test <= 64; test++) {
		mul_mod_gmp_test(200000, test);
	}

	return 0;
}
