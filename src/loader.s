.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


.section .text
.extern kernelMain
.extern callConstructors
.global loader


loader:

    mov $0x03dA, %dx
    in %dx, %al
    mov $0x03C0, %dx
    mov $0x30, %al
    out %al, %dx
    inc %dx
	in %dx, %al
    and 0xF7, %al
    dec %dx
	out %al, %dx

    mov $kernel_stack, %esp
    call callConstructors
    push %eax
    push %ebx
    call kernelMain


_stop:
    cli
    hlt
    jmp _stop



.section .bss
.space 2*1024*1024; # 2 MiB
kernel_stack:

