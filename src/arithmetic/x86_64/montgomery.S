	.local	_N
	.comm	_N, 8, 8
	.local	_Ninv
	.comm	_Ninv, 8, 8
	.local	_R
	.comm	_R, 8, 8
	.local	_k
	.comm	_k, 1, 1



	.p2align 4
	.globl	dc_mul_redc_64
	.type	dc_mul_redc_64, @function
# uint64_t dc_mul_redc_64 (a (rdi), b (rsi), N (rdx), Ninv (rcx))
# Montgomery reduction (REDC) of product a*b with R = 2^64
dc_mul_redc_64:

	movq	%rdi, %rax
	movq	%rdx, %r10
	mulq	%rsi		# T (rdx:rax) = a (rax) * b (rsi)
	movq	%rax, %rsi
	movq	%rdx, %rdi	# T (rdi:rsi) copy
	imulq	%rcx, %rax	# m (rax) = T (rax) * N' (r9) (mod R)
	mulq	%r10		# m*N (rdx:rax) = m (rax) * N (r10)
	xorq	%r11, %r11
	addq	%rax, %rsi
	adcx	%rdi, %rdx	# T+m*N (CF:rdx:rax) = T (rdi:rsi) + m*N (rdx:rax)
	movq	%rdx, %rax	# t (CF:rax) = (T+m*N) / R
	cmovcq	%r10, %r11
	cmpq	%r10, %rdx
	cmovaeq	%r10, %r11
	subq	%r11, %rax	# (t >= N) ? t - N : t
	ret



	.p2align 4
	.globl	dc_mul_redc_32
	.type	dc_mul_redc_32, @function
# uint32_t dc_mul_redc_32 (a (edi), b (esi), N (edx), Ninv (ecx))
# Montgomery reduction (REDC) of product a*b with R = 2^32
dc_mul_redc_32:

	imulq	%rsi, %rdi	# T (rdi) = a (edi) * b (rsi)
	xorl	%eax, %eax
	movl	%edx, %esi	# N (esi = edx) copy
	imull	%edi, %ecx	# m (ecx) = T (edi) * N' (ecx) (mod R)
	imulq	%rsi, %rcx	# m*N (rcx) = m (rcx) * N (rsi)
	addq	%rcx, %rdi	# T+m*N (CF:rdi) = T (rdi) + m*N (rcx)
	rcrq	$1,   %rdi
	shrq	$31,  %rdi	# t (rdi) = (T+m*N) / R
	cmpq	%rsi, %rdi
	cmovael	%esi, %eax
	subl	%eax, %edi	# (t >= N) ? t - N : t
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

	# CASE M < 0x100000000
	movl	%edx, %esi
	movb	$32,  %dil
	leaq	0(%rsp), %rdx
	call	dc_montgomery@PLT
	movq	0(%rsp), %r8
	movq	%rax, %r9
	movq	%rbx, %rax
	mulq	%r8
	divq	%r9
	addq	$8,   %rsp
	movl	%edx, %ebx
.Lforloop32:
	# x (r8/r8d), b (rbx/ebx), e (r12), M (rbp/ebp), M' (r9d)
	test 	%r12, %r12
	jz		.Lrevert32	# case e == 0
	testb	$1, %r12b
	je		.Leven32	# case e is even
# inline dc_mul_redc_32
	imulq	%rbx, %r8	# T (r8) = x (r8) * b (rbx)
	xorl	%eax, %eax
	movl	%r9d, %ecx
	imull	%r8d, %ecx	# m (ecx) = T (r8d) * M' (r9d=ecx) (mod R)
	imulq	%rbp, %rcx	# m*M (rcx) = m (rcx/ecx) * M (rbp)
	addq	%rcx, %r8	# T+m*M (CF:r8) = T (r8) + m*M (rcx)
	rcrq	$1,   %r8
	shrq	$31,  %r8	# t (r8) = (T+m*M) / R
	cmpq	%rbp, %r8
	cmovael	%ebp, %eax
	subl	%eax, %r8d	# x = (t >= M) ? t - M : t
