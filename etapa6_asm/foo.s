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
	subq	$32, %rsp
	leaq	L_.str(%rip), %rdi
	leaq	-8(%rbp), %rsi
	movl	$0, -4(%rbp)
	movl	$1111111, -8(%rbp)      ## imm = 0x10F447
	movb	$0, %al
	callq	_scanf
	leaq	L_.str(%rip), %rdi
	movl	$2222222, -12(%rbp)     ## imm = 0x21E88E
	movl	-8(%rbp), %esi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	movl	$3333333, -16(%rbp)     ## imm = 0x32DCD5
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$5555555, %esi          ## imm = 0x54C563
	movl	$4444444, -20(%rbp)     ## imm = 0x43D11C
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	movl	%esi, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d"

L_.str.1:                               ## @.str.1
	.asciz	"OI EU SOU O GOKU"


.subsections_via_symbols
