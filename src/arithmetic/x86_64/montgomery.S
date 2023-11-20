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
dc_mul_redc_64:

	movq	%rdi, %rax
	movq	%rdx, %r10
	mulq	%rsi		# T (rdx:rax) = a (rax) * b (rsi)
	movq	%rax, %rsi
	movq	%rdx, %rdi	# T (rdi:rsi) copy
	imulq	%rcx,  %rax	# m (rax) = T (rax) * N' (r9) (mod 2^64)
	mulq	%r10		# m*N (rdx:rax) = m (rax) * N (r10)
	xorq	%r11, %r11
	addq	%rax, %rsi
	adcx	%rdi, %rdx	# T+m*N (CF:rdx:rax) = T (rdi:rsi) + m*N (rdx:rax)
	movq	%rdx, %rax	# t (CF:rax) = (T+m*N)/2^64
	cmovcq	%r10, %r11
	cmpq	%r10, %rdx
	cmovaeq	%r10, %r11
	subq	%r11, %rax	# (t >= N) ? t - N : t
	ret



	.p2align 4
	.globl	dc_mul_redc_32
	.type	dc_mul_redc_32, @function
# uint32_t dc_mul_redc_32 (a (edi), b (esi), N (edx), Ninv (ecx))
dc_mul_redc_32:

	imulq	%rsi, %rdi	# T (rdi) = a (edi) * b (rsi)
	xorl	%eax, %eax
	movl	%edx, %esi	# N (esi) copy
	imull	%edi, %ecx	# m (ecx) = T (edi) * N' (ecx) (mod 2^32)
	imulq	%rsi, %rcx	# m*N (rcx) = m (rcx) * N (rsi)
	addq	%rcx, %rdi	# T+m*N (CF:rdi) = T (rdi) + m*N (rcx)
	setc	%al
	shrq	$32, %rdi
	salq	$32, %rax
	addq	%rdi, %rax
	subl	%edx, %edi
	cmpq	%rsi, %rax
	cmovnb	%edi, %eax
	ret



	.p2align 4
	.globl	dc_mon_expmod
	.type	dc_mon_expmod, @function
dc_mon_expmod:
	ret



	.p2align 4
	.globl	dc_montgomery
	.type	dc_montgomery, @function
# uint64_t dc_montgomery (k (dil), N (rsi), *x (rdx))
dc_montgomery:

	cmpq	%rsi, _N(%rip)
	jne .Lnew_vars
	cmpb	%dil, _k(%rip)
	jne .Lnew_vars

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
	subq	$16, %rsp
	xorq	%r8, %r8
	movb	%dil, %cl
	cmpb	$64, %dil
	setne	%al				# rax = (k == 64) ? 0 : 1
	cmoveq	%rsi, %r8		# r8 = (k == 64) ? N : 0
	shlq	%cl, %rax
	subq	%r8, %rax		# rax = (k == 64) ? -N : 2^k
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
