	.file	"while.c"
	.text
	.globl	fact_do
	.type	fact_do, @function
fact_do:
.LFB0:
	.cfi_startproc
	endbr64
	movl	$1, %eax
.L2:
	imulq	%rdi, %rax
	subq	$1, %rdi
	cmpq	$1, %rdi
	jg	.L2
	ret
	.cfi_endproc
.LFE0:
	.size	fact_do, .-fact_do
	.globl	fact_do_doto
	.type	fact_do_doto, @function
fact_do_doto:
.LFB1:
	.cfi_startproc
	endbr64
	movl	$1, %eax
.L4:
	addq	%rdi, %rax
	subq	$1, %rdi
	cmpq	$1, %rdi
	jg	.L4
	ret
	.cfi_endproc
.LFE1:
	.size	fact_do_doto, .-fact_do_doto
	.globl	fact_while
	.type	fact_while, @function
fact_while:
.LFB2:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	jmp	.L6
.L7:
	imulq	%rdi, %rax
	subq	$1, %rdi
.L6:
	cmpq	$1, %rdi
	jg	.L7
	ret
	.cfi_endproc
.LFE2:
	.size	fact_while, .-fact_while
	.globl	fact_while_jm_goto
	.type	fact_while_jm_goto, @function
fact_while_jm_goto:
.LFB3:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	jmp	.L9
.L11:
	imulq	%rdi, %rax
	subq	$1, %rdi
.L9:
	cmpq	$1, %rdi
	jg	.L11
	ret
	.cfi_endproc
.LFE3:
	.size	fact_while_jm_goto, .-fact_while_jm_goto
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
