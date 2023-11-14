	.file	"calculate.c"
	.text
	.globl	scale
	.type	scale, @function
scale:
.LFB0:
	.cfi_startproc
	endbr64
	leaq	(%rdi,%rsi,4), %rax
	leaq	(%rdx,%rdx,2), %rdx
	leaq	(%rax,%rdx,4), %rax
	ret
	.cfi_endproc
.LFE0:
	.size	scale, .-scale
	.globl	arith
	.type	arith, @function
arith:
.LFB1:
	.cfi_startproc
	endbr64
	xorq	%rsi, %rdi
	leaq	(%rdx,%rdx,2), %rax
	salq	$4, %rax
	andl	$252645135, %edi
	subq	%rdi, %rax
	ret
	.cfi_endproc
.LFE1:
	.size	arith, .-arith
	.globl	float_cal
	.type	float_cal, @function
float_cal:
.LFB2:
	.cfi_startproc
	endbr64
	mulsd	%xmm1, %xmm0
	divsd	%xmm2, %xmm0
	ret
	.cfi_endproc
.LFE2:
	.size	float_cal, .-float_cal
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
