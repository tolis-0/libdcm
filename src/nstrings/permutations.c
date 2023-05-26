#include <stdint.h>

/*  2 numbers have the same digit_id iff the have the same digits 
 *	digit_id7 works for numbers up to 7 digits
 *	digit_id works for all 64bit numbers
 *	runs in O(log(n))
*/
uint32_t digit_id7 (uint32_t n) {
	long id, digit;

	for (id = 0; n > 0; n /= 10) {
		digit = n % 10;
		id += 1 << (digit * 3);
	}

	return id;
}

uint64_t digit_id (uint64_t n) {
	uint64_t id, digit;

	for (id = 0; n > 0; n /= 10) {
		digit = n % 10;
		id += 1LL << (digit * 6);
	}

	return id;
}



uint64_t reverse (uint64_t n) {
	uint64_t copy = n, reverse;

	for (reverse = 0; copy > 0; copy /= 10) 
		reverse = reverse * 10 + (copy % 10);

	return reverse;
}


