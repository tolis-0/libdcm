	.local	_rbit
	.comm	_rbit, 8, 8
	.local	_un_i
	.comm	_un_i, 8, 8
	.local	_mask
	.comm	_mask, 8, 8
	.local	cached_n
	.comm	cached_n, 8, 8



	.p2align 4
	.globl	dc_montgomery_mul_mod
	.type	dc_montgomery_mul_mod, @function
# uint64_t dc_montgomery_mul_mod (uint64_t a (rdi), uint64_t b (rsi))
dc_montgomery_mul_mod:

	movq	%rdi, %rax
	mulq	%rsi		# t (rdx:rax) = a (rax) * b (rsi)
	movq	_rbit(%rip), %rcx
	movq	_un_i(%rip), %r9
	movq	cached_n(%rip), %r10
	movq	%rax, %rsi
	movq	%rdx, %rdi	# t (rdi:rsi) copy
	cmpq	$64, %rcx
	je	.L64_bit

	# _rbit < 64
	movq	_mask(%rip), %r11
	andq	%r11, %rax	# m (rax) = t & _mask (r11)
	mulq	%r9			# m (rdx:rax) = m (rax) * _un_i (r9)
	andq	%r11, %rax	# m (rax) &= _mask (r11)
	mulq	%r10		# m*n (rdx:rax) = m (rax) * cached_n (r10)
	addq	%rsi, %rax
	adcx	%rdi, %rdx	# rem128 (rdx:rax) = t (rdi:rsi) + (m*n) (rdx:rax)
	shrdq	%cl, %rdx, %rax	# rem128 (rax) >>= _rbit;
	cmpq	%r10, %rax
	jae .Lsub
	ret

.L64_bit:

	# _rbit = 64
	mulq	%r9			# m (rdx:rax) = m (rax) * _un_i (r9)
	mulq	%r10		# m (rdx:rax) = m (rax) * cached_n (r10)
	addq	%rsi, %rax
	adcx	%rdi, %rdx	# rem128 (CF:rdx:rax) = t (rdi:rsi) + m (rdx:rax)
	movq	%rdx, %rax
	jc	.Lsub
	cmpq	%r10, %rdx
	jae .Lsub
	ret

.Lsub:
	subq	%r10, %rax	# rem (rax) -= cached_n (r10)
	ret



	.p2align 4
	.globl	dc_montgomery_cached
	.type	dc_montgomery_cached, @function
# void dc_montgomery_cached (uint64_t n (rdi), uint64_t *x (rsi))
dc_montgomery_cached:

	cmpq	%rdi, cached_n(%rip)
	je .Lcached_ret

	subq	$24, %rsp
	movq	%rdi, cached_n(%rip)	# cached_n = n;
	bsr		%rdi, %rcx
	inc		%rcx
	movq	%rcx, _rbit(%rip)
	cmpq	$64, %rcx
	je .L64_set

	# _rbit < 64
	movq	$1, %rdx
	shlq	%cl, %rdx				# r (rdx) = 1 << _rbit (rcx)
	movq	%rdx, %rax
	subq	%rdi, %rax				# r - n (rax)
	movq	%rax, (%rsi)			# x[0] = r - n
	movq	%rdi, %rsi
	movq	%rdx, %rdi
	movq	%rdx, 16(%rsp)
	leaq	0(%rsp), %rdx
	leaq	8(%rsp), %rcx
	# dc_ext_gcd(_mask (rdi), n (rsi), &tmp (rdx), &n_i (rcx));
	call	dc_ext_gcd@PLT
	movq	8(%rsp), %rcx			# n_i (rcx)
	xorl	%eax, %eax
	movq	16(%rsp), %rdx			# r (rdx)
	testq	%rcx, %rcx
	cmovnsq	%rdx, %rax				# (n_i < 0) ? 0 : r (rax)
	decq	%rdx
	movq	%rdx, _mask(%rip)
	subq	%rcx, %rax				# (rax) - n_i (rcx)
	movq	%rax, _un_i(%rip)
	addq	$24, %rsp
	ret

.L64_set:

	# _rbit = 64
	movq	%rdi, %rdx
	negq	%rdx
	movq	%rdx, (%rsi)
	movq	%rdx, %rsi
	leaq	0(%rsp), %rdx
	leaq	8(%rsp), %rcx
	# dc_ext_gcd(n (rdi), -n (rsi), &n_i (rdx), &tmp (rcx));
	call	dc_ext_gcd@PLT
	movq	8(%rsp), %rcx			# tmp (rcx)
	movq	0(%rsp), %rdx			# n_i (rdx)
	subq	%rdx, %rcx
	movq	%rcx, _un_i(%rip)
	addq	$24, %rsp
	ret

.Lcached_ret:

	# montgomery_cached_return		n (rdi), x (rsi)
	cmpq	$64, _rbit(%rip)
	je .L64_ret
	movq	_mask(%rip), %rax
	incq	%rax
	subq	%rdi, %rax
	movq	%rax, (%rsi)
	ret
.L64_ret:
	negq	%rdi
	movq	%rdi, (%rsi)
	ret
