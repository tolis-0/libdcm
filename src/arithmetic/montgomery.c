#include <stdint.h>
#include "dc_arithmetic.h"


static
#ifdef _DC_THREADS
	__thread
#endif
	uint64_t cached_n = 0, _mask, _un_i, _rbit;


uint64_t dc_montgomery_mul_mod (uint64_t a, uint64_t b)
{
	unsigned __int128 t, m, rem128;
	uint64_t rem, t_0;

	t = (unsigned __int128) a * b;
	if (_rbit == 64) {
		m = t & 0xFFFFFFFFFFFFFFFF;
		m *= (unsigned __int128) _un_i;
		m &= 0xFFFFFFFFFFFFFFFF;
		m *= (unsigned __int128) cached_n;
		t_0 = (uint64_t) (t & 1);
		t >>= 1, m >>= 1;
		rem128 = (t + m) >> 63;
		if (t_0 > 0) rem128++;
		t_0 = (uint64_t) (rem128 >> 64);
		if (t_0 > 0) rem = rem128 - cached_n;
		else {
			rem = (uint64_t) rem128;
			if (rem >= cached_n) rem -= cached_n;
		}
	} else {
		m = t & _mask;
		m *= (unsigned __int128) _un_i;
		m &= _mask;
		rem128 = t + m * (unsigned __int128) cached_n;
		rem128 >>= _rbit;
		rem = (uint64_t) rem128;
		if (rem >= cached_n) rem -= cached_n;
	}

	return rem;
}


void dc_montgomery_cached (uint64_t n, uint64_t *x)
{
	int64_t tmp, n_i;

	if (n == cached_n) goto montgomery_cached_return;

	_mask = 0x8000000000000000, _rbit = 63;
	while ((_mask & n) == 0) _rbit--, _mask >>= 1;
	_rbit++;

	if (_rbit == 64) {
		dc_ext_gcd(n, -n, &n_i, &tmp);
		_un_i = tmp - n_i;
	} else {
		_mask <<= 1;
		dc_ext_gcd(_mask, n, &tmp, &n_i);
		if (n_i < 0) _un_i = - n_i;
		else _un_i = _mask - n_i;
	}

	cached_n = n;
	_mask--;

montgomery_cached_return:
	if (_rbit == 64) x[0] = -n;
	else x[0] = (_mask + 1) - n;
}
