#include <stdint.h>
#include "dc_arithmetic.h"

#define MONEXP_USE_32BIT 1


/*	Montgomery multiplication and reduction for R = 2^64 */
uint64_t dc_mul_redc_64 (uint64_t a, uint64_t b,
	uint64_t N, uint64_t Ninv)
{
	unsigned __int128 T, m, mN;
	uint64_t t, sub, high_T, low_T, high_mN, low_mN;
	int carry;

	T = (unsigned __int128) a * b;

	//	m = (T mod R)*N',	R = 2^64
	m = T & 0xFFFFFFFFFFFFFFFF;
	m *= Ninv;
	high_T = (uint64_t) (T >> 64);
	low_T = (uint64_t) T;

	//	m*N = (m mod R)*N
	m &= 0xFFFFFFFFFFFFFFFF;
	mN = m * N;
	high_mN = (uint64_t) (mN >> 64);
	low_mN = (uint64_t) mN;

	//	t = (T + m*N) / R
	high_T += __builtin_add_overflow(low_T, low_mN, &t);
	carry = __builtin_add_overflow(high_T, high_mN, &t);

	//	(t >= N) ? (t - N) : t
	sub = (carry) ? N : 0;
	sub = (t >= N) ? N : sub;

	return t - sub;
}



/*	Montgomery multiplication and reduction for R = 2^32 */
uint32_t dc_mul_redc_32 (uint32_t a, uint32_t b,
	uint32_t N, uint32_t Ninv)
{
	uint64_t T, mN, carry, t;
	uint32_t m;

	T = (uint64_t) a * (uint64_t) b;

	//	m = (T mod R)*N',	R = 2^32
	m = (uint32_t) T;
	m *= Ninv;

	//	m*N = (m mod R)*N
	mN = (uint64_t) m * (uint64_t) N;

	//	t = (T + m*N)/R
	carry = __builtin_add_overflow(T, mN, &t);

	t >>= 32;
	carry <<= 32;
	t += carry;

	//	(t >= N) ? (t - N) : t
	return (uint32_t) ((t >= N) ? t - N : t);
}



/*	Montgomery Modular Exponentiation */
uint64_t dc_mon_expmod (uint64_t base, uint64_t exp, uint64_t m)
{
	uint64_t x, n_inv;

#if MONEXP_USE_32BIT == 1
	if (m < 0x100000000) {
		uint32_t b, x_32, n_inv;

		n_inv = dc_montgomery(32, m, &x);
		x_32 = x;
		b = dc_mul_mod(base, x, m);

		for (; exp > 0; exp >>= 1) {
			if (exp & 1) x_32 = dc_mul_redc_32(x_32, b, m, n_inv);
			b = dc_mul_redc_32(b, b, m, n_inv);
		}

		x_32 = dc_mul_redc_32(x_32, 1U, m, n_inv);

		return x_32;
	}
#endif

	n_inv = dc_montgomery(64, m, &x);
	base = dc_mul_mod(base, x, m);

	for (; exp > 0; exp >>= 1) {
		if (exp & 1) x = dc_mul_redc_64(x, base, m, n_inv);
		base = dc_mul_redc_64(base, base, m, n_inv);
	}

	x = dc_mul_redc_64(x, 1ULL, m, n_inv);

	return x;
}



/*	Calculates N' and R (mod N) for Montgomery form 
	R = 2^k, 0 < k <= 64 and N < R and N odd */
uint64_t dc_montgomery (unsigned k, uint64_t N, uint64_t *x)
{
	static unsigned _k;
	static uint64_t _N = 0, _Ninv, _R;
	uint64_t tmp;

	if (N == _N && k == _k)
		goto montgomery_cached_ret;

	_N = N;
	_k = k;

	if (k == 64U) {
		_R = (-N) % N;
	} else {
		_R = (1ULL << k) % N;
	}

	dc_2powr_gcd(k, N, &tmp, &_Ninv);

montgomery_cached_ret:
	
	x[0] = _R;
	return _Ninv;
}
