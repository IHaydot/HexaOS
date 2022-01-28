build/multiboot_header: boot/multiboot_header.asm
	nasm boot/multiboot_header.asm -f elf64 -o build/multiboot_header
build/boot: boot/boot.asm
	nasm boot/boot.asm -f elf64 -o build/boot
build/kernel.bin: build/multiboot_header build/boot
	x86_64-elf-ld -n -o build/kernel.bin -T target/linker.ld build/multiboot_header build/boot

run: build/kernel.bin
	cp build/kernel.bin isofiles/boot/kernel.bin 
	grub-mkrescue --directory /usr/lib/grub/i386-pc -o hexaos-amd64.iso isofiles 
	qemu-system-x86_64 -cdrom hexaos-amd64.iso
