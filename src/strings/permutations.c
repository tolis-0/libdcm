#include <stdint.h>

/*  2 numbers have the same digit_id iff the have the same digits
 *	digit_id works for all 64bit numbers
 *	runs in O(log(n))
*/

uint64_t dc_digit_id (uint64_t n) {
	uint64_t id, digit;

	for (id = 0; n > 0; n /= 10) {
		digit = n % 10;
		id += 1LL << (digit * 6);
	}

	return id;
}



uint64_t dc_reverse (uint64_t n) {
	uint64_t copy, rev;

	for (rev = 0, copy = n; copy > 0; copy /= 10) 
		rev = rev * 10 + (copy % 10);

	return rev;
}


