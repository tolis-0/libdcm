	.file	"prime_test.c"
	.text
	.section	.rodata
.LC0:
	.string	"r"
.LC1:
	.string	"isprime.txt"
.LC2:
	.string	"Failed to open isprime.txt"
.LC3:
	.string	"%lu%d"
	.align 8
.LC4:
	.string	"at input %lu: expected %d, got %d\n"
	.align 8
.LC5:
	.string	"mr_prime sequence test result: %d\\%d"
.LC6:
	.string	"  \033[32mPassed\033[39m"
.LC7:
	.string	"  \033[31mFailed\033[39m"
	.text
	.globl	mr_prime_sequence_test
	.type	mr_prime_sequence_test, @function
mr_prime_sequence_test:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L2
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L1
.L2:
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
.L8:
	leaq	-40(%rbp), %rcx
	leaq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L12
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	mr_prime@PLT
	movl	%eax, -28(%rbp)
	movl	-40(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	je	.L6
	movl	-40(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %ecx
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L7
.L6:
	addl	$1, -32(%rbp)
.L7:
	addl	$1, -36(%rbp)
	jmp	.L8
.L12:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-36(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jne	.L9
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L1
.L9:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	mr_prime_sequence_test, .-mr_prime_sequence_test
	.section	.rodata
	.align 8
.LC8:
	.string	"s3_prime sequence test result: %d\\%d"
	.text
	.globl	s3_prime_sequence_test
	.type	s3_prime_sequence_test, @function
s3_prime_sequence_test:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L14
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L13
.L14:
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
.L20:
	leaq	-40(%rbp), %rcx
	leaq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L24
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	s3_prime@PLT
	movl	%eax, -28(%rbp)
	movl	-40(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	je	.L18
	movl	-40(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %ecx
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L19
.L18:
	addl	$1, -32(%rbp)
.L19:
	addl	$1, -36(%rbp)
	jmp	.L20
.L24:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-36(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jne	.L21
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L13
.L21:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L13:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L23
	call	__stack_chk_fail@PLT
.L23:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	s3_prime_sequence_test, .-s3_prime_sequence_test
	.section	.rodata
	.align 8
.LC9:
	.string	"ef_prime sequence test result: %d\\%d"
	.text
	.globl	ef_prime_sequence_test
	.type	ef_prime_sequence_test, @function
ef_prime_sequence_test:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L26
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L25
.L26:
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
.L32:
	leaq	-40(%rbp), %rcx
	leaq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L36
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ef_prime@PLT
	movl	%eax, -28(%rbp)
	movl	-40(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	je	.L30
	movl	-40(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %ecx
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L31
.L30:
	addl	$1, -32(%rbp)
.L31:
	addl	$1, -36(%rbp)
	jmp	.L32
.L36:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-36(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jne	.L33
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L25
.L33:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L25:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L35
	call	__stack_chk_fail@PLT
.L35:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	ef_prime_sequence_test, .-ef_prime_sequence_test
	.section	.rodata
.LC10:
	.string	"%zu%d"
	.align 8
.LC11:
	.string	"at input %zu: expected %d, got %d\n"
	.align 8
.LC12:
	.string	"er_sieve sequence test result: %d\\%d"
	.text
	.globl	er_sieve_sequence_test
	.type	er_sieve_sequence_test, @function
er_sieve_sequence_test:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L38
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L37
.L38:
	movl	$0, -32(%rbp)
	movl	$0, -28(%rbp)
.L44:
	leaq	-34(%rbp), %rcx
	leaq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC10(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L48
	movq	-24(%rbp), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -33(%rbp)
	movzbl	-34(%rbp), %eax
	cmpb	%al, -33(%rbp)
	je	.L42
	movsbl	-33(%rbp), %ecx
	movzbl	-34(%rbp), %eax
	movsbl	%al, %edx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L43
.L42:
	addl	$1, -28(%rbp)
.L43:
	addl	$1, -32(%rbp)
	jmp	.L44
.L48:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-28(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jne	.L45
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L37
.L45:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L37:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L47
	call	__stack_chk_fail@PLT
.L47:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	er_sieve_sequence_test, .-er_sieve_sequence_test
	.section	.rodata
.LC13:
	.string	"primes.txt"
.LC14:
	.string	"Failed to open primes.txt"
.LC15:
	.string	"%lu"
.LC16:
	.string	"primes.txt is empty\n"
	.align 8
.LC17:
	.string	"mr_prime set test result: %d\\%d"
	.text
	.globl	mr_prime_set_test
	.type	mr_prime_set_test, @function
mr_prime_set_test:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L50
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L49
.L50:
	leaq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	jne	.L52
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$20, %edx
	movl	$1, %esi
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L49
.L52:
	movq	$0, -24(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -44(%rbp)
.L59:
	movq	-32(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jnb	.L53
	leaq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L64
.L53:
	movq	-32(%rbp), %rax
	cmpq	%rax, -24(%rbp)
	jne	.L55
	movl	$1, -40(%rbp)
	jmp	.L56
.L55:
	movl	$0, -40(%rbp)
.L56:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	mr_prime@PLT
	movl	%eax, -36(%rbp)
	movl	-40(%rbp), %eax
	cmpl	-36(%rbp), %eax
	je	.L57
	movl	-36(%rbp), %ecx
	movl	-40(%rbp), %edx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L58
.L57:
	addl	$1, -44(%rbp)
.L58:
	addl	$1, -48(%rbp)
	addq	$1, -24(%rbp)
	jmp	.L59
.L64:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-48(%rbp), %edx
	movl	-44(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-44(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jne	.L60
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L49
.L60:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L49:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L63
	call	__stack_chk_fail@PLT
.L63:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	mr_prime_set_test, .-mr_prime_set_test
	.section	.rodata
	.align 8
.LC18:
	.string	"s3_prime set test result: %d\\%d"
	.text
	.globl	s3_prime_set_test
	.type	s3_prime_set_test, @function
s3_prime_set_test:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L66
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L65
.L66:
	leaq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	jne	.L68
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$20, %edx
	movl	$1, %esi
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L65
.L68:
	movq	$0, -24(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -44(%rbp)
.L75:
	movq	-32(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jnb	.L69
	leaq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L80
.L69:
	movq	-32(%rbp), %rax
	cmpq	%rax, -24(%rbp)
	jne	.L71
	movl	$1, -40(%rbp)
	jmp	.L72
.L71:
	movl	$0, -40(%rbp)
.L72:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	s3_prime@PLT
	movl	%eax, -36(%rbp)
	movl	-40(%rbp), %eax
	cmpl	-36(%rbp), %eax
	je	.L73
	movl	-36(%rbp), %ecx
	movl	-40(%rbp), %edx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L74
.L73:
	addl	$1, -44(%rbp)
.L74:
	addl	$1, -48(%rbp)
	addq	$1, -24(%rbp)
	jmp	.L75
.L80:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-48(%rbp), %edx
	movl	-44(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC18(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-44(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jne	.L76
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L65
.L76:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L65:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L79
	call	__stack_chk_fail@PLT
.L79:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	s3_prime_set_test, .-s3_prime_set_test
	.section	.rodata
	.align 8
.LC19:
	.string	"ef_prime set test result: %d\\%d"
	.text
	.globl	ef_prime_set_test
	.type	ef_prime_set_test, @function
ef_prime_set_test:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L82
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L81
.L82:
	leaq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	jne	.L84
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$20, %edx
	movl	$1, %esi
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L81
.L84:
	movq	$0, -24(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -44(%rbp)
.L91:
	movq	-32(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jnb	.L85
	leaq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L96
.L85:
	movq	-32(%rbp), %rax
	cmpq	%rax, -24(%rbp)
	jne	.L87
	movl	$1, -40(%rbp)
	jmp	.L88
.L87:
	movl	$0, -40(%rbp)
.L88:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ef_prime@PLT
	movl	%eax, -36(%rbp)
	movl	-40(%rbp), %eax
	cmpl	-36(%rbp), %eax
	je	.L89
	movl	-36(%rbp), %ecx
	movl	-40(%rbp), %edx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L90
.L89:
	addl	$1, -44(%rbp)
.L90:
	addl	$1, -48(%rbp)
	addq	$1, -24(%rbp)
	jmp	.L91
.L96:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-48(%rbp), %edx
	movl	-44(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC19(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-44(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jne	.L92
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L81
.L92:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L81:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L95
	call	__stack_chk_fail@PLT
.L95:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	ef_prime_set_test, .-ef_prime_set_test
	.section	.rodata
.LC20:
	.string	"primes26.txt"
.LC21:
	.string	"Failed to open primes26.txt"
.LC22:
	.string	"primes26.txt is empty\n"
	.align 8
.LC23:
	.string	"mr_prime set26 test result: %d\\%d"
	.text
	.globl	mr_prime_set26_test
	.type	mr_prime_set26_test, @function
mr_prime_set26_test:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC20(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L98
	leaq	.LC21(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L97
.L98:
	leaq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	jne	.L100
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$22, %edx
	movl	$1, %esi
	leaq	.LC22(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L97
.L100:
	movq	$472882048, -24(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -44(%rbp)
.L107:
	movq	-32(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jnb	.L101
	leaq	-32(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L112
.L101:
	movq	-32(%rbp), %rax
	cmpq	%rax, -24(%rbp)
	jne	.L103
	movl	$1, -40(%rbp)
	jmp	.L104
.L103:
	movl	$0, -40(%rbp)
.L104:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	mr_prime@PLT
	movl	%eax, -36(%rbp)
	movl	-40(%rbp), %eax
	cmpl	-36(%rbp), %eax
	je	.L105
	movl	-36(%rbp), %ecx
	movl	-40(%rbp), %edx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L106
.L105:
	addl	$1, -44(%rbp)
.L106:
	addl	$1, -48(%rbp)
	addq	$1, -24(%rbp)
	jmp	.L107
.L112:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-48(%rbp), %edx
	movl	-44(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC23(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-44(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jne	.L108
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L97
.L108:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L97:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L111
	call	__stack_chk_fail@PLT
.L111:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	mr_prime_set26_test, .-mr_prime_set26_test
	.section	.rodata
.LC24:
	.string	"a074773.txt"
.LC25:
	.string	"Failed to open a074773.txt"
	.align 8
.LC26:
	.string	"at input %lu: expected 0, got %d\n"
	.align 8
.LC27:
	.string	"mr_prime strps test result: %d\\%d"
	.text
	.globl	mr_prime_strps_test
	.type	mr_prime_strps_test, @function
mr_prime_strps_test:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC24(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L114
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L113
.L114:
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
.L120:
	leaq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L124
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	mr_prime@PLT
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	je	.L118
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %edx
	movq	%rax, %rsi
	leaq	.LC26(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L119
.L118:
	addl	$1, -32(%rbp)
.L119:
	addl	$1, -36(%rbp)
	jmp	.L120
.L124:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-36(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC27(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jne	.L121
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L113
.L121:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L113:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L123
	call	__stack_chk_fail@PLT
.L123:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	mr_prime_strps_test, .-mr_prime_strps_test
	.section	.rodata
.LC28:
	.string	"b049002.txt"
.LC29:
	.string	"Failed to open b049002.txt"
	.align 8
.LC30:
	.string	"at input %lu: expected 1, got %d\n"
	.align 8
.LC31:
	.string	"mr_prime p2_2 test result: %d\\%d"
	.text
	.globl	mr_prime_p2_2_test
	.type	mr_prime_p2_2_test, @function
mr_prime_p2_2_test:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC28(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L126
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L125
.L126:
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
.L132:
	leaq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L136
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	mr_prime@PLT
	movl	%eax, -28(%rbp)
	cmpl	$1, -28(%rbp)
	je	.L130
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %edx
	movq	%rax, %rsi
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L131
.L130:
	addl	$1, -32(%rbp)
.L131:
	addl	$1, -36(%rbp)
	jmp	.L132
.L136:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-36(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC31(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jne	.L133
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L125
.L133:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L125:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L135
	call	__stack_chk_fail@PLT
.L135:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	mr_prime_p2_2_test, .-mr_prime_p2_2_test
	.section	.rodata
.LC32:
	.string	"b056130.txt"
.LC33:
	.string	"Failed to open b056130.txt"
	.align 8
.LC34:
	.string	"mr_prime palb24 test result: %d\\%d"
	.text
	.globl	mr_prime_palb24_test
	.type	mr_prime_palb24_test, @function
mr_prime_palb24_test:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC32(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L138
	leaq	.LC33(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L137
.L138:
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
.L144:
	leaq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L148
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	mr_prime@PLT
	movl	%eax, -28(%rbp)
	cmpl	$1, -28(%rbp)
	je	.L142
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %edx
	movq	%rax, %rsi
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L143
.L142:
	addl	$1, -32(%rbp)
.L143:
	addl	$1, -36(%rbp)
	jmp	.L144
.L148:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-36(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC34(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jne	.L145
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L137
.L145:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L137:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L147
	call	__stack_chk_fail@PLT
.L147:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	mr_prime_palb24_test, .-mr_prime_palb24_test
	.section	.rodata
.LC35:
	.string	"b272061.txt"
.LC36:
	.string	"Failed to open b272061.txt"
	.align 8
.LC37:
	.string	"mr_prime sigtp test result: %d\\%d"
	.text
	.globl	mr_prime_sigtp_test
	.type	mr_prime_sigtp_test, @function
mr_prime_sigtp_test:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC35(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L150
	leaq	.LC36(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L149
.L150:
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
.L156:
	leaq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$-1, %eax
	je	.L160
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	mr_prime@PLT
	movl	%eax, -28(%rbp)
	cmpl	$1, -28(%rbp)
	je	.L154
	movq	-24(%rbp), %rax
	movl	-28(%rbp), %edx
	movq	%rax, %rsi
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L155
.L154:
	addl	$1, -32(%rbp)
.L155:
	addl	$1, -36(%rbp)
	jmp	.L156
.L160:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-36(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC37(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jne	.L157
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L149
.L157:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L149:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L159
	call	__stack_chk_fail@PLT
.L159:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	mr_prime_sigtp_test, .-mr_prime_sigtp_test
	.globl	main
	.type	main, @function
main:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, %eax
	call	mr_prime_sequence_test
	movl	$0, %eax
	call	s3_prime_sequence_test
	movl	$0, %eax
	call	ef_prime_sequence_test
	movl	$100001, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$100001, %esi
	movq	%rax, %rdi
	call	er_sieve@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	er_sieve_sequence_test
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	$0, %eax
	call	mr_prime_set_test
	movl	$0, %eax
	call	s3_prime_set_test
	movl	$0, %eax
	call	ef_prime_set_test
	movl	$0, %eax
	call	mr_prime_strps_test
	movl	$0, %eax
	call	mr_prime_p2_2_test
	movl	$0, %eax
	call	mr_prime_palb24_test
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits
