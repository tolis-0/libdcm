#include <stdint.h>
#include "dc_arithmetic.h"


/* (a * b + c) % m */
uint64_t dc_muladd_mod (uint64_t a, uint64_t b, uint64_t c, uint64_t m)
{
	unsigned __int128 full;
	uint64_t rem;

	if (m <= 0x100000000)
		return ((a > m ? (a % m) : a) * (b > m ? (b % m) : b) + c) % m;

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

uint64_t dc_montgomery_mul_mod(uint64_t a, uint64_t b, uint64_t rbit,
	uint64_t r_1, uint64_t n, uint64_t n_)
{
	unsigned __int128 t, m, rem128;
	uint64_t rem, t_0;

	t = (unsigned __int128) a * b;
	if (n >= 0x8000000000000000) {
		rem = t;
		m = (unsigned __int128) rem * n_;
		rem = m;
		m = (unsigned __int128) rem * n;
		t_0 = (t & 1);
		t >>= 1, m >>= 1;
		rem128 = (t + m) >> 63;
		if (t_0) rem128++;
		t_0 = rem128 >> 64;
		if (t_0) rem = rem128 - n;
		else {
			rem = rem128;
			if (rem >= n) rem -= n;
		}
	} else {
		m = ((t & r_1) * n_) & r_1;
		rem = (t + m * n) >> rbit;
		if (rem >= (n)) rem -= n;
	}

	return rem;
}

uint64_t dc_add_mod(uint64_t a, uint64_t b, uint64_t m)
{
	uint64_t rem;
	unsigned __int128 tmp128;

	if (m < 0x8000000000000000) {
		rem = ((a) >= (m) ? ((a) % (m)) : (a))
			+ ((b) >= (m) ? ((b) % (m)) : (b));
		if (rem > m) rem -= m;
	} else {
		tmp128 = (unsigned __int128) (a) + (b);
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
uint64_t dc_exp_mod (uint64_t base, uint64_t exp, uint64_t n) 
{
	uint64_t x, rbit, r_1, un_i;
	
	if (n <= 0x100000000) {
		for (x = 1, base %= n; exp != 0; exp >>= 1){
			if (exp & 1) x = (x * base) % n;
			base = (base * base) % n;
		}

		return x;
	}

	if ((n & 1) == 0) {
		for (x = 1, base %= n; exp; exp >>= 1){
			if (exp & 1) x = dc_mul_mod(x, base, n);
			base = dc_mul_mod(base, base, n);
		}

		return x;
	}

	dc_montgomery_cached(n, &un_i, &rbit);

	if (rbit == 64) {
		r_1 = 0xFFFFFFFFFFFFFFFF;
		x = -n;
	} else {
		r_1 = 1ULL << rbit;
		x = r_1 - n;
		r_1--;
	}
	base = dc_mul_mod(base, x, n);

	for (; exp != 0; exp >>= 1) {
		if (exp & 1)
			x = dc_montgomery_mul_mod(x, base, rbit, r_1, n, un_i);
		base = dc_montgomery_mul_mod(base, base, rbit, r_1, n, un_i);
	}

	x = dc_montgomery_mul_mod(x, 1, rbit, r_1, n, un_i);

	return x;
}


void dc_montgomery_cached (uint64_t n, uint64_t *un_i, uint64_t *rbit)
{
	static uint64_t cached_n = 0, _un_i, _rbit;
	uint64_t _r_1;
	int64_t tmp, n_i;

	if (n == cached_n) goto mont_cached_return;

	_r_1 = 0x8000000000000000, _rbit = 63;
	while ((_r_1 & n) == 0) _rbit--, _r_1 >>= 1;
	_rbit++;

	if (_rbit == 64) {
		ext_gcd(n, -n, &n_i, &tmp);
		_un_i = tmp - n_i;
	} else {
		_r_1 <<= 1;
		ext_gcd(_r_1, n, &tmp, &n_i);
		if (n_i < 0) _un_i = - n_i;
		else _un_i = _r_1 - n_i;
	}

	cached_n = n;

mont_cached_return:
	un_i[0] = _un_i;
	rbit[0] = _rbit;
}