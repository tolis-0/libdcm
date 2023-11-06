#include <stdint.h>
#include <math.h>
#include "dc_arithmetic.h"


uint64_t dc_pcf_approx (uint64_t n)
{
	if (n < 2) return 0;
	return ceill(1.25506L * n / logl(n));
}


uint64_t dc_primef_approx (uint64_t n)
{
	if (n < 6) return 11;
	return floorl(n * (logl(n) + logl(logl(n))));
}


uint64_t dc_sqrt(uint64_t n)
{
	uint64_t x = n, c = 0, d = 0x4000000000000000;

	while (d > n) d >>= 2;

	for (; d != 0; d >>= 2) {
		if (x >= c + d) {
			x -= c + d;
			c = (c >> 1) + d;
		} else {
			c >>= 1;
		}
	}

	return c;
}
