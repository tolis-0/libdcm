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
	uint64_t r0, r1, r2;

	if (n == 0) return 0;

	for (r0 = 1, r1 = n;; r0 = r1, r1 = r2) {
		r2 = (r1 + (n / r1)) / 2;
		if (r0 == r1 || r0 == r2) break;
	}

	return (r0 < r1) ? r0 : r1;
}
