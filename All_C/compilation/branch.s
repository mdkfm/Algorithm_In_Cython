	.file	"branch.c"
	.text
	.globl	absdiff_se
	.type	absdiff_se, @function
absdiff_se:
.LFB0:
	.cfi_startproc
	endbr64
	cmpq	%rsi, %rdi
	jge	.L2
	addq	$1, lt_cnt(%rip)
	movq	%rsi, %rax
	subq	%rdi, %rax
	ret
.L2:
	addq	$1, ge_cnt(%rip)
	movq	%rdi, %rax
	subq	%rsi, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	absdiff_se, .-absdiff_se
	.globl	gotodiff_se
	.type	gotodiff_se, @function
gotodiff_se:
.LFB1:
	.cfi_startproc
	endbr64
	cmpq	%rsi, %rdi
	jge	.L7
	addq	$1, lt_cnt(%rip)
	movq	%rsi, %rax
	subq	%rdi, %rax
	ret
.L7:
	addq	$1, ge_cnt(%rip)
	movq	%rdi, %rax
	subq	%rsi, %rax
	ret
	.cfi_endproc
.LFE1:
	.size	gotodiff_se, .-gotodiff_se
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB2:
	.cfi_startproc
	endbr64
	cmpq	%rsi, %rdi
	jge	.L9
	movq	%rsi, %rax
	subq	%rdi, %rax
	ret
.L9:
	movq	%rdi, %rax
	subq	%rsi, %rax
	ret
	.cfi_endproc
.LFE2:
	.size	absdiff, .-absdiff
	.globl	cmovdiff
	.type	cmovdiff, @function
cmovdiff:
.LFB3:
	.cfi_startproc
	endbr64
	movq	%rdi, %rdx
	subq	%rsi, %rdx
	movq	%rsi, %rax
	subq	%rdi, %rax
	cmpq	%rsi, %rdi
	jl	.L11
	movq	%rdx, %rax
.L11:
	ret
	.cfi_endproc
.LFE3:
	.size	cmovdiff, .-cmovdiff
	.globl	switch_eg
	.type	switch_eg, @function
switch_eg:
.LFB4:
	.cfi_startproc
	endbr64
	subq	$100, %rsi
	cmpq	$6, %rsi
	ja	.L20
	leaq	.L16(%rip), %rcx
	movslq	(%rcx,%rsi,4), %rax
	addq	%rcx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L16:
	.long	.L19-.L16
	.long	.L20-.L16
	.long	.L18-.L16
	.long	.L17-.L16
	.long	.L15-.L16
	.long	.L20-.L16
	.long	.L15-.L16
	.text
.L19:
	leaq	(%rdi,%rdi,2), %rax
	leaq	(%rdi,%rax,4), %rdi
	jmp	.L14
.L18:
	addq	$10, %rdi
.L17:
	addq	$11, %rdi
.L15:
	imulq	%rdi, %rdi
.L14:
	movq	%rdi, (%rdx)
	ret
.L20:
	movl	$0, %edi
	jmp	.L14
	.cfi_endproc
.LFE4:
	.size	switch_eg, .-switch_eg
	.globl	switch_eg_impl
	.type	switch_eg_impl, @function
switch_eg_impl:
.LFB5:
	.cfi_startproc
	endbr64
	subq	$100, %rsi
	cmpq	$6, %rsi
	ja	.L22
	leaq	jt.0(%rip), %rax
	jmp	*(%rax,%rsi,8)
.L23:
	endbr64
	leaq	(%rdi,%rdi,2), %rax
	leaq	(%rdi,%rax,4), %rdi
	jmp	.L24
.L25:
	endbr64
	addq	$10, %rdi
.L26:
	endbr64
	addq	$11, %rdi
	jmp	.L24
.L27:
	endbr64
	imulq	%rdi, %rdi
	jmp	.L24
.L22:
	endbr64
	movl	$0, %edi
.L24:
	movq	%rdi, (%rdx)
	ret
	.cfi_endproc
.LFE5:
	.size	switch_eg_impl, .-switch_eg_impl
	.section	.data.rel.ro.local,"aw"
	.align 32
	.type	jt.0, @object
	.size	jt.0, 56
jt.0:
	.quad	.L23
	.quad	.L22
	.quad	.L25
	.quad	.L26
	.quad	.L27
	.quad	.L22
	.quad	.L27
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
