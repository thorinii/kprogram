#! /bin/bash

gcc_options="-c -std=c99 -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -g -Iinclude/"
as_options="-gstabs"
output_bin="kprogram.bin"

# Fail Function
function fail() { echo "$1"; exit 1; }
function echoln() { echo ; echo "------------------------------------------------"; echo "$1"; echo ;}

echo "KProgram Compile Script v0.1"

echoln "Deleting old files...";
# clean
rm -r objectfiles
rm kprogram.bin

mkdir objectfiles

echoln "Assembling the loader..."
as --32 -o ./objectfiles/loader.o ./boot/loader.s $as_options || fail "Loader invalid"

as --32 -o ./objectfiles/gdt-asm.o ./boot/gdt-asm.s $as_options || fail "GDT ASM invalid"
as --32 -o ./objectfiles/idt-asm.o ./boot/idt-asm.s $as_options || fail "IDT ASM invalid"
as --32 -o ./objectfiles/syscall-asm.o ./boot/syscall-asm.s $as_options || fail "Syscall ASM invalid"

echoln "Compiling the Startup, Screen and Main..."
gcc -m32 -o ./objectfiles/startup.o ./boot/startup.c $gcc_options || fail "Startup invalid"
gcc -m32 -o ./objectfiles/screen.o ./libs/screen.c $gcc_options || fail "Screen invalid"
gcc -m32 -o ./objectfiles/system.o ./libs/system.c $gcc_options || fail "System invalid"

gcc -m32 -o ./objectfiles/gdt.o ./libs/gdt.c $gcc_options || fail "GDT C invalid"
gcc -m32 -o ./objectfiles/idt.o ./libs/idt.c $gcc_options || fail "IDT C invalid"
gcc -m32 -o ./objectfiles/keyboard.o ./libs/keyboard.c $gcc_options || fail "Keyboard C invalid"
gcc -m32 -o ./objectfiles/pit.o ./libs/pit.c $gcc_options || fail "PIT C invalid"

gcc -m32 -o ./objectfiles/main.o ./main.c $gcc_options || fail "Main invalid"
gcc -m32 -o ./objectfiles/game.o ./game.c $gcc_options || fail "Game invalid"

echoln "Linking..."
ld -melf_i386 -T linker.ld -o $output_bin ./objectfiles/loader.o \
 ./objectfiles/gdt-asm.o ./objectfiles/idt-asm.o ./objectfiles/startup.o \
 ./objectfiles/screen.o ./objectfiles/system.o ./objectfiles/gdt.o ./objectfiles/idt.o \
 ./objectfiles/keyboard.o ./objectfiles/pit.o ./objectfiles/syscall-asm.o ./objectfiles/main.o \
 ./objectfiles/game.o || fail "Linker error"

# Copy the kprogram.bin to sda2
#mkdir /media/partition2
#mount /dev/sda2 /media/partition2
#cp ./kprogram.bin /media/partition2/kprogram.bin
#umount /dev/sda2
#rm -r /media/partition2

# Run QEMU
# ./qemu.sh
