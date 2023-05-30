#include "../dctest.h"

SEQUENCE_TEST_F(uint32_t, mr_prime, uint64_t, isprime);
SEQUENCE_TEST_F(uint32_t, s3_prime, uint64_t, isprime);
SEQUENCE_TEST_F(uint32_t, ef_prime, uint64_t, isprime);

int main () {
	mr_prime_sequence_test();
	s3_prime_sequence_test();
	ef_prime_sequence_test();
}
