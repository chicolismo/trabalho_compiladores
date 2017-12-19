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
	movl	$0, -4(%rbp)
	movl	_x(%rip), %eax
	popq	%rbp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.globl	_x                      ## @x
	.p2align	2
_x:
	.long	1                       ## 0x1

	.globl	_y                      ## @y
.zerofill __DATA,__common,_y,4,2

.subsections_via_symbols
