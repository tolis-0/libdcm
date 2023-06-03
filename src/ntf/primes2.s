	.file	"primes.c"
	.text
	.globl	s3_prime
	.type	s3_prime, @function
s3_prime:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$1, -24(%rbp)
	ja	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	cmpq	$2, -24(%rbp)
	je	.L4
	cmpq	$3, -24(%rbp)
	jne	.L5
.L4:
	movl	$1, %eax
	jmp	.L3
.L5:
	movq	-24(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	je	.L6
	movq	-24(%rbp), %rcx
	movabsq	$-6148914691236517205, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	%rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L7
.L6:
	movl	$0, %eax
	jmp	.L3
.L7:
	fildq	-24(%rbp)
	cmpq	$0, -24(%rbp)
	jns	.L8
	fldt	.LC0(%rip)
	faddp	%st, %st(1)
.L8:
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	call	sqrtl@PLT
	addq	$16, %rsp
	fnstcw	-26(%rbp)
	movzwl	-26(%rbp), %eax
	orb	$12, %ah
	movw	%ax, -28(%rbp)
	fldcw	-28(%rbp)
	frndint
	fldcw	-26(%rbp)
	fldt	.LC1(%rip)
	fxch	%st(1)
	fcomi	%st(1), %st
	fstp	%st(1)
	jnb	.L9
	fldcw	-28(%rbp)
	fistpq	-8(%rbp)
	fldcw	-26(%rbp)
	jmp	.L10
.L9:
	fldt	.LC1(%rip)
	fsubrp	%st, %st(1)
	fldcw	-28(%rbp)
	fistpq	-8(%rbp)
	fldcw	-26(%rbp)
	movabsq	$-9223372036854775808, %rax
	xorq	%rax, -8(%rbp)
.L10:
	movq	-8(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	$5, -16(%rbp)
	jmp	.L11
.L14:
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L12
	movl	$0, %eax
	jmp	.L3
.L12:
	addq	$2, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L13
	movl	$0, %eax
	jmp	.L3
.L13:
	addq	$4, -16(%rbp)
.L11:
	movq	-16(%rbp), %rax
	cmpq	%rax, -8(%rbp)
	jnb	.L14
	movl	$1, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	s3_prime, .-s3_prime
	.globl	s5_prime_st97
	.type	s5_prime_st97, @function
s5_prime_st97:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$1, -24(%rbp)
	ja	.L16
	movl	$0, %eax
	jmp	.L17
.L16:
	cmpq	$9408, -24(%rbp)
	ja	.L18
	movl	$1, %eax
	jmp	.L17
.L18:
	movq	-24(%rbp), %rcx
	movabsq	$5895351198814392785, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$6, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L19
	movl	$0, %eax
	jmp	.L17
.L19:
	fildq	-24(%rbp)
	cmpq	$0, -24(%rbp)
	jns	.L20
	fldt	.LC0(%rip)
	faddp	%st, %st(1)
.L20:
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	call	sqrtl@PLT
	addq	$16, %rsp
	fnstcw	-26(%rbp)
	movzwl	-26(%rbp), %eax
	orb	$12, %ah
	movw	%ax, -28(%rbp)
	fldcw	-28(%rbp)
	frndint
	fldcw	-26(%rbp)
	fldt	.LC1(%rip)
	fxch	%st(1)
	fcomi	%st(1), %st
	fstp	%st(1)
	jnb	.L21
	fldcw	-28(%rbp)
	fistpq	-8(%rbp)
	fldcw	-26(%rbp)
	jmp	.L22
.L21:
	fldt	.LC1(%rip)
	fsubrp	%st, %st(1)
	fldcw	-28(%rbp)
	fistpq	-8(%rbp)
	fldcw	-26(%rbp)
	movabsq	$-9223372036854775808, %rax
	xorq	%rax, -8(%rbp)
.L22:
	movq	-8(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	$101, -16(%rbp)
	jmp	.L23
.L32:
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L24
	movl	$0, %eax
	jmp	.L17
.L24:
	addq	$2, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L25
	movl	$0, %eax
	jmp	.L17
.L25:
	addq	$4, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L26
	movl	$0, %eax
	jmp	.L17
.L26:
	addq	$2, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L27
	movl	$0, %eax
	jmp	.L17
.L27:
	addq	$4, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L28
	movl	$0, %eax
	jmp	.L17
.L28:
	addq	$6, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L29
	movl	$0, %eax
	jmp	.L17
.L29:
	addq	$2, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L30
	movl	$0, %eax
	jmp	.L17
.L30:
	addq	$6, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	divq	-16(%rbp)
	movq	%rdx, %rax
	testq	%rax, %rax
	jne	.L31
	movl	$0, %eax
	jmp	.L17
.L31:
	addq	$4, -16(%rbp)
.L23:
	movq	-16(%rbp), %rax
	cmpq	%rax, -8(%rbp)
	jnb	.L32
	movl	$1, %eax
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	s5_prime_st97, .-s5_prime_st97
	.globl	mr_prime
	.type	mr_prime, @function
mr_prime:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$1, -24(%rbp)
	ja	.L34
	movl	$0, %eax
	jmp	.L35
.L34:
	cmpq	$2, -24(%rbp)
	jne	.L36
	movl	$1, %eax
	jmp	.L35
.L36:
	movq	-24(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	jne	.L37
	movl	$0, %eax
	jmp	.L35
.L37:
	movq	-24(%rbp), %rax
	subq	$1, %rax
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L38
.L39:
	shrq	-8(%rbp)
	addl	$1, -12(%rbp)
.L38:
	movq	-8(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	je	.L39
	cmpq	$9080190, -24(%rbp)
	ja	.L40
	cmpq	$31, -24(%rbp)
	je	.L41
	cmpq	$73, -24(%rbp)
	jne	.L42
.L41:
	movl	$1, %eax
	jmp	.L35
.L42:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$31, %ecx
	movq	%rax, %rdi
	call	mr_prime_test
	testl	%eax, %eax
	je	.L43
	movl	$0, %eax
	jmp	.L35
.L43:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$73, %ecx
	movq	%rax, %rdi
	call	mr_prime_test
	testl	%eax, %eax
	je	.L44
	movl	$0, %eax
	jmp	.L35
.L44:
	movl	$1, %eax
	jmp	.L35
.L40:
	movabsq	$4759123140, %rax
	cmpq	-24(%rbp), %rax
	jb	.L45
	movl	$4294967294, %eax
	cmpq	-24(%rbp), %rax
	jb	.L46
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$7, %ecx
	movq	%rax, %rdi
	call	mr_prime_test
	testl	%eax, %eax
	je	.L47
	movl	$0, %eax
	jmp	.L35
.L47:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$2, %ecx
	movq	%rax, %rdi
	call	mr_prime_test
	testl	%eax, %eax
	je	.L48
	movl	$0, %eax
	jmp	.L35
.L48:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$61, %ecx
	movq	%rax, %rdi
	call	mr_prime_test
	testl	%eax, %eax
	je	.L49
	movl	$0, %eax
	jmp	.L35
.L49:
	movl	$1, %eax
	jmp	.L35
.L46:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$7, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L50
	movl	$0, %eax
	jmp	.L35
.L50:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$2, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L51
	movl	$0, %eax
	jmp	.L35
.L51:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$61, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L52
	movl	$0, %eax
	jmp	.L35
.L52:
	movl	$1, %eax
	jmp	.L35
.L45:
	movabsq	$1122004669632, %rax
	cmpq	-24(%rbp), %rax
	jb	.L53
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$13, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L54
	movl	$0, %eax
	jmp	.L35
.L54:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$2, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L55
	movl	$0, %eax
	jmp	.L35
.L55:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$23, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L56
	movl	$0, %eax
	jmp	.L35
.L56:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$1662803, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L57
	movl	$0, %eax
	jmp	.L35
.L57:
	movl	$1, %eax
	jmp	.L35
.L53:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$11, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L58
	movl	$0, %eax
	jmp	.L35
.L58:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$7, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L59
	movl	$0, %eax
	jmp	.L35
.L59:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$5, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L60
	movl	$0, %eax
	jmp	.L35
.L60:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$3, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L61
	movl	$0, %eax
	jmp	.L35
.L61:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$2, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L62
	movl	$0, %eax
	jmp	.L35
.L62:
	movabsq	$2152302898746, %rax
	cmpq	-24(%rbp), %rax
	jb	.L63
	movl	$1, %eax
	jmp	.L35
.L63:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$13, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L64
	movl	$0, %eax
	jmp	.L35
.L64:
	movabsq	$3474749660382, %rax
	cmpq	-24(%rbp), %rax
	jb	.L65
	movl	$1, %eax
	jmp	.L35
.L65:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$17, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L66
	movl	$0, %eax
	jmp	.L35
.L66:
	movabsq	$341550071728320, %rax
	cmpq	-24(%rbp), %rax
	jb	.L67
	movl	$1, %eax
	jmp	.L35
.L67:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$19, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L68
	movl	$0, %eax
	jmp	.L35
.L68:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$23, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L69
	movl	$0, %eax
	jmp	.L35
.L69:
	movabsq	$3825123056546413050, %rax
	cmpq	-24(%rbp), %rax
	jb	.L70
	movl	$1, %eax
	jmp	.L35
.L70:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$29, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L71
	movl	$0, %eax
	jmp	.L35
.L71:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$31, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L72
	movl	$0, %eax
	jmp	.L35
.L72:
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$37, %ecx
	movq	%rax, %rdi
	call	ext_mr_prime_test
	testl	%eax, %eax
	je	.L73
	movl	$0, %eax
	jmp	.L35
.L73:
	movl	$1, %eax
.L35:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	mr_prime, .-mr_prime
	.globl	ef_prime
	.type	ef_prime, @function
ef_prime:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	jne	.L75
	cmpq	$2, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L75:
	movq	-8(%rbp), %rcx
	movabsq	$-6148914691236517205, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	%rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L77
	cmpq	$3, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L77:
	movq	-8(%rbp), %rcx
	movabsq	$-3689348814741910323, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$2, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L78
	cmpq	$5, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L78:
	movq	-8(%rbp), %rcx
	movabsq	$2635249153387078803, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$2, %rax
	movq	%rax, %rdx
	salq	$3, %rdx
	subq	%rax, %rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	testq	%rax, %rax
	jne	.L79
	cmpq	$7, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L79:
	movq	-8(%rbp), %rcx
	movabsq	$3353953467947191203, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	%rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L80
	cmpq	$11, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L80:
	movq	-8(%rbp), %rcx
	movabsq	$5675921253449092805, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$2, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L81
	cmpq	$13, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L81:
	movq	-8(%rbp), %rcx
	movabsq	$-1085102592571150095, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rdx, %rax
	shrq	$4, %rax
	movq	%rax, %rdx
	salq	$4, %rdx
	addq	%rax, %rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	testq	%rax, %rax
	jne	.L82
	cmpq	$17, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L82:
	movq	-8(%rbp), %rcx
	movabsq	$-2912643801112034465, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$4, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L83
	cmpq	$19, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L83:
	movq	-8(%rbp), %rcx
	movabsq	$7218291159277650633, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$4, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L84
	cmpq	$23, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L84:
	movq	-8(%rbp), %rcx
	movabsq	$1908283869694091547, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$4, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L85
	cmpq	$29, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L85:
	movq	-8(%rbp), %rcx
	movabsq	$595056260442243601, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$4, %rax
	movq	%rax, %rdx
	salq	$5, %rdx
	subq	%rax, %rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	testq	%rax, %rax
	jne	.L86
	cmpq	$31, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L86:
	movq	-8(%rbp), %rcx
	movabsq	$-2492803253203993461, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$5, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L87
	cmpq	$37, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L87:
	movq	-8(%rbp), %rcx
	movabsq	$-4049285284472828403, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$5, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L88
	cmpq	$41, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L88:
	movq	-8(%rbp), %rcx
	movabsq	$-4718934530483838785, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$5, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L89
	cmpq	$43, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L89:
	movq	-8(%rbp), %rcx
	movabsq	$6672226579852391011, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$5, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L90
	cmpq	$47, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L90:
	movq	-8(%rbp), %rcx
	movabsq	$3828569524732171091, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$5, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L91
	cmpq	$53, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L91:
	movq	-8(%rbp), %rcx
	movabsq	$-8441730338816235485, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rdx, %rax
	shrq	$5, %rax
	imulq	$59, %rax, %rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	testq	%rax, %rax
	jne	.L92
	cmpq	$59, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L92:
	movq	-8(%rbp), %rcx
	movabsq	$907216921657846801, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$5, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L93
	cmpq	$61, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L93:
	movq	-8(%rbp), %rcx
	movabsq	$-825973615240726191, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$6, %rdx
	movq	%rdx, %rax
	salq	$5, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L94
	cmpq	$67, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L94:
	movq	-8(%rbp), %rcx
	movabsq	$-3637386155379348205, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$6, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L95
	cmpq	$71, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L95:
	movq	-8(%rbp), %rcx
	movabsq	$8086243977516515777, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$5, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L96
	cmpq	$73, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L96:
	movq	-8(%rbp), %rcx
	movabsq	$7472098865300071541, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$5, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L97
	cmpq	$79, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L97:
	movq	-8(%rbp), %rcx
	movabsq	$3555998857582564167, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	shrq	$4, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L98
	cmpq	$83, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L98:
	movq	-8(%rbp), %rcx
	movabsq	$8083404706456994529, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$6, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L99
	cmpq	$89, -8(%rbp)
	sete	%al
	movzbl	%al, %eax
	jmp	.L76
.L99:
	cmpq	$129999, -8(%rbp)
	ja	.L100
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	s5_prime_st97
	jmp	.L76
.L100:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	mr_prime
.L76:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	ef_prime, .-ef_prime
	.globl	mr_prime_test
	.type	mr_prime_test, @function
mr_prime_test:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	%ecx, -40(%rbp)
	movl	-40(%rbp), %eax
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	exp_mod@PLT
	movq	%rax, -8(%rbp)
	cmpq	$1, -8(%rbp)
	je	.L102
	movq	-24(%rbp), %rax
	subq	$1, %rax
	cmpq	%rax, -8(%rbp)
	jne	.L103
.L102:
	movl	$0, %eax
	jmp	.L104
.L103:
	movl	$1, -12(%rbp)
	jmp	.L105
.L108:
	movq	-8(%rbp), %rax
	imulq	%rax, %rax
	movl	$0, %edx
	divq	-24(%rbp)
	movq	%rdx, -8(%rbp)
	cmpq	$1, -8(%rbp)
	jne	.L106
	movl	$1, %eax
	jmp	.L104
.L106:
	movq	-24(%rbp), %rax
	subq	$1, %rax
	cmpq	%rax, -8(%rbp)
	jne	.L107
	movl	$0, %eax
	jmp	.L104
.L107:
	addl	$1, -12(%rbp)
.L105:
	movl	-12(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jb	.L108
	movl	$1, %eax
.L104:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	mr_prime_test, .-mr_prime_test
	.globl	__umodti3
	.globl	ext_mr_prime_test
	.type	ext_mr_prime_test, @function
ext_mr_prime_test:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movl	%edx, -84(%rbp)
	movl	%ecx, -88(%rbp)
	movl	-88(%rbp), %eax
	movq	-72(%rbp), %rdx
	movq	-80(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ext_mod@PLT
	movq	%rax, -56(%rbp)
	cmpq	$1, -56(%rbp)
	je	.L110
	movq	-72(%rbp), %rax
	subq	$1, %rax
	cmpq	%rax, -56(%rbp)
	jne	.L111
.L110:
	movl	$0, %eax
	jmp	.L112
.L111:
	movl	$1, -60(%rbp)
	jmp	.L113
.L116:
	movq	-56(%rbp), %rax
	movq	%rax, %r12
	movl	$0, %r13d
	movq	-56(%rbp), %rax
	movq	%rax, %r14
	movl	$0, %r15d
	movq	%r13, %rdx
	imulq	%r14, %rdx
	movq	%r15, %rax
	imulq	%r12, %rax
	leaq	(%rdx,%rax), %rcx
	movq	%r12, %rax
	mulq	%r14
	addq	%rdx, %rcx
	movq	%rcx, %rdx
	movq	-72(%rbp), %rcx
	movq	%rcx, -112(%rbp)
	movq	$0, -104(%rbp)
	movq	%rax, %rcx
	movq	%rdx, %rbx
	movq	%rcx, %rsi
	movq	%rdx, %rax
	movq	-112(%rbp), %rdx
	movq	-104(%rbp), %rcx
	movq	%rsi, %rdi
	movq	%rax, %rsi
	call	__umodti3@PLT
	movq	%rax, -56(%rbp)
	cmpq	$1, -56(%rbp)
	jne	.L114
	movl	$1, %eax
	jmp	.L112
.L114:
	movq	-72(%rbp), %rax
	subq	$1, %rax
	cmpq	%rax, -56(%rbp)
	jne	.L115
	movl	$0, %eax
	jmp	.L112
.L115:
	addl	$1, -60(%rbp)
.L113:
	movl	-60(%rbp), %eax
	cmpl	-84(%rbp), %eax
	jb	.L116
	movl	$1, %eax
.L112:
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	ext_mr_prime_test, .-ext_mr_prime_test
	.globl	er_sieve
	.type	er_sieve, @function
er_sieve:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movb	$0, (%rax)
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movb	$0, (%rax)
	movq	-32(%rbp), %rax
	leaq	-2(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	$2, %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movq	$2, -16(%rbp)
	jmp	.L118
.L123:
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L124
	movq	$2, -8(%rbp)
.L122:
	movq	-16(%rbp), %rax
	imulq	-8(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jnb	.L125
	movq	-16(%rbp), %rax
	imulq	-8(%rbp), %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	addq	$1, -8(%rbp)
	jmp	.L122
.L124:
	nop
	jmp	.L120
.L125:
	nop
.L120:
	addq	$1, -16(%rbp)
.L118:
	movq	-16(%rbp), %rax
	imulq	%rax, %rax
	cmpq	-32(%rbp), %rax
	jb	.L123
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	er_sieve, .-er_sieve
	.globl	pcf_approx
	.type	pcf_approx, @function
pcf_approx:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$1, -8(%rbp)
	ja	.L127
	movl	$0, %edx
	jmp	.L128
.L127:
	fildq	-8(%rbp)
	cmpq	$0, -8(%rbp)
	jns	.L129
	fldt	.LC0(%rip)
	faddp	%st, %st(1)
.L129:
	fldt	.LC3(%rip)
	fmulp	%st, %st(1)
	fstpt	-32(%rbp)
	fildq	-8(%rbp)
	cmpq	$0, -8(%rbp)
	jns	.L130
	fldt	.LC0(%rip)
	faddp	%st, %st(1)
.L130:
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	call	logl@PLT
	addq	$16, %rsp
	fldt	-32(%rbp)
	fdivp	%st, %st(1)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	call	ceill@PLT
	addq	$16, %rsp
	fldt	.LC1(%rip)
	fxch	%st(1)
	fcomi	%st(1), %st
	fstp	%st(1)
	jnb	.L131
	fnstcw	-10(%rbp)
	movzwl	-10(%rbp), %eax
	orb	$12, %ah
	movw	%ax, -12(%rbp)
	fldcw	-12(%rbp)
	fistpq	-32(%rbp)
	fldcw	-10(%rbp)
	movq	-32(%rbp), %rdx
	jmp	.L128
.L131:
	fldt	.LC1(%rip)
	fsubrp	%st, %st(1)
	fnstcw	-10(%rbp)
	movzwl	-10(%rbp), %eax
	orb	$12, %ah
	movw	%ax, -12(%rbp)
	fldcw	-12(%rbp)
	fistpq	-32(%rbp)
	fldcw	-10(%rbp)
	movq	-32(%rbp), %rdx
	movabsq	$-9223372036854775808, %rax
	xorq	%rax, %rdx
.L128:
	movq	%rdx, %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	pcf_approx, .-pcf_approx
	.globl	mobius_f
	.type	mobius_f, @function
mobius_f:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -12(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -8(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-20(%rbp), %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	floor@PLT
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L134
	movl	$-1, %eax
	jmp	.L135
.L134:
	movl	-20(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L136
	sarl	-20(%rbp)
	movl	-20(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L137
	movl	$0, %eax
	jmp	.L135
.L137:
	addl	$1, -12(%rbp)
.L136:
	movl	$3, -16(%rbp)
	jmp	.L138
.L142:
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L139
	movl	-20(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L139
	movl	-20(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L140
	movl	$0, %eax
	jmp	.L135
.L140:
	addl	$1, -12(%rbp)
.L139:
	addl	$2, -16(%rbp)
.L138:
	cmpl	$1, -20(%rbp)
	jle	.L143
	movl	-16(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jle	.L142
	jmp	.L143
.L146:
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L144
	movl	-20(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L144
	movl	-20(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%eax, -20(%rbp)
	addl	$1, -12(%rbp)
.L144:
	addl	$2, -16(%rbp)
.L143:
	cmpl	$1, -20(%rbp)
	jle	.L145
	movl	-16(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	.L146
.L145:
	movl	-12(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L147
	movl	$-1, %eax
	jmp	.L135
.L147:
	movl	$1, %eax
.L135:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	mobius_f, .-mobius_f
	.globl	mobius_setup
	.type	mobius_setup, @function
mobius_setup:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	%rdx, -40(%rbp)
	movl	%ecx, -32(%rbp)
	movq	-24(%rbp), %rax
	addq	$4, %rax
	movl	$1, (%rax)
	movl	$0, -4(%rbp)
	jmp	.L150
.L151:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$-1, (%rax)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-32(%rbp), %r8d
	movq	-40(%rbp), %rdi
	movl	-4(%rbp), %ecx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	%r8d, %r9d
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	rec_mob_setup
	addl	$1, -4(%rbp)
.L150:
	movl	-4(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L151
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	mobius_setup, .-mobius_setup
	.globl	rec_mob_setup
	.type	rec_mob_setup, @function
rec_mob_setup:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movq	%r8, -48(%rbp)
	movl	%r9d, -40(%rbp)
	addl	$1, -36(%rbp)
	jmp	.L153
.L156:
	movl	-32(%rbp), %eax
	movslq	%eax, %rdx
	movl	-36(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-48(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cltq
	imulq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movl	-28(%rbp), %eax
	cltq
	cmpq	%rax, -8(%rbp)
	jge	.L157
	movl	-32(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	negl	%edx
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	movl	%eax, %r10d
	movl	-40(%rbp), %edi
	movq	-48(%rbp), %rcx
	movl	-36(%rbp), %edx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	%edi, %r9d
	movq	%rcx, %r8
	movl	%edx, %ecx
	movl	%r10d, %edx
	movq	%rax, %rdi
	call	rec_mob_setup
	addl	$1, -36(%rbp)
.L153:
	movl	-36(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jl	.L156
	jmp	.L152
.L157:
	nop
.L152:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	rec_mob_setup, .-rec_mob_setup
	.section	.rodata
	.align 16
.LC0:
	.long	0
	.long	-2147483648
	.long	16447
	.long	0
	.align 16
.LC1:
	.long	0
	.long	-2147483648
	.long	16446
	.long	0
	.align 16
.LC3:
	.long	1111881134
	.long	-1599746469
	.long	16383
	.long	0
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits
