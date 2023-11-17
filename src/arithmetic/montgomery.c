#include <stdint.h>
#include "dc_arithmetic.h"


static
#ifdef _DC_THREADS
	__thread
#endif
	uint64_t cached_n = 0, _un_i, r_mod_n;


#define _dc_redc_helper(a, b) \
	t = (unsigned __int128) a * b; \
\
	m = t & 0xFFFFFFFFFFFFFFFF; \
	m *= _un_i; \
	high_t = (uint64_t) (t >> 64); \
	low_t = (uint64_t) t; \
\
	m &= 0xFFFFFFFFFFFFFFFF; \
	m *= cached_n; \
	high_m = (uint64_t) (m >> 64); \
	low_m = (uint64_t) m; \
\
	high_t += __builtin_add_overflow(low_t, low_m, &rem); \
	carry = __builtin_add_overflow(high_t, high_m, &rem); \
\
	sub = (carry) ? cached_n : 0; \
	sub = (rem >= cached_n) ? cached_n : sub;



uint64_t dc_redc_64bit (uint64_t a, uint64_t b)
{
	unsigned __int128 t, m;
	uint64_t rem, sub, high_t, high_m, low_t, low_m;
	int carry;

	_dc_redc_helper(a, b);

	return rem - sub;
}


uint64_t dc_redc2_64bit (uint64_t *a, uint64_t b)
{
	unsigned __int128 t, m;
	uint64_t rem, sub, high_t, high_m, low_t, low_m;
	int carry;

	_dc_redc_helper(a[0], b);

	a[0] = rem - sub;

	_dc_redc_helper(b, b);

	return rem - sub;
}

#undef _dc_redc_helper


void dc_montgomery_cached (uint64_t n, uint64_t *x)
{
	uint64_t tmp;

	if (n == cached_n) goto montgomery_cached_return;

	cached_n = n;
	r_mod_n = (-n) % n;

	dc_montgomery_gcd(n, &tmp, &_un_i);

montgomery_cached_return:
	x[0] = r_mod_n;
}
