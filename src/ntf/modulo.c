#include <stdint.h>
#include "ntf.h"

uint64_t exp_mod (uint64_t base, uint64_t exp, uint64_t n) 
{
	uint64_t x = 1;

	for (base %= n; exp != 0; exp >>= 1){
		if (exp & 1) x = ( x * base) % n;
		base = (base * base) % n;
	}

	return x;
}


uint64_t ext_mod (uint64_t base, uint64_t exp, uint64_t n) 
{
	uint64_t x, rbit, r_1, un_i;
	
	if ((n & 1) == 0) {
		x = 1;

		for (base %= n; exp; exp >>= 1){
			if (exp & 1) fast_mul_mod(x, x, base, n);
			fast_mul_mod(base, base, base, n);
		}

		return x;
	}

	montgomery_cached(n, &un_i, &rbit);

	if (rbit == 64) {

		x = -n;
		fast_mul_mod(base, base, x, n);

		for (; exp != 0; exp >>= 1) {
			if (exp & 1)
				montgomery_mul_mod_bit64(x, x, base, n, un_i);
			montgomery_mul_mod_bit64(base, base, base, n, un_i);
		}

		montgomery_mul_mod_bit64(x, x, 1, n, un_i);
	} else {
		r_1 = 1ULL << rbit;
		x = r_1 - n;
		r_1--;
		fast_mul_mod(base, base, x, n);

		for (; exp != 0; exp >>= 1) {
			if (exp & 1)
				montgomery_mul_mod(x, x, base, rbit, r_1, n, un_i);
			montgomery_mul_mod(base, base, base, rbit, r_1, n, un_i);
		}

		montgomery_mul_mod(x, x, 1, rbit, r_1, n, un_i);
	}

	return x;
}


void montgomery_cached (uint64_t n, uint64_t *un_i, uint64_t *rbit)
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