	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min	10, 13
	.globl	_main
	.p2align	4, 0x90
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

_sub:
	.cfi_startproc
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset	16
Lcfi4:
	.cfi_offset %rbp,	-16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register	%rbp
	movl	w(%rip), %eax
	movl	z(%rip), %ebx
	subl	%ebx, %eax
	movl	%eax, __temp_1__(%rip)
	movl	__temp_1__(%rip), %eax
	popq	%rbp
	retq
	.cfi_endproc

_main:
	.cfi_startproc
	pushq	%rbp
Lcfi6:
	.cfi_def_cfa_offset	16
Lcfi7:
	.cfi_offset %rbp,	-16
	movq	%rsp, %rbp
Lcfi8:
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
	movl	%ecx, __temp_2__(%rip)
	movl	__temp_2__(%rip), %eax
	cmpl	$0, %eax
	je	__label_1__
	movl	i(%rip), %eax
	movl	__1(%rip), %ebx
	addl	%ebx, %eax
	movl	%eax, __temp_3__(%rip)
	movl	__temp_3__(%rip), %eax
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
__label_2__:
	movl	i(%rip), %ecx
	cmpl	__9(%rip), %ecx
	setle	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, __temp_4__(%rip)
	movl	__temp_4__(%rip), %eax
	cmpl	$0, %eax
	je	__label_3__
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
	movl	%eax, __temp_5__(%rip)
	leaq	L_.str(%rip), %rdi
	movl	__temp_5__(%rip), %esi
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
	movl	%eax, __temp_6__(%rip)
	movl	__temp_6__(%rip), %eax
	movl	%eax, i(%rip)
	jmp	__label_2__
__label_3__:
	movl	__0(%rip), %eax
	movl	%eax, i(%rip)
	movl	__5(%rip), %eax
	movl	%eax, a(%rip)
__label_6__:
	movl	i(%rip), %ecx
	cmpl	__10(%rip), %ecx
	sete	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, __temp_7__(%rip)
	movl	__temp_7__(%rip), %ecx
	cmpl	$0, %ecx
	setne	%dl
	xorb	$-1, %dl
	andb	$1, %dl
	movzbl	%dl, %edx
	movl	%edx, __temp_7__(%rip)
	movl	a(%rip), %ecx
	cmpl	__0(%rip), %ecx
	setge	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, __temp_8__(%rip)
	movl	__temp_7__(%rip), %eax
	movl	__temp_8__(%rip), %ebx
	andl	%ebx, %eax
	movl	%eax, __temp_7__(%rip)
	movl	__temp_7__(%rip), %eax
	cmpl	$0, %eax
	je	__label_7__
	movl	i(%rip), %ecx
	cmpl	__0(%rip), %ecx
	setg	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, __temp_9__(%rip)
	movl	__temp_9__(%rip), %eax
	cmpl	$0, %eax
	je	__label_4__
	movl	i(%rip), %eax
	movl	__1(%rip), %ebx
	subl	%ebx, %eax
	movl	%eax, __temp_10__(%rip)
	movq	mat@GOTPCREL(%rip), %rcx
	movslq	__temp_10__(%rip), %rdx
	movl	(%rcx,%rdx,4), %eax
	movl	%eax, __temp_10__(%rip)
	movl	__temp_10__(%rip), %eax
	movl	%eax, y(%rip)
	movl	__1(%rip), %eax
	movl	%eax, x(%rip)
	callq	_sum
	movl	%eax, __temp_11__(%rip)
	movl	__temp_11__(%rip), %eax
	movl	%eax, y(%rip)
	movl	__10(%rip), %eax
	movl	%eax, x(%rip)
	callq	_sum
	movl	%eax, __temp_12__(%rip)
	movl	__temp_12__(%rip), %eax
	movl	%eax, y(%rip)
	movl	__100(%rip), %eax
	movl	%eax, x(%rip)
	callq	_sum
	movl	%eax, __temp_13__(%rip)
	movq	mat@GOTPCREL(%rip), %rcx
	movl	__temp_13__(%rip), %eax
	movslq	i(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
	jmp	__label_5__
__label_4__:
	movq	mat@GOTPCREL(%rip), %rcx
	movl	__0(%rip), %eax
	movslq	i(%rip), %rdx
	movl	%eax, (%rcx,%rdx,4)
__label_5__:
	leaq	L_.str6(%rip), %rdi
	movl	L_.str6(%rip), %esi
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
	movq	mat@GOTPCREL(%rip), %rcx
	movslq	i(%rip), %rdx
	movl	(%rcx,%rdx,4), %eax
	movl	%eax, __temp_14__(%rip)
	leaq	L_.str(%rip), %rdi
	movl	__temp_14__(%rip), %esi
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
	movl	%eax, __temp_15__(%rip)
	movl	__temp_15__(%rip), %eax
	movl	%eax, i(%rip)
	movl	__1(%rip), %eax
	movl	%eax, z(%rip)
	movl	a(%rip), %eax
	movl	%eax, w(%rip)
	callq	_sub
	movl	%eax, __temp_16__(%rip)
	movl	__temp_16__(%rip), %eax
	movl	%eax, a(%rip)
	jmp	__label_6__
__label_7__:
	movl	$0, %eax
	popq	%rbp
	retq
	.cfi_endproc

	.comm	w,2,2
	.comm	x,2,2
	.comm	__temp_2__,2,2
	.comm	__temp_7__,2,2
	.comm	__temp_10__,2,2
	.comm	y,2,2
	.comm	z,2,2
	.comm	__temp_15__,2,2
	.comm	__temp_0__,2,2
	.comm	__temp_5__,2,2
	.comm	__temp_12__,2,2
	.comm	__temp_3__,2,2
	.comm	__temp_8__,2,2
	.comm	__temp_14__,2,2
	.comm	__temp_1__,2,2
	.comm	__temp_6__,2,2
	.comm	__temp_11__,2,2
	.comm	mat,40,4
	.comm	__temp_16__,2,2
	.comm	__temp_4__,2,2
	.comm	__temp_9__,2,2
	.comm	__temp_13__,2,2

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
	.globl	__5
	.p2align	2
__5:
	.long	5
	.globl	__8
	.p2align	2
__8:
	.long	8
	.globl	__9
	.p2align	2
__9:
	.long	9
	.globl	a
	.p2align	2
a:
	.long	0
	.globl	c
	.p2align	2
c:
	.long	'x'
	.globl	d
	.p2align	2
d:
	.long	65
	.globl	i
	.p2align	2
i:
	.long	0
	.globl	v
	.p2align	4
v:
	.long	1
	.long	1
	.long	2
	.long	3
	.long	5
	.long	8
	.long	13
	.long	21
	.long	34
	.long	55
	.globl	__x
	.p2align	2
__x:
	.long	'x'
	.globl	__100
	.p2align	2
__100:
	.long	100
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
L_.str6:
	.asciz	"mat["
L_.str2:
	.asciz	"\n"
L_.str3:
	.asciz	"Incrementado para "
L_.str0:
	.asciz	"Oi, o trabalho de compiladores funciona! Digite um numero:\n"
