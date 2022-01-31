Installation guide:
  1. clone the project into a desired directory through the following command:
    ```git clone https://github.com/IHaydot/HexaOS.git```
  2. Take the image file that suits your needs (for a 64 bit image, take the *hexaos-amd64.iso* image.)
  3. IMPORTANT! Due to this OS being a test operating system that is not meant to be functional nor working, it's always important to run the image on an emulator (I recommend QEMU) or on a virtual machine to make sure it is working. (if you want to emulate the OS on QEMU, you will need to download QEMU and run the following command:
    ```qemu-system-x86_64 -cdrom hexaos-amd64.iso -d cpu_reset -D qemu-logs```
  4. If you would like to write your own code for the OS, you will need alot of things to get you setup. I will most likely add a docker file to the project to allow easier and faster access to these tools, but as of right now you will need to download the following:
    a. A gcc cross compiler (you can use a normal compiler if you just want to test things, but considering the makefile currently uses the cross compiler and linker you will need to change the makefile to get it to work with a normal compiler)
    b. same for the linker
    c. grub 
    d. on a Linux distro, have the following directory: ```/usr/lib/grub/i386-pc```
    e. nasm
    f. make
    g. QEMU
    When you have all these tools, open the directory in which the makefile is in and type ```make run -B``` to compile, assemble and link all files. QEMU should run and give output.
    Whats next is up to you!
    
   
