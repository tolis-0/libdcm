#include <stdint.h>
#include "dc_arithmetic.h"


static uint64_t cached_n = 0, _mask, _un_i, _rbit;

/* (a * b + c) % m */
uint64_t dc_muladd_mod (uint64_t a, uint64_t b, uint64_t c, uint64_t m)
{
	unsigned __int128 full;
	uint64_t rem;

	if (m <= 0x100000000)
		return ((a > m ? (a % m) : a) *
				(b > m ? (b % m) : b) +
				(c > 0x1FFFFFFFF ? (c % m) : c)) % m;

#ifdef __x86_64__
	uint64_t low, high, result;

	full = (unsigned __int128)
		(a >= m ? (a % m) : a) * (b >= m ? (b % m) : b) + c;
	high = full >> 64;
	low = full;

	if (high == 0) {
		if (low >= m) rem = low % m;
		else rem = low;
	} else {
		__asm__("divq %[v]"
			: "=a"(result), "=d"(rem)
			: [v] "r"(m), "a"(low), "d"(high));
	}
#else
	full = (unsigned __int128) a * b + c;
	rem = (uint64_t) (full % (uint64_t) m);
#endif

	return rem;
}


uint64_t dc_montgomery_mul_mod (uint64_t a, uint64_t b)
{
	unsigned __int128 t, m, rem128;
	uint64_t rem, t_0;

	t = (unsigned __int128) a * b;
	if (_rbit == 64) {
		rem = t;
		m = (unsigned __int128) rem * _un_i;
		rem = m;
		m = (unsigned __int128) rem * cached_n;
		t_0 = (t & 1);
		t >>= 1, m >>= 1;
		rem128 = (t + m) >> 63;
		if (t_0) rem128++;
		t_0 = rem128 >> 64;
		if (t_0) rem = rem128 - cached_n;
		else {
			rem = rem128;
			if (rem >= cached_n) rem -= cached_n;
		}
	} else {
		rem = t;
		rem &= _mask;
		m = ((unsigned __int128) rem * _un_i);
		rem = m;
		rem &= _mask;
		rem128 = t + (unsigned __int128) rem * (unsigned __int128) cached_n;
		rem = rem128 >> _rbit;
		if (rem >= cached_n) rem -= cached_n;
	}

	return rem;
}


/* (a + b) % m*/
uint64_t dc_add_mod (uint64_t a, uint64_t b, uint64_t m)
{
	uint64_t rem;
	unsigned __int128 tmp128;

	if (m < 0x8000000000000000) {
		rem = (a >= m ? (a % m) : a)
			+ (b >= m ? (b % m) : b);
		if (rem >= m) rem -= m;
	} else {
		tmp128 = (unsigned __int128) (a >= m ? (a % m) : a) + (b >= m ? (b % m) : b);
		if (tmp128 >> 64) {
			rem = tmp128 - m;
		} else {
			rem = tmp128;
			if (rem > m) rem -= m;
		}
	}

	return rem;
}


/* (a ^ b) % m*/
uint64_t dc_exp_mod (uint64_t base, uint64_t exp, uint64_t m)
{
	uint64_t x;

	if (m <= 0x100000000) {
		if (m == 1) return 0;

		for (x = 1, base %= m; exp != 0; exp >>= 1){
			if (exp & 1) x = (x * base) % m;
			base = (base * base) % m;
		}

		return x;
	}

	if ((m & 1) == 0) {
		for (x = 1, base %= m; exp; exp >>= 1){
			if (exp & 1) x = dc_mul_mod(x, base, m);
			base = dc_mul_mod(base, base, m);
		}

		return x;
	}

	dc_montgomery_cached(m, &x);
	base = dc_mul_mod(base, x, m);

	for (; exp != 0; exp >>= 1) {
		if (exp & 1) x = dc_montgomery_mul_mod(x, base);
		base = dc_montgomery_mul_mod(base, base);
	}

	x = dc_montgomery_mul_mod(x, 1);

	return x;
}


void dc_montgomery_cached (uint64_t n, uint64_t *x)
{
	int64_t tmp, n_i;

	if (n == cached_n) goto montgomery_cached_return;

	_mask = 0x8000000000000000, _rbit = 63;
	while ((_mask & n) == 0) _rbit--, _mask >>= 1;
	_rbit++;

	if (_rbit == 64) {
		ext_gcd(n, -n, &n_i, &tmp);
		_un_i = tmp - n_i;
	} else {
		_mask <<= 1;
		ext_gcd(_mask, n, &tmp, &n_i);
		if (n_i < 0) _un_i = - n_i;
		else _un_i = _mask - n_i;
	}

	cached_n = n;
	_mask--;

montgomery_cached_return:
	if (_rbit == 64) x[0] = -n;
	else x[0] = (_mask + 1) - n;
}