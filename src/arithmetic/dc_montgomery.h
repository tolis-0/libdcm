#include <stdint.h>



/*	Montgomery multiplication and reduction for R = 2^64 */
static inline uint64_t dc_mul_redc_64 (uint64_t a, uint64_t b,
	uint64_t N, uint64_t Ninv)
{
#if __x86_64__
	uint64_t t;
	__asm__(
		"movq    %1,   %%rax \n\t"
		"mulq    %2          \n\t"	// T (rdx:rax) = A * B
		"movq   %%rax, %%rsi \n\t"
		"movq   %%rdx, %%rdi \n\t"	// make a copy of T (rdi:rsi)
		"imulq   %4,   %%rax \n\t"	// m (rax) = T (rax) * Ninv (mod R)
		"mulq    %3          \n\t"	// m*N (rdx:rax) = m (rax) * N
		"addq   %%rax, %%rsi \n\t"	// Low part of T+m*N is always 0
		"adcx   %%rdi, %%rdx \n\t"	// T+m*N (CF:rdx:rsi) = T (rdi:rsi) + m*N (rdx:rax)
		"movq   %%rdx,  %0   \n\t"	// t (CF:Out) = (T+m*N) / R
		"cmovcq  %3,   %%rsi \n\t"	// Use rsi as 0 for conditional move
		"cmp     %3,   %%rdx \n\t"
		"cmovaeq %3,   %%rsi \n\t"
		"subq   %%rsi,  %0       "	// Out = (t >= N) ? t - N : t
		: "=r" (t)
		: "r"(a), "r"(b), "r"(N), "r"(Ninv)
		: "rax", "rdx", "rdi", "rsi", "cc");
	return t;
#else
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
#endif
}



/*	Montgomery multiplication and reduction for R = 2^32 */
static inline uint32_t dc_mul_redc_32 (uint32_t a, uint32_t b,
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



/*	Calculates N' and R (mod N) for Montgomery form
	R = 2^k, 0 < k <= 64 and N < R and N odd */
static inline uint64_t dc_montgomery (uint8_t k, uint64_t N, uint64_t *x)
{
	uint64_t Ninv, R;

	if (k == 64) {
		R = (-N) % N;
		Ninv = dc_modinv_2pow64(N);
	} else {
		R = (1ULL << k) % N;
		Ninv = dc_modinv_2pow32(N); // implied k = 32
	}

	x[0] = R;
	return Ninv;
}
