cpp_sources = $(wildcard kernel/*.cpp kernel/writer/*.cpp kernel/IO/*.cpp kernel/Drivers/*.cpp kernel/Drivers/Setup/*.cpp kernel/Drivers/keyboard/*.cpp kernel/Tests/*.cpp)
obj = ${cpp_sources:.cpp=.o}
asm_kernel_sources=$(wildcard kernel/Drivers/*.asm kernel/Drivers/Setup/*.asm kernel/Drivers/keyboard/*.asm kernel/Memory/DetMemory.asm kernel/Tests/*.asm)
asm_obj=$(asm_kernel_sources:.asm=.oa)
%.oa: %.asm
	@echo "assembling $<...\n"
	nasm $< -f elf64 -o $@
build/binaries.o: kernel/low_level/binaries.asm
	@echo "Assembling $<...\n"
	nasm kernel/low_level/binaries.asm -f elf64 -o build/binaries.o
%.o: %.cpp
	@echo "Compiling $<...\n"
	x86_64-elf-gcc -ffreestanding -c $< -o $@ -w -O0 -Wall
build/multiboot_header: boot/multiboot_header.asm
	@echo "Assembling $<...\n"
	nasm boot/multiboot_header.asm -f elf64 -o build/multiboot_header
build/boot: boot/boot.asm
	@echo "Assembling $<...\n"
	nasm boot/boot.asm -f elf64 -o build/boot
build/long_mode: boot/long_mode.asm
	@echo "Assembling $<...\n"
	nasm boot/long_mode.asm -f elf64 -o build/long_mode

build/kernel.bin: build/multiboot_header build/boot build/long_mode build/kernel.o $(obj) build/binaries.o $(asm_obj)
	@echo "Linking $<...\n"
	x86_64-elf-ld -n -o build/kernel.bin -T target/linker.ld build/multiboot_header build/boot build/long_mode $(obj) build/binaries.o $(asm_obj)

run: build/kernel.bin
	@echo "Copying $@ into isofiles/boot/kernel.bin...\n"
	cp build/kernel.bin isofiles/boot/kernel.bin 
	@echo "Creating the iso image...\n"
	grub-mkrescue --directory /usr/lib/grub/i386-pc -o hexaos-amd64.iso isofiles 
	@echo "Running the OS...\n"
	qemu-system-x86_64 -cdrom hexaos-amd64.iso -d cpu_reset -D qemu-logs -serial file:serial.log
