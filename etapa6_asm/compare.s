	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	xorl	%eax, %eax
	movl	$0, -4(%rbp)
	movl	$1, -8(%rbp)
	movl	$2, -12(%rbp)
	movl	$3, -16(%rbp)
	movl	-8(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	setl	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, -16(%rbp)
	movl	-8(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	setg	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, -16(%rbp)
	movl	-8(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	setle	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, -16(%rbp)
	movl	-8(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	setge	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, -16(%rbp)
	movl	-8(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	sete	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, -16(%rbp)
	movl	-8(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	setne	%dl
	andb	$1, %dl
	movzbl	%dl, %ecx
	movl	%ecx, -16(%rbp)
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
