	.local	_un_i
	.comm	_un_i, 8, 8
	.local	cached_n
	.comm	cached_n, 8, 8
	.local	r_mod_n
	.comm	r_mod_n, 8, 8


	.p2align 4
	.globl	dc_montgomery_mul_mod
	.type	dc_montgomery_mul_mod, @function
# uint64_t dc_montgomery_mul_mod (uint64_t a (rdi), uint64_t b (rsi))
dc_montgomery_mul_mod:

	movq	%rdi, %rax
	mulq	%rsi		# t (rdx:rax) = a (rax) * b (rsi)
	movq	_un_i(%rip), %r9
	movq	cached_n(%rip), %r10
	movq	%rax, %rsi
	movq	%rdx, %rdi	# t (rdi:rsi) copy
	# _rbit = 64
	mulq	%r9			# m (rdx:rax) = m (rax) * _un_i (r9)
	mulq	%r10		# m (rdx:rax) = m (rax) * cached_n (r10)
	xorq	%r11, %r11
	addq	%rsi, %rax
	adcx	%rdi, %rdx	# rem128 (CF:rdx:rax) = t (rdi:rsi) + m (rdx:rax)
	movq	%rdx, %rax
	cmovcq	%r10, %r11
	cmpq	%r10, %rdx
	cmovaeq	%r10, %r11
	subq	%r11, %rax	# (u >= n) ? u - n : u
	ret



	.p2align 4
	.globl	dc_montgomery_cached
	.type	dc_montgomery_cached, @function
# void dc_montgomery_cached (uint64_t n (rdi), uint64_t *x (rsi))
dc_montgomery_cached:

	cmpq	%rdi, cached_n(%rip)
	je .Lcached_ret

	subq	$16, %rsp
	movq	%rdi, cached_n(%rip)	# cached_n = n;
	xorq	%rdx, %rdx
	movq	%rdi, %rax
	negq	%rax
	movq	%rax, %r9
	divq	%rdi					# n (rdi), x (rsi), r-n (rax)
	movq	%rdx, r_mod_n(%rip)
	movq	%rdx, (%rsi)
	movq	%r9, %rsi
	leaq	0(%rsp), %rdx
	leaq	8(%rsp), %rcx
	# dc_ext_gcd(n (rdi), r-n (rsi), &n_i (rdx), &tmp (rcx));
	call	dc_ext_gcd@PLT
	movq	8(%rsp), %rcx			# tmp (rcx)
	movq	0(%rsp), %rdx			# n_i (rdx)
	subq	%rdx, %rcx
	movq	%rcx, _un_i(%rip)
	addq	$16, %rsp
	ret

.Lcached_ret:

	# montgomery_cached_return		n (rdi), x (rsi)
	movq	r_mod_n(%rip), %rax
	movq	%rax, (%rsi)
	ret
