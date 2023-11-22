	.local	_N
	.comm	_N, 8, 8
	.local	_Ninv
	.comm	_Ninv, 8, 8
	.local	_R
	.comm	_R, 8, 8
	.local	_k
	.comm	_k, 1, 1



# Inputs (Constant):	A, B, N, Ninv
# Output:	Out
# Volatile Registers:	rax, rdx, rsi, rdi, r11
# Invalid Registers for A: rax
# Invalid Registers for Ninv: rax, rdx, rsi, rdi
# Invalid Registers for N: rax, rdx, rsi, rdi, r11
# Invalid Registers for Out: r11
# A, B and Out don't have to be different registers
.macro  mul_redc_64 	A, B, N, Ninv, Out
	movq	\B,   %rax
	mulq	\A			# T (rdx:rax) = A * B
	movq	%rax, %rsi
	movq	%rdx, %rdi	# T (rdi:rsi) copy
	imulq	\Ninv,%rax	# m (rax) = T (rax) * Ninv (mod R)
	mulq	\N			# m*N (rdx:rax) = m (rax) * N
	xorq	%r11, %r11
	addq	%rax, %rsi
	adcx	%rdi, %rdx	# T+m*N (CF:rdx:rax) = T (rdi:rsi) + m*N (rdx:rax)
	movq	%rdx, \Out	# t (CF:Out) = (T+m*N) / R
	cmovcq	\N, %r11
	cmpq	\N, %rdx
	cmovaeq	\N, %r11
	subq	%r11, \Out	# Out = (t >= N) ? t - N : t
.endm



# Inputs (Volatile):	A, Ninv
# Inputs (Constant):	B, N
# Output:	A
# Volatile Registers:	r11 (Don't use for A, Ninv, N)
.macro  mul_redc_32 	A64, A32, B64, N64, N32, Ninv64, Ninv32
	imulq	\B64, \A64	# T (rdi) = A * B
	xorl	%r11d, %r11d
	imull	\A32, \Ninv32	# m = T (edi) * N' (ecx) (mod R)
	imulq	\N64, \Ninv64	# m*N = m (rcx) * N
	addq	\Ninv64, \A64	# T+m*N (CF:rdi) = T (rdi) + m*N (rcx)
	rcrq	$1,   \A64
	shrq	$31,  \A64		# t (rdi) = (T+m*N) / R
	cmpq	\N64, \A64
	cmovael	\N32, %r11d
	subl	%r11d, \A32		# (t >= N) ? t - N : t
.endm



	.p2align 4
	.globl	dc_mul_redc_64
	.type	dc_mul_redc_64, @function
# uint64_t dc_mul_redc_64 (a (rdi), b (rsi), N (rdx), Ninv (rcx))
# Montgomery reduction (REDC) of product a*b with R = 2^64
dc_mul_redc_64:

	movq	%rdx, %r10
	mul_redc_64 %rdi, %rsi, %r10, %rcx, %rax
	ret



	.p2align 4
	.globl	dc_mul_redc_32
	.type	dc_mul_redc_32, @function
# uint32_t dc_mul_redc_32 (a (edi), b (esi), N (edx), Ninv (ecx))
# Montgomery reduction (REDC) of product a*b with R = 2^32
dc_mul_redc_32:

	mul_redc_32 %rdi, %edi, %rsi, %rdx, %edx, %rcx, %ecx
	movl	%edi, %eax
	ret



	.p2align 4
	.globl	dc_montgomery
	.type	dc_montgomery, @function
# uint64_t dc_montgomery (k (dil), N (rsi), *x (rdx))
dc_montgomery:

	cmpq	%rsi, _N(%rip)
	jne 	.Lnew_vars
	cmpb	%dil, _k(%rip)
	jne 	.Lnew_vars

	# montgomery_cached_return
	movq	_R(%rip), %rsi
	movq	_Ninv(%rip), %rax
	movq	%rsi, (%rdx)
	ret

