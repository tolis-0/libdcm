#include <stdint.h>
#include "dc_arithmetic.h"


uint64_t dc_gcd (uint64_t a, uint64_t b)
{
	uint8_t shift, a_lz, b_lz;
	uint64_t tmp;

	if (a == 0) return b;
	if (b == 0) return a;

	a_lz = __builtin_ctzll(a);
	b_lz = __builtin_ctzll(b);

	shift = (a_lz < b_lz) ? a_lz : b_lz;
	b >>= b_lz;

	while (a != 0) {
		a >>= a_lz;
		a_lz = __builtin_ctzll(b - a);
		tmp = (a > b) ? a - b : b - a;
		b = (a > b) ? b : a;
		a = tmp;
	}

	return b << shift;
}


uint64_t _dc_ext_gcd (uint64_t a, uint64_t b, int64_t* s, int64_t* t)
{
	uint64_t a2, a3, c0, c1, g;

	dc_mul_div(a2, c0, a, b);

	if (a2 < 1) {
		s[0] = 1;
		t[0] = 0;
		return b;
	}

	dc_mul_div(a3, c1, b, a2);

	if (a3 < 1) {
		s[0] = -c0;
		t[0] = 1;
		return a2;
	}

	g = _dc_ext_gcd (a2, a3, s, t);
	t[0] -= c1 * s[0];
	s[0] -= c0 * t[0];

	return g;
}


uint64_t dc_ext_gcd (uint64_t a, uint64_t b, int64_t* s, int64_t* t)
{
	if (a == 0) {
		s[0] = 0;
		if (b == 0) t[0] = 0;
		else t[0] = 1;
		return b;
	}

	if (b == 0) {
		s[0] = 1, t[0] = 0;
		return a;
	}

	if (a > b) return _dc_ext_gcd(a, b, t, s);
	else return _dc_ext_gcd(b, a, s, t);
}


uint64_t dc_binary_ext_gcd (uint64_t a, uint64_t b, int64_t *s, int64_t *t)
{
	uint64_t u, v, g = 1;
	int64_t A, B, C, D;

	if (a == 0) {
		s[0] = 0;
		if (b == 0) t[0] = 0;
		else t[0] = 1;
		return b;
	}

	if (b == 0) {
		s[0] = 1, t[0] = 0;
		return a;
	}

	while ((a & 1) == 0 && (b & 1) == 0) {
		a >>= 1;
		b >>= 1;
		g <<= 1;
	}

	u = a, v = b;
	A = 1, B = 0, C = 0, D = 1;

	while (u != 0) {
		while ((u & 1) == 0) {
			u >>= 1;
			if ((A & 1) == 0 && (B & 1) == 0) {
				A >>= 1;
				B >>= 1;
			} else {
				A = (A + (int64_t) b) / 2;
				B = (B - (int64_t) a) / 2;
			}
		}

		while ((v & 1) == 0) {
			v >>= 1;
			if ((C & 1) == 0 && (D & 1) == 0) {
				C >>= 1;
				D >>= 1;
			} else {
				C = (C + (int64_t) b) / 2;
				D = (D - (int64_t) a) / 2;
			}
		}

		if (u >= v) {
			u -= v;
			A -= C;
			B -= D;
		} else {
			v -= u;
			C -= A;
			D -= B;
		}
	}

	s[0] = C;
	t[0] = D;
	return g * v;
}
