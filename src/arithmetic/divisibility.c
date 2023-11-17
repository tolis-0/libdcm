#include <stdint.h>
#include "dc_arithmetic.h"


uint64_t dc_gcd (uint64_t u, uint64_t v)
{
	unsigned shift, u_lz, v_lz;
	uint64_t tmp;

	if (u == 0) return v;
	if (v == 0) return u;

	u_lz = __builtin_ctzll(u);
	v_lz = __builtin_ctzll(v);

	shift = (u_lz < v_lz) ? u_lz : v_lz;
	v >>= v_lz;

	while (u != 0) {
		u >>= u_lz;
		u_lz = __builtin_ctzll(v - u);
		tmp = (u > v) ? u - v : v - u;
		v = (u > v) ? v : u;
		u = tmp;
	}

	return v << shift;
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


uint64_t dc_ext_gcd (uint64_t u, uint64_t v, int64_t* s, int64_t* t)
{
	if (u == 0) {
		s[0] = 0;
		if (v == 0) t[0] = 0;
		else t[0] = 1;
		return v;
	}

	if (v == 0) {
		s[0] = 1;
		t[0] = 0;
		return u;
	}

	if (u > v) return _dc_ext_gcd(u, v, t, s);
	else return _dc_ext_gcd(v, u, s, t);
}


/* Binary Extended GCD from GMP implementation */
uint64_t dc_binary_ext_gcd (uint64_t u, uint64_t v, int64_t *s, int64_t *t)
{
	uint64_t s0, t0, s1, t1, Ug, Vg, Ugh, Vgh;
	unsigned i, zero_bits, shift, count;

	if (u == 0) {
		s[0] = 0;
		if (v == 0) t[0] = 0;
		else t[0] = 1;
		return v;
	}

	if (v == 0) {
		s[0] = 1, t[0] = 0;
		return u;
	}

	/* 	Maintain

		U = t1 u + t0 v
		V = s1 u + s0 v

		where U, V are the inputs (without any shared power of two),
		and the matrix has determinant ± 2^{shift}.
	*/

	s0 = 1, t0 = 0, s1 = 0, t1 = 1;

	zero_bits = __builtin_ctzll(u | v);

	u >>= zero_bits;
	v >>= zero_bits;

	if ((u & 1) == 0) {
		shift = __builtin_ctzll(u);

		u >>= shift;
		t1 <<= shift;
	} else if ((v & 1) == 0) {
		shift = __builtin_ctzll(v);

		v >>= shift;
		s0 <<= shift;
	} else {
		shift = 0;
	}

	while (u != v) {
		if (u > v) {
			u -= v;

			count = __builtin_ctzll(u);
			u >>= count;

			t0 += t1; t1 <<= count;
			s0 += s1; s1 <<= count;
		}  else {
			v -= u;

			count = __builtin_ctzll(v);
			v >>= count;

			t1 += t0; t0 <<= count;
			s1 += s0; s0 <<= count;
		}
		shift += count;
	}

	/* 	Now u = v = g = gcd (u,v). Compute U/g and V/g */
	Ug = t0 + t1;
	Vg = s0 + s1;

	Ugh = Ug/2 + (Ug & 1);
	Vgh = Vg/2 + (Vg & 1);

	/* 	Now 2^{shift} g = s0 U - t0 V. Get rid of the power of two, using
		s0 U - t0 V = (s0 + V/g) U - (t0 + U/g) V. */
	for (i = 0; i < shift; i++) {
		uint64_t mask = -((s0 | t0) & 1);

		s0 /= 2;
		t0 /= 2;
		s0 += mask & Vgh;
		t0 += mask & Ugh;
	}

	if (s0 > Vg - s0) {
		s0 -= Vg;
		t0 -= Ug;
	}

	s[0] = s0;
	t[0] = -t0;

	return v << zero_bits;
}


/* finds s and t such that 1 = s*2^64 - t*v where v is odd */
void dc_montgomery_gcd (uint64_t v, uint64_t *s, uint64_t *t)
{
	uint64_t s0, t0, mask;
	const uint64_t Ugh = 0x8000000000000000; // 2^63
	const uint64_t Vgh = v/2 + 1;
	unsigned i;

	s0 = 1;
	t0 = 0;

	for (i = 0; i < 64; i++) {
		mask = -(s0 & 1);

		s0 >>= 1;
		t0 >>= 1;
		s0 += mask & Vgh;
		t0 += mask & Ugh;
	}

	s[0] = s0;
	t[0] = t0;
}