.Lnew_vars:
	movq	%rsi, _N(%rip)	# cached Ν = Ν;
	movb	%dil, _k(%rip)	# cached k = k;
	movq	%rdx, %r9
	xorq	%rax, %rax
	xorq	%rdx, %rdx
	subq	$16,  %rsp
	xorq	%r8,  %r8
	movb	%dil, %cl
	cmpb	$64,  %dil
	setne	%al				# rax = (k == 64) ? 0 : 1
	cmoveq	%rsi, %r8		# r8 = (k == 64) ? N : 0
	shlq	%cl,  %rax
	subq	%r8,  %rax		# rax = (k == 64) ? -N : 2^k
	divq	%rsi			# x (rdx) = R (rdx:rax) (mod N (rsi))
	movq	%rdx, _R(%rip)
	movq	%rdx, (%r9)
	leaq	0(%rsp), %rcx
	leaq	8(%rsp), %rdx
	# dc_2powr_gcd (k (dil), v (rsi), *s (rdx), *t (rcx))
	call	dc_2powr_gcd@PLT
	movq	0(%rsp), %rax
	movq	%rax, _Ninv(%rip)
	addq	$16, %rsp
	ret



	.p2align 4
	.globl	dc_monexp_mod
	.type	dc_monexp_mod, @function
# uint64_t dc_monexp_mod (base (rdi), exp (rsi), M (rdx))
# Montgomery Modular Exponentiation (for odd M)
dc_monexp_mod:

	pushq	%rbx
	movq	%rdi, %rbx	# base (rbx)
	pushq	%r12
	movq	%rsi, %r12	# exp (r12)
	pushq	%rbp
	movq	%rdx, %rbp	# M (rbp)
	movabsq	$4294967296, %rax
	subq	$8,   %rsp
	cmpq	%rax, %rdx
	jae		.Lexpmod64

	# case M < 0x100000000
	movl	%edx, %esi
	movb	$32,  %dil
	leaq	0(%rsp), %rdx
	call	dc_montgomery@PLT
	movq	0(%rsp), %r8
	movq	%rax, %r9
	movq	%rbx, %rax
	mulq	%r8
	divq	%rbp
	addq	$8,   %rsp
	movl	%edx, %ebx
.Lforloop32:
	# x (r8/r8d), b (rbx/ebx), e (r12), M (rbp/ebp), M' (r9/r9d)
	test 	%r12, %r12
	jz		.Lrevert32	# case e == 0
	testb	$1, %r12b
	je		.Leven32	# case e is even
# inline dc_mul_redc_32
	movq	%r9, %rax
	mul_redc_32 %r8, %r8d, %rbx, %rbp, %ebp, %rax, %eax
.Leven32:
	movq	%r9, %rax
	mul_redc_32 %rbx, %ebx, %rbx, %rbp, %ebp, %rax, %eax
	shrq	$1, %r12	# e >>= 1
	jmp 	.Lforloop32
.Lrevert32:
	mul_redc_32 %r8, %r8d, $1, %rbp, %ebp, %r9, %r9d
	movl	%r8d, %eax
	popq	%rbp
	popq	%r12
	popq	%rbx
	ret

.Lexpmod64:
	# case M >= 0x100000000
	movq	%rdx, %rsi
	movb	$64,  %dil
	leaq	0(%rsp), %rdx
	call	dc_montgomery@PLT
	movq	0(%rsp), %r8
	movq	%rax, %r9
	movq	%rbx, %rax
	mulq	%r8
	divq	%rbp
	addq	$8,   %rsp
	movq	%rdx, %rbx
.Lforloop64:
	# x (r8), b (rbx), e (r12), M (rbp), M' (r9)
	test 	%r12, %r12
	jz		.Lrevert64	# case e == 0
	testb	$1, %r12b
	je		.Leven64	# case e is even
	# inline dc_mul_redc_64
	mul_redc_64 %r8, %rbx, %rbp, %r9, %r8
.Leven64:
	# inline dc_mul_redc_64
	mul_redc_64 %rbx, %rbx, %rbp, %r9, %rbx
	shrq	$1, %r12	# e >>= 1
	jmp 	.Lforloop64
.Lrevert64:
	# inline dc_mul_redc_64
	mul_redc_64 %r8, $1, %rbp, %r9, %rax
	popq	%rbp
	popq	%r12
	popq	%rbx
	ret
