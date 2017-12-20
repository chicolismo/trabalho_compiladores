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
	movq	_x@GOTPCREL(%rip), %rcx
	movl	$0, -4(%rbp)
	movl	$111111, 4(%rcx)        ## imm = 0x1B207
	movl	$222222, 8(%rcx)        ## imm = 0x3640E
	movl	$333333, 12(%rcx)       ## imm = 0x51615
	movslq	_z(%rip), %rdx
	movl	$444444, (%rcx,%rdx,4)  ## imm = 0x6C81C
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_z                      ## @z
.zerofill __DATA,__common,_z,4,2
	.comm	_x,16,4                 ## @x
	.comm	_y,2004,4               ## @y

.subsections_via_symbols
