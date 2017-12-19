	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min	10, 13
	.globl	_main
	.p2align	4, 0x90
_main:
	.cfi_startproc
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset	16
Lcfi1:
	.cfi_offset %rbp,	-16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register	%rbp
	movl	__0(%rip), %eax
	movl	%eax, a(%rip)
	movl	__0(%rip), %eax
	movl	%eax, i(%rip)
	leaq	L_.str0(%rip), %rdi
	movl	L_.str0(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str(%rip), %rdi
	leaq	i(%rip), %rsi
	movb	$0, %al
	callq	_scanf
	movl	i(%rip), %eax
	movl	%eax, a(%rip)
	leaq	L_.str1(%rip), %rdi
	movl	L_.str1(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str(%rip), %rdi
	movl	a(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str2(%rip), %rdi
	movl	L_.str2(%rip), %esi
	movb	$0, %al
	callq	_printf
__label_0__:
	movl	i(%rip), %ecx
	cmpl	__10(%rip), %ecx
	setl	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, __temp_0__(%rip)
	movl	__temp_0__(%rip), %eax
	cmpl	$0, %eax
	je	__label_1__
	movl	i(%rip), %eax
	movl	__1(%rip), %ebx
	addl	%ebx, %eax
	movl	%eax, __temp_1__(%rip)
	movl	__temp_1__(%rip), %eax
	movl	%eax, i(%rip)
	leaq	L_.str3(%rip), %rdi
	movl	L_.str3(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str(%rip), %rdi
	movl	i(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str2(%rip), %rdi
	movl	L_.str2(%rip), %esi
	movb	$0, %al
	callq	_printf
	jmp	__label_0__
__label_1__:
	movl	i(%rip), %eax
	popq	%rbp
	retq
	.cfi_endproc

	.comm	a,4,2
	.comm	i,4,2
	.comm	__temp_0__,4,2
	.comm	__temp_1__,4,2

	.section	__DATA,__data
	.globl	__0
	.p2align	2
__0:
	.long	0
	.globl	__1
	.p2align	2
__1:
	.long	1
	.globl	__10
	.p2align	2
__10:
	.long	10

	.section	__TEXT,__cstring,cstring_literals
L_.str:
	.asciz	"%d"
L_.str1:
	.asciz	"Voce digitou "
L_.str2:
	.asciz	"\n"
L_.str3:
	.asciz	"Incrementado para "
L_.str0:
	.asciz	"Oi, o trabalho de compiladores funciona! Digite um numero:\n"
