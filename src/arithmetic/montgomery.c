#include <stdint.h>
#include "dc_arithmetic.h"

static unsigned _k;
static uint64_t _n = 0, _n_inv, r_mod_n;


uint64_t dc_redc_64bit (uint64_t a, uint64_t b)
{
	unsigned __int128 t, m, mn;
	uint64_t u, sub, high_t, high_mn, low_t, low_mn;
	int carry;

	t = (unsigned __int128) a * b;

	/*	m = (t mod r) * n',		r = 2^64 */
	m = t & 0xFFFFFFFFFFFFFFFF;
	m *= _n_inv;
	high_t = (uint64_t) (t >> 64);
	low_t = (uint64_t) t;

	/*	m*n = (m mod r) * n */
	m &= 0xFFFFFFFFFFFFFFFF;
	mn = m * _n;
	high_mn = (uint64_t) (mn >> 64);
	low_mn = (uint64_t) mn;

	/*	u = (t + m*n) / r */
	high_t += __builtin_add_overflow(low_t, low_mn, &u);
	carry = __builtin_add_overflow(high_t, high_mn, &u);

	/*	(u >= n) ? (u - n) : u */
	sub = (carry) ? _n : 0;
	sub = (u >= _n) ? _n : sub;

	return u - sub;
}



uint32_t dc_redc_32bit (uint32_t a, uint32_t b)
{
	uint64_t t, mn, carry, u;
	uint64_t m;

	t = (uint64_t) a * (uint64_t) b;

	/*	m = (t mod r) * n',		r = 2^32 */
	m = (uint32_t) t;
	m *= _n_inv;

	/*	m*n = (m mod r) * n */
	mn = (uint64_t) m * _n;

	/*	u = (t + m*n) / r */
	carry = __builtin_add_overflow(t, mn, &u);

	u >>= 32;
	carry <<= 32;
	u += carry;

	/*	(u >= n) ? (u - n) : u */
	return (uint32_t) ((u >= _n) ? u - _n : u);
}



uint64_t dc_montgomery (unsigned k, uint64_t n, uint64_t *x)
{
	if (n == _n && k == _k) goto montgomery_cached_ret;

	_n = n;
	_k = k;

	if (k == 64U) {
		r_mod_n = (-n) % n;
	} else {
		r_mod_n = (1ULL << k) % n;
	}

	dc_2powr_gcd(k, n, &_n_inv);

montgomery_cached_ret:
	
	x[0] = r_mod_n;
	return _n_inv;
}

