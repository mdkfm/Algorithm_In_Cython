	.file	"write_read.c"
	.text
	.globl	cumsum1
	.type	cumsum1, @function
cumsum1:
.LFB39:
	.cfi_startproc
	endbr64
	movsd	(%rdi), %xmm0
	movsd	%xmm0, (%rdx)
	movl	$1, %eax
	jmp	.L2
.L3:
	movslq	%eax, %rcx
	movsd	(%rdi,%rcx,8), %xmm0
	mulsd	-8(%rdx,%rcx,8), %xmm0
	movsd	%xmm0, (%rdx,%rcx,8)
	addl	$1, %eax
.L2:
	cmpl	%esi, %eax
	jl	.L3
	ret
	.cfi_endproc
.LFE39:
	.size	cumsum1, .-cumsum1
	.globl	cumsum2
	.type	cumsum2, @function
cumsum2:
.LFB40:
	.cfi_startproc
	endbr64
	movsd	(%rdi), %xmm0
	movsd	%xmm0, (%rdx)
	movl	$1, %eax
	jmp	.L5
.L6:
	movslq	%eax, %rcx
	mulsd	(%rdi,%rcx,8), %xmm0
	movsd	%xmm0, (%rdx,%rcx,8)
	addl	$1, %eax
.L5:
	cmpl	%esi, %eax
	jl	.L6
	ret
	.cfi_endproc
.LFE40:
	.size	cumsum2, .-cumsum2
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"time = %08ld us\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	leaq	-1597440(%rsp), %r11
	.cfi_def_cfa 11, 1597488
.LPSRL0:
	subq	$4096, %rsp
	orq	$0, (%rsp)
	cmpq	%r11, %rsp
	jne	.LPSRL0
	.cfi_def_cfa_register 7
	subq	$2608, %rsp
	.cfi_def_cfa_offset 1600096
	movq	%fs:40, %rax
	movq	%rax, 1600040(%rsp)
	xorl	%eax, %eax
	movl	$10, %edi
	call	srand@PLT
	movl	$0, %ebx
	jmp	.L8
.L9:
	call	rand@PLT
	movl	%eax, %edx
	movslq	%ebx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%edx, %xmm0
	movsd	%xmm0, 32(%rsp,%rax,8)
	addl	$1, %ebx
.L8:
	cmpl	$99999, %ebx
	jle	.L9
	movq	%rsp, %r14
	movl	$0, %esi
	movq	%r14, %rdi
	call	gettimeofday@PLT
	leaq	800032(%rsp), %r13
	leaq	32(%rsp), %r12
	movq	%r13, %rdx
	movl	$100000, %esi
	movq	%r12, %rdi
	call	cumsum1
	leaq	16(%rsp), %rbp
	movl	$0, %esi
	movq	%rbp, %rdi
	call	gettimeofday@PLT
	movq	16(%rsp), %rdx
	subq	(%rsp), %rdx
	imulq	$1000000, %rdx, %rdx
	addq	24(%rsp), %rdx
	subq	8(%rsp), %rdx
	leaq	.LC0(%rip), %rbx
	movq	%rbx, %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %esi
	movq	%r14, %rdi
	call	gettimeofday@PLT
	movq	%r13, %rdx
	movl	$100000, %esi
	movq	%r12, %rdi
	call	cumsum2
	movl	$0, %esi
	movq	%rbp, %rdi
	call	gettimeofday@PLT
	movq	16(%rsp), %rdx
	subq	(%rsp), %rdx
	imulq	$1000000, %rdx, %rdx
	addq	24(%rsp), %rdx
	subq	8(%rsp), %rdx
	movq	%rbx, %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	1600040(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L12
	addq	$1600048, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L12:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
