

#include <grub/machine/memory.h>


protstack:
	.long	GRUB_MEMORY_MACHINE_PROT_STACK

	.macro PROT_TO_REAL
	call	prot_to_real
	.endm

	.macro REAL_TO_PROT
	calll	real_to_prot
	.endm


	.p2align	5	
gdt:
	.word	0, 0
	.byte	0, 0, 0, 0


	.word	0xFFFF, 0
	.byte	0, 0x9A, 0xCF, 0


	.word	0xFFFF, 0
	.byte	0, 0x92, 0xCF, 0


	.word	0xFFFF, 0
	.byte	0, 0x9E, 0, 0


	.word	0xFFFF, 0
	.byte	0, 0x92, 0, 0


	.p2align 5

gdtdesc:
	.word	0x27			
	.long	gdt			
LOCAL(realidt):
	.word 0x400
	.long 0
protidt:
	.word 0
	.long 0



real_to_prot:
	.code16
	cli

	xorw	%ax, %ax
	movw	%ax, %ds
#ifdef GRUB_MACHINE_QEMU

	lgdtl	%cs:(gdtdesc - _start - GRUB_BOOT_MACHINE_SIZE + 0x10000)
#else
	lgdtl	gdtdesc
#endif

	movl	%cr0, %eax
	orl	$GRUB_MEMORY_CPU_CR0_PE_ON, %eax
	movl	%eax, %cr0

	ljmpl	$GRUB_MEMORY_MACHINE_PROT_MODE_CSEG, $protcseg

	.code32
protcseg:

	movw	$GRUB_MEMORY_MACHINE_PROT_MODE_DSEG, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	movl	(%esp), %eax
	movl	%eax, GRUB_MEMORY_MACHINE_REAL_STACK

	movl	protstack, %eax
	movl	%eax, %esp
	movl	%eax, %ebp

	movl	GRUB_MEMORY_MACHINE_REAL_STACK, %eax
	movl	%eax, (%esp)

	xorl	%eax, %eax

	sidt LOCAL(realidt)
	lidt protidt

	ret
#ifndef GRUB_MACHINE_QEMU

prot_to_real:

	lgdt	gdtdesc

	sidt    protidt
	lidt    LOCAL(realidt)

	movl	%esp, %eax
	movl	%eax, protstack

	movl	(%esp), %eax
	movl	%eax, GRUB_MEMORY_MACHINE_REAL_STACK

	movl	$GRUB_MEMORY_MACHINE_REAL_STACK, %eax
	movl	%eax, %esp
	movl	%eax, %ebp

	movw	$GRUB_MEMORY_MACHINE_PSEUDO_REAL_DSEG, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	ljmp	$GRUB_MEMORY_MACHINE_PSEUDO_REAL_CSEG, $tmpcseg

tmpcseg:
	.code16

	movl	%cr0, %eax
	andl 	$(~GRUB_MEMORY_CPU_CR0_PE_ON), %eax
	movl	%eax, %cr0

	ljmpl	$0, $realcseg

realcseg:

	xorl	%eax, %eax

	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

#ifdef GRUB_MACHINE_PCBIOS

	sti
#endif

	retl
#endif
	.code32