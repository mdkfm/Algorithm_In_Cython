	.file	"branch.c"
	.text
	.p2align 4
	.globl	absdiff_se
	.type	absdiff_se, @function
absdiff_se:
.LFB0:
	.cfi_startproc
	endbr64
	cmpq	%rsi, %rdi
	jge	.L2
	movq	%rsi, %rax
	addq	$1, lt_cnt(%rip)
	subq	%rdi, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L2:
	movq	%rdi, %rax
	addq	$1, ge_cnt(%rip)
	subq	%rsi, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	absdiff_se, .-absdiff_se
	.p2align 4
	.globl	gotodiff_se
	.type	gotodiff_se, @function
gotodiff_se:
.LFB1:
	.cfi_startproc
	endbr64
	cmpq	%rsi, %rdi
	jge	.L8
	movq	%rsi, %rax
	addq	$1, lt_cnt(%rip)
	subq	%rdi, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	movq	%rdi, %rax
	addq	$1, ge_cnt(%rip)
	subq	%rsi, %rax
	ret
	.cfi_endproc
.LFE1:
	.size	gotodiff_se, .-gotodiff_se
	.p2align 4
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB2:
	.cfi_startproc
	endbr64
	movq	%rsi, %rdx
	movq	%rdi, %rax
	subq	%rdi, %rdx
	subq	%rsi, %rax
	cmpq	%rsi, %rdi
	cmovl	%rdx, %rax
	ret
	.cfi_endproc
.LFE2:
	.size	absdiff, .-absdiff
	.p2align 4
	.globl	cmovdiff
	.type	cmovdiff, @function
cmovdiff:
.LFB3:
	.cfi_startproc
	endbr64
	movq	%rdi, %rdx
	movq	%rsi, %rax
	subq	%rsi, %rdx
	subq	%rdi, %rax
	cmpq	%rsi, %rdi
	cmovge	%rdx, %rax
	ret
	.cfi_endproc
.LFE3:
	.size	cmovdiff, .-cmovdiff
	.globl	ge_cnt
	.bss
	.align 8
	.type	ge_cnt, @object
	.size	ge_cnt, 8
ge_cnt:
	.zero	8
	.globl	lt_cnt
	.align 8
	.type	lt_cnt, @object
	.size	lt_cnt, 8
lt_cnt:
	.zero	8
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