.Leven32:
	imulq	%rbx, %rbx	# T (rbx) = b (rbx) * b (rbx)
	xorl	%eax, %eax
	movl	%r9d, %ecx
	imull	%ebx, %ecx	# m (ecx) = T (ebx) * M' (r9d=ecx) (mod R)
	imulq	%rbp, %rcx	# m*M (rcx) = m (rcx/ecx) * M (rbp)
	addq	%rcx, %rbx	# T+m*M (CF:rbx) = T (rbx) + m*M (rcx)
	rcrq	$1,   %rbx
	shrq	$31,  %rbx	# t (rbx) = (T+m*M) / R
	cmpq	%rbp, %rbx
	cmovael	%ebp, %eax
	subl	%eax, %ebx	# b = (t >= M) ? t - M : t
	shrq	$1, %r12	# e >>= 1
	jmp 	.Lforloop32
.Lrevert32:
	imulq	$1, %r8
	xorl	%eax, %eax
	movl	%r9d, %ecx
	imull	%r8d, %ecx
	imulq	%rbp, %rcx
	addq	%rcx, %r8
	rcrq	$1,   %r8
	shrq	$31,  %r8
	cmpq	%rbp, %r8
	cmovael	%ebp, %eax
	subl	%eax, %r8d
	movl	%r8d, %eax
	popq	%rbp
	popq	%r12
	popq	%rbx
	ret

.Lexpmod64:
	# CASE M >= 0x100000000
	movq	%rdx, %rsi
	movb	$64,  %dil
	leaq	0(%rsp), %rdx
	call	dc_montgomery@PLT
	movq	0(%rsp), %r8
	movq	%rax, %r9
	movq	%rbx, %rax
	mulq	%r8
	divq	%r9
	addq	$8,   %rsp
	movq	%rdx, %rbx
.Lforloop64:
	# x (r8), b (rbx), e (r12), M (rbp), M' (r9)
	test 	%r12, %r12
	jz		.Lrevert64	# case e == 0
	testb	$1, %r12b
	je		.Leven64	# case e is even
# inline dc_mul_redc_64
	movq	%rbx, %rax
	mulq	%r8			# T (rdx:rax) = x (r8) * b (rbx)
	movq	%rax, %rsi
	movq	%rdx, %rdi	# T (rdi:rsi) copy
	imulq	%r9,  %rax	# m (rax) = T (rax) * M' (r9) (mod R)
	mulq	%rbp		# m*M (rdx:rax) = m (rax) * M (rbp)
	xorq	%r11, %r11
	addq	%rax, %rsi
	adcx	%rdi, %rdx	# T+m*M (CF:rdx:rax) = T (rdi:rsi) + m*M (rdx:rax)
	movq	%rdx, %r8	# t (CF:r8) = (T+m*M) / R
	cmovcq	%rbp, %r11
	cmpq	%rbp, %rdx
	cmovaeq	%rbp, %r11
	subq	%r11, %r8	# x = (t >= M) ? t - M : t
.Leven64:
	movq	%rbx, %rax
	mulq	%rbx		# T (rdx:rax) = b (rbx) * b (rbx)
	movq	%rax, %rsi
	movq	%rdx, %rdi	# T (rdi:rsi) copy
	imulq	%r9, %rax	# m (rax) = T (rax) * M' (r9) (mod R)
	mulq	%rbp		# m*M (rdx:rax) = m (rax) * M (rbp)
	xorq	%r11, %r11
	addq	%rax, %rsi
	adcx	%rdi, %rdx	# T+m*M (CF:rdx:rax) = T (rdi:rsi) + m*M (rdx:rax)
	movq	%rdx, %rbx	# t (CF:rbx) = (T+m*M) / R
	cmovcq	%rbp, %r11
	cmpq	%rbp, %rdx
	cmovaeq	%rbp, %r11
	subq	%r11, %rbx	# x = (t >= M) ? t - M : t
	shrq	$1, %r12	# e >>= 1
	jmp 	.Lforloop64
.Lrevert64:
	movq	$1, %rax
	mulq	%r8
	movq	%rax, %rsi
	movq	%rdx, %rdi
	imulq	%r9, %rax
	mulq	%rbp
	xorq	%r11, %r11
	addq	%rax, %rsi
	adcx	%rdi, %rdx
	movq	%rdx, %rax
	cmovcq	%rbp, %r11
	cmpq	%rbp, %rdx
	cmovaeq	%rbp, %r11
	subq	%r11, %rax
	popq	%rbp
	popq	%r12
	popq	%rbx
	ret
