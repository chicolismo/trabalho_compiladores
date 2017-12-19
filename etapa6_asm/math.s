	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3
LCPI0_0:
	.quad	4618441417868443648     ## double 6
LCPI0_1:
	.quad	4617315517961601024     ## double 5
LCPI0_2:
	.quad	4616189618054758400     ## double 4
	.section	__TEXT,__literal4,4byte_literals
	.p2align	2
LCPI0_3:
	.long	1084227584              ## float 5
LCPI0_4:
	.long	1082130432              ## float 4
LCPI0_5:
	.long	1077936128              ## float 3
	.section	__TEXT,__text,regular,pure_instructions
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
	movsd	LCPI0_0(%rip), %xmm0    ## xmm0 = mem[0],zero
	movsd	LCPI0_1(%rip), %xmm1    ## xmm1 = mem[0],zero
	movsd	LCPI0_2(%rip), %xmm2    ## xmm2 = mem[0],zero
	movss	LCPI0_3(%rip), %xmm3    ## xmm3 = mem[0],zero,zero,zero
	movss	LCPI0_4(%rip), %xmm4    ## xmm4 = mem[0],zero,zero,zero
	movss	LCPI0_5(%rip), %xmm5    ## xmm5 = mem[0],zero,zero,zero
	movl	$0, -4(%rbp)
	movl	$1, -8(%rbp)
	movl	$2, -12(%rbp)
	movl	$3, -16(%rbp)
	movq	$2, -24(%rbp)
	movq	$3, -32(%rbp)
	movq	$4, -40(%rbp)
	movss	%xmm5, -44(%rbp)
	movss	%xmm4, -48(%rbp)
	movss	%xmm3, -52(%rbp)
	movsd	%xmm2, -64(%rbp)
	movsd	%xmm1, -72(%rbp)
	movsd	%xmm0, -80(%rbp)
	movl	-12(%rbp), %ecx
	addl	-16(%rbp), %ecx
	movl	%ecx, -8(%rbp)
	movq	-32(%rbp), %rdx
	addq	-40(%rbp), %rdx
	movq	%rdx, -24(%rbp)
	movss	-48(%rbp), %xmm0        ## xmm0 = mem[0],zero,zero,zero
	addss	-52(%rbp), %xmm0
	movss	%xmm0, -44(%rbp)
	movsd	-72(%rbp), %xmm0        ## xmm0 = mem[0],zero
	addsd	-80(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
	movl	-12(%rbp), %ecx
	imull	-16(%rbp), %ecx
	movl	%ecx, -8(%rbp)
	movq	-32(%rbp), %rdx
	imulq	-40(%rbp), %rdx
	movq	%rdx, -24(%rbp)
	movss	-48(%rbp), %xmm0        ## xmm0 = mem[0],zero,zero,zero
	mulss	-52(%rbp), %xmm0
	movss	%xmm0, -44(%rbp)
	movsd	-72(%rbp), %xmm0        ## xmm0 = mem[0],zero
	mulsd	-80(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
	movl	-12(%rbp), %ecx
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	idivl	-16(%rbp)
	movl	%eax, -8(%rbp)
	movq	-32(%rbp), %rax
	cqto
	idivq	-40(%rbp)
	movq	%rax, -24(%rbp)
	movss	-48(%rbp), %xmm0        ## xmm0 = mem[0],zero,zero,zero
	divss	-52(%rbp), %xmm0
	movss	%xmm0, -44(%rbp)
	movsd	-72(%rbp), %xmm0        ## xmm0 = mem[0],zero
	divsd	-80(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
	movl	-12(%rbp), %ecx
	subl	-16(%rbp), %ecx
	movl	%ecx, -8(%rbp)
	movq	-32(%rbp), %rax
	subq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movss	-48(%rbp), %xmm0        ## xmm0 = mem[0],zero,zero,zero
	subss	-52(%rbp), %xmm0
	movss	%xmm0, -44(%rbp)
	movsd	-72(%rbp), %xmm0        ## xmm0 = mem[0],zero
	subsd	-80(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
	movl	-84(%rbp), %eax         ## 4-byte Reload
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
