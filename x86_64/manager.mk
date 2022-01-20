
build/boot1.bin: boot/stage1/boot1.s boot/stage2/boot2.s
	nasm boot/stage1/boot1.s -f bin -o build/boot1.bin
	nasm boot/stage2/boot2.s -f bin -o build/boot2.bin

os-image: build/boot1.bin
	cat build/boot1.bin build/boot2.bin > os-image

run: os-image
	qemu-system-x86_64 -drive format=raw,file=os-image -d cpu_reset -D qemu-logs