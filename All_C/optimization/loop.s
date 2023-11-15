	.file	"loop.c"
	.text
	.globl	new_vec
	.type	new_vec, @function
new_vec:
.LFB23:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rbp
	movl	$16, %edi
	call	malloc@PLT
	movq	%rax, %rbx
	testq	%rax, %rax
	je	.L1
	movq	%rbp, (%rax)
	testq	%rbp, %rbp
	jg	.L6
	movl	$0, %ebp
.L3:
	movq	%rbp, 8(%rbx)
.L1:
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	movl	$8, %esi
	movq	%rbp, %rdi
	call	calloc@PLT
	movq	%rax, %rbp
	testq	%rax, %rax
	jne	.L3
	movq	%rbx, %rdi
	call	free@PLT
	movq	%rbp, %rbx
	jmp	.L1
	.cfi_endproc
.LFE23:
	.size	new_vec, .-new_vec
	.globl	get_vec_element
	.type	get_vec_element, @function
get_vec_element:
.LFB24:
	.cfi_startproc
	endbr64
	testq	%rsi, %rsi
	js	.L9
	cmpq	%rsi, (%rdi)
	jle	.L10
	movq	8(%rdi), %rax
	movq	(%rax,%rsi,8), %rax
	movq	%rax, (%rdx)
	movl	$1, %eax
	ret
.L9:
	movl	$0, %eax
	ret
.L10:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE24:
	.size	get_vec_element, .-get_vec_element
	.globl	vec_length
	.type	vec_length, @function
vec_length:
.LFB25:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rax
	ret
	.cfi_endproc
.LFE25:
	.size	vec_length, .-vec_length
	.globl	combine1
	.type	combine1, @function
combine1:
.LFB27:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, %r12
	movq	%rsi, %rbp
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	$1, (%rsi)
	movl	$0, %ebx
	jmp	.L13
.L14:
	movq	%rsp, %rdx
	movq	%rbx, %rsi
	movq	%r12, %rdi
	call	get_vec_element
	movq	0(%rbp), %rax
	imulq	(%rsp), %rax
	movq	%rax, 0(%rbp)
	addq	$1, %rbx
.L13:
	movq	%r12, %rdi
	call	vec_length
	cmpq	%rbx, %rax
	jg	.L14
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L17
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L17:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE27:
	.size	combine1, .-combine1
	.globl	combine2
	.type	combine2, @function
combine2:
.LFB28:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	movq	%rdi, %r13
	movq	%rsi, %rbp
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	vec_length
	movq	%rax, %r12
	movq	$1, 0(%rbp)
	movl	$0, %ebx
	jmp	.L19
.L20:
	movq	%rsp, %rdx
	movq	%rbx, %rsi
	movq	%r13, %rdi
	call	get_vec_element
	movq	0(%rbp), %rax
	imulq	(%rsp), %rax
	movq	%rax, 0(%rbp)
	addq	$1, %rbx
.L19:
	cmpq	%r12, %rbx
	jl	.L20
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L23
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L23:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE28:
	.size	combine2, .-combine2
	.globl	get_vec_start
	.type	get_vec_start, @function
get_vec_start:
.LFB26:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	ret
	.cfi_endproc
.LFE26:
	.size	get_vec_start, .-get_vec_start
	.globl	combine3
	.type	combine3, @function
combine3:
.LFB29:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	movq	%rsi, %rbx
	call	vec_length
	movq	%rax, %rbp
	movq	%r12, %rdi
	call	get_vec_start
	movl	$0, %edx
	jmp	.L26
.L27:
	movq	(%rax,%rdx,8), %rcx
	imulq	(%rbx), %rcx
	movq	%rcx, (%rbx)
	addq	$1, %rdx
.L26:
	cmpq	%rbp, %rdx
	jl	.L27
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE29:
	.size	combine3, .-combine3
	.globl	combine4
	.type	combine4, @function
combine4:
.LFB30:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	movq	%rsi, %rbp
	call	vec_length
	movq	%rax, %rbx
	movq	%r12, %rdi
	call	get_vec_start
	movl	$1, %ecx
	movl	$0, %edx
	jmp	.L30
.L31:
	imulq	(%rax,%rdx,8), %rcx
	addq	$1, %rdx
.L30:
	cmpq	%rbx, %rdx
	jl	.L31
	movq	%rcx, 0(%rbp)
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE30:
	.size	combine4, .-combine4
	.globl	combine5
	.type	combine5, @function
combine5:
.LFB31:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	movq	%rsi, %rbp
	call	vec_length
	movq	%rax, %rbx
	movq	%r12, %rdi
	call	get_vec_start
	movl	$1, %ecx
	movl	$0, %edx
	jmp	.L34
.L35:
	imulq	(%rax,%rdx,8), %rcx
	imulq	8(%rax,%rdx,8), %rcx
	addq	$2, %rdx
.L34:
	leaq	-1(%rbx), %rsi
	cmpq	%rdx, %rsi
	jg	.L35
.L36:
	cmpq	%rbx, %rdx
	jl	.L37
	movq	%rcx, 0(%rbp)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L37:
	.cfi_restore_state
	imulq	(%rax,%rdx,8), %rcx
	addq	$1, %rdx
	jmp	.L36
	.cfi_endproc
.LFE31:
	.size	combine5, .-combine5
	.globl	combine6
	.type	combine6, @function
combine6:
.LFB32:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	movq	%rsi, %rbx
	call	vec_length
	movq	%rax, %rbp
	movq	%r12, %rdi
	call	get_vec_start
	movl	$1, %esi
	movl	$1, %ecx
	movl	$0, %edx
	jmp	.L40
.L41:
	imulq	(%rax,%rdx,8), %rcx
	imulq	8(%rax,%rdx,8), %rsi
	addq	$2, %rdx
.L40:
	leaq	-1(%rbp), %rdi
	cmpq	%rdx, %rdi
	jg	.L41
.L42:
	cmpq	%rbp, %rdx
	jl	.L43
	imulq	%rsi, %rcx
	movq	%rcx, (%rbx)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L43:
	.cfi_restore_state
	imulq	(%rax,%rdx,8), %rcx
	addq	$1, %rdx
	jmp	.L42
	.cfi_endproc
.LFE32:
	.size	combine6, .-combine6
	.globl	combine7
	.type	combine7, @function
combine7:
.LFB33:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	movq	%rsi, %rbp
	call	vec_length
	movq	%rax, %rbx
	movq	%r12, %rdi
	call	get_vec_start
	movl	$1, %esi
	movl	$0, %edx
	jmp	.L46
.L47:
	movq	8(%rax,%rdx,8), %rcx
	imulq	(%rax,%rdx,8), %rcx
	imulq	%rcx, %rsi
	addq	$2, %rdx
.L46:
	leaq	-1(%rbx), %rcx
	cmpq	%rdx, %rcx
	jg	.L47
.L48:
	cmpq	%rbx, %rdx
	jl	.L49
	movq	%rsi, 0(%rbp)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L49:
	.cfi_restore_state
	imulq	(%rax,%rdx,8), %rsi
	addq	$1, %rdx
	jmp	.L48
	.cfi_endproc
.LFE33:
	.size	combine7, .-combine7
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"time%c = %08ld us\n"
	.text
	.globl	clock
	.type	clock, @function
clock:
.LFB34:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%rdi, %rbp
	movq	%rsi, %r12
	movq	%rdx, %r13
	movl	%ecx, %ebx
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	movl	$0, %esi
	call	gettimeofday@PLT
	movq	%r13, %rsi
	movq	%r12, %rdi
	movl	$0, %eax
	call	*%rbp
	leaq	16(%rsp), %rdi
	movl	$0, %esi
	call	gettimeofday@PLT
	movq	16(%rsp), %rcx
	subq	(%rsp), %rcx
	imulq	$1000000, %rcx, %rcx
	addq	24(%rsp), %rcx
	subq	8(%rsp), %rcx
	movsbl	%bl, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L54
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L54:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE34:
	.size	clock, .-clock
	.globl	main
	.type	main, @function
main:
.LFB35:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movl	$1000000, %edi
	call	new_vec
	movq	%rax, %rbx
	movq	$0, (%rsp)
	movl	$0, %eax
	jmp	.L56
.L57:
	movslq	%eax, %rcx
	leaq	0(,%rcx,8), %rdx
	addq	8(%rbx), %rdx
	movq	%rcx, (%rdx)
	addl	$1, %eax
.L56:
	cmpl	$999999, %eax
	jle	.L57
	movq	%rsp, %rbp
	movl	$49, %ecx
	movq	%rbp, %rdx
	movq	%rbx, %rsi
	leaq	combine1(%rip), %rdi
	call	clock
	movl	$50, %ecx
	movq	%rbp, %rdx
	movq	%rbx, %rsi
	leaq	combine2(%rip), %rdi
	call	clock
	movl	$51, %ecx
	movq	%rbp, %rdx
	movq	%rbx, %rsi
	leaq	combine3(%rip), %rdi
	call	clock
	movl	$52, %ecx
	movq	%rbp, %rdx
	movq	%rbx, %rsi
	leaq	combine4(%rip), %rdi
	call	clock
	movl	$53, %ecx
	movq	%rbp, %rdx
	movq	%rbx, %rsi
	leaq	combine5(%rip), %rdi
	call	clock
	movl	$54, %ecx
	movq	%rbp, %rdx
	movq	%rbx, %rsi
	leaq	combine6(%rip), %rdi
	call	clock
	movl	$55, %ecx
	movq	%rbp, %rdx
	movq	%rbx, %rsi
	leaq	combine7(%rip), %rdi
	call	clock
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L60
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L60:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE35:
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
