	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min	10, 13
	.globl	_main
	.p2align	4, 0x90
	movl	__0(%rip), %eax
	movl	%eax, a(%rip)
	movl	__0(%rip), %eax
	movl	%eax, i(%rip)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__1(%rip), %eax
	movslq	__0(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__1(%rip), %eax
	movslq	__1(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__2(%rip), %eax
	movslq	__2(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__3(%rip), %eax
	movslq	__3(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__5(%rip), %eax
	movslq	__4(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__8(%rip), %eax
	movslq	__5(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__13(%rip), %eax
	movslq	__6(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__21(%rip), %eax
	movslq	__7(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__34(%rip), %eax
	movslq	__8(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	v@GOTPCREL(%rip), %rcx
	movl	__55(%rip), %eax
	movslq	__9(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movl	__x(%rip), %eax
	movl	%eax, c(%rip)
	movl	__65(%rip), %eax
	movl	%eax, d(%rip)
_sum:
	.cfi_startproc
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset	16
Lcfi1:
	.cfi_offset %rbp,	-16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register	%rbp
	movl	x(%rip), %eax
	movl	y(%rip), %ebx
	addl	%ebx, %eax
	movl	%eax, __temp_0__(%rip)
	movl	__temp_0__(%rip), %eax
	popq	%rbp
	retq
	.cfi_endproc

_main:
	.cfi_startproc
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset	16
Lcfi4:
	.cfi_offset %rbp,	-16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register	%rbp
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
	movl	%ecx, __temp_1__(%rip)
	movl	__temp_1__(%rip), %eax
	cmpl	$0, %eax
	je	__label_1__
	movl	i(%rip), %eax
	movl	__1(%rip), %ebx
	addl	%ebx, %eax
	movl	%eax, __temp_2__(%rip)
	movl	__temp_2__(%rip), %eax
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
	movl	__0(%rip), %eax
	movl	%eax, i(%rip)
__label_3__:
	movl	i(%rip), %ecx
	cmpl	__10(%rip), %ecx
	setl	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, __temp_3__(%rip)
	movl	__temp_3__(%rip), %eax
	cmpl	$0, %eax
	je	__label_4__
	leaq	L_.str4(%rip), %rdi
	movl	L_.str4(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str(%rip), %rdi
	movl	i(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str5(%rip), %rdi
	movl	L_.str5(%rip), %esi
	movb	$0, %al
	callq	_printf
	movq	v@GOTPCREL(%rip), %rcx
	movslq	i(%rip), %rdx
	movl	(%rcx,%rdx,4), %eax
	movl	%eax, __temp_4__(%rip)
	leaq	L_.str(%rip), %rdi
	movl	__temp_4__(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	L_.str2(%rip), %rdi
	movl	L_.str2(%rip), %esi
	movb	$0, %al
	callq	_printf
	movl	__1(%rip), %eax
	movl	%eax, y(%rip)
	movl	i(%rip), %eax
	movl	%eax, x(%rip)
	callq	_sum
	movl	%eax, __temp_5__(%rip)
__label_2__:
	movl	__temp_5__(%rip), %eax
	movl	%eax, i(%rip)
	jmp	__label_3__
__label_4__:
	movl	$0, %eax
	popq	%rbp
	retq
	.cfi_endproc

	.comm	a,4,2
	.comm	c,4,2
	.comm	d,4,2
	.comm	i,4,2
	.comm	v,40,4
	.comm	x,4,2
	.comm	__temp_2__,4,2
	.comm	y,4,2
	.comm	__temp_0__,4,2
	.comm	__temp_5__,4,2
	.comm	__temp_3__,4,2
	.comm	__temp_1__,4,2
	.comm	mat,40,4
	.comm	__temp_4__,4,2

	.section	__DATA,__data
	.globl	__0
	.p2align	2
__0:
	.long	0
	.globl	__1
	.p2align	2
__1:
	.long	1
	.globl	__2
	.p2align	2
__2:
	.long	2
	.globl	__3
	.p2align	2
__3:
	.long	3
	.globl	__4
	.p2align	2
__4:
	.long	4
	.globl	__5
	.p2align	2
__5:
	.long	5
	.globl	__6
	.p2align	2
__6:
	.long	6
	.globl	__7
	.p2align	2
__7:
	.long	7
	.globl	__8
	.p2align	2
__8:
	.long	8
	.globl	__9
	.p2align	2
__9:
	.long	9
	.globl	__x
	.p2align	2
__x:
	.long	'x'
	.globl	__10
	.p2align	2
__10:
	.long	10
	.globl	__21
	.p2align	2
__21:
	.long	21
	.globl	__13
	.p2align	2
__13:
	.long	13
	.globl	__34
	.p2align	2
__34:
	.long	34
	.globl	__55
	.p2align	2
__55:
	.long	55
	.globl	__65
	.p2align	2
__65:
	.long	65

	.section	__TEXT,__cstring,cstring_literals
L_.str:
	.asciz	"%d"
L_.str1:
	.asciz	"Voce digitou "
L_.str5:
	.asciz	"] = "
L_.str4:
	.asciz	"v["
L_.str2:
	.asciz	"\n"
L_.str3:
	.asciz	"Incrementado para "
L_.str0:
	.asciz	"Oi, o trabalho de compiladores funciona! Digite um numero:\n"
