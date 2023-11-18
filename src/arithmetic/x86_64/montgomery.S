# This algorithm uses r = 2^64 such that division and modulo with r
# is choosing rdx or rax register respectively
	.local	_un_i
	.comm	_un_i, 8, 8
	.local	cached_n
	.comm	cached_n, 8, 8
	.local	r_mod_n
	.comm	r_mod_n, 8, 8



	.p2align 4
	.globl	dc_redc_64bit
	.type	dc_redc_64bit, @function
# uint64_t dc_redc_64bit (uint64_t a (rdi), uint64_t b (rsi))
dc_redc_64bit:

	movq	%rdi, %rax
	mulq	%rsi		# t (rdx:rax) = a (rax) * b (rsi)
	movq	_un_i(%rip), %r9
	movq	cached_n(%rip), %r10
	movq	%rax, %rsi
	movq	%rdx, %rdi	# t (rdi:rsi) copy
	imulq	%r9,  %rax	# m (rax) = t (rax) * n' (r9) (mod 2^64)
	mulq	%r10		# m*n (rdx:rax) = m (rax) * n (r10)
	xorq	%r11, %r11
	addq	%rax, %rsi
	adcx	%rdi, %rdx	# t+m*n (CF:rdx:rax) = t (rdi:rsi) + m*n (rdx:rax)
	movq	%rdx, %rax	# u (CF:rax) = (t+m*n)/2^64
	cmovcq	%r10, %r11
	cmpq	%r10, %rdx
	cmovaeq	%r10, %r11
	subq	%r11, %rax	# (u >= n) ? u - n : u
	ret



	.p2align 4
	.globl	dc_montgomery_64bit
	.type	dc_montgomery_64bit, @function
# void dc_montgomery_64bit (uint64_t n (rdi), uint64_t *x (rsi))
dc_montgomery_64bit:

	cmpq	%rdi, cached_n(%rip)
	je .Lcached_ret

	subq	$16, %rsp
	movq	%rdi, cached_n(%rip)	# cached_n = n;
	movq	$1, %rdx
	xorq	%rax, %rax				# r (rdx:rax) = 2^64
	divq	%rdi					# x (rdx) = r (mod n)
	movq	%rdx, r_mod_n(%rip)
	movq	%rdx, (%rsi)
	leaq	0(%rsp), %rsi
	leaq	8(%rsp), %rdx
	# dc_2pow64_gcd (n (rdi), &s (rsi), &t (rdx))
	call	dc_2pow64_gcd@PLT
	movq	8(%rsp), %rax			# n' (rax), r' * 2^64 - n' * n = 1
	movq	%rax, _un_i(%rip)
	addq	$16, %rsp
	retq

.Lcached_ret:

	# montgomery_cached_return		n (rdi), x (rsi)
	movq	r_mod_n(%rip), %rax
	movq	%rax, (%rsi)
	retq
