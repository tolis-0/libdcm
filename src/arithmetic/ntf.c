#include <stdint.h>
#include <math.h>
#include "dc_arithmetic.h"


uint64_t dc_pcf_approx (uint64_t x)
{
	if (x < 2) return 0;
	return ceill(1.25506L * x / logl(x));
}

uint64_t dc_primef_approx (uint64_t x)
{
	if (x < 6) return 11;
	return floorl(n * (logl(n) + logl(logl(n))));
}
