.global loader                 # making entry point visible to linker

# setting up the Multiboot header - see GRUB docs for details
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum required

.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# reserve initial kernel stack space
.set STACKSIZE, 0x16000          # that is, 88k.
.comm stack, STACKSIZE, 32      # reserve 88k stack on a quadword boundary

loader:
   cli
   movl   $(stack + STACKSIZE), %esp # set up the stack
   pushl  %eax                       # Multiboot magic number
   pushl  %ebx                       # Multiboot data structure
   call  startup
   popl %ebx
   popl %eax

   sti # Enable interrupts after Startup

   call  kmain            # call the kernel

   cli

   call  cleanup

hang:
   hlt                    # halt machine should kernel return
   jmp   hang
