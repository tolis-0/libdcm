#include "../dctest.h"
#include <stdlib.h>

void ef_prime_performance (uint64_t total, uint64_t bits) {
	uint64_t i, *input;
	clock_t start, end = 0;

	set_rand();
	input = (uint64_t *) malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++)
		input[i] = rand_bit(bits) | 1;
	
	start = clock();

	for (i = 0; i < total; i++)
		ef_prime(input[i]);

	end = clock();
	free(input);

	printf("% 2lubit time: %lfs\n", bits, (double) (end - start)/CLOCKS_PER_SEC);
}

int main ()
{
	int test;

	for (test = 3; test <= 64; test++) {
		ef_prime_performance(100000, test);
	}

	return 0;
}
