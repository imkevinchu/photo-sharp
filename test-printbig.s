	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:                               ## %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$72, %edi
	callq	_printbig
	movl	$69, %edi
	callq	_printbig
	movl	$76, %edi
	callq	_printbig
	movl	$76, %edi
	callq	_printbig
	movl	$79, %edi
	callq	_printbig
	movl	$32, %edi
	callq	_printbig
	movl	$87, %edi
	callq	_printbig
	movl	$79, %edi
	callq	_printbig
	movl	$82, %edi
	callq	_printbig
	movl	$76, %edi
	callq	_printbig
	movl	$68, %edi
	callq	_printbig
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_fmt:                                  ## @fmt
	.asciz	"%d\n"

L_fmt.1:                                ## @fmt.1
	.asciz	"%s\n"

L_fmt.2:                                ## @fmt.2
	.asciz	"%g\n"


.subsections_via_symbols
