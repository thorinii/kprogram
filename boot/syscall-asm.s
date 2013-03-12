#; Purpose:
#;   To run a specified system-call with specified arguments
#; Input:
#;  Values of %eax, %ebx, %ecx, %edx and the syscall number
#; Output:
#;  The result of the syscall

.globl syscall
.type syscall, @function 

.equ SYSCALL_INT, 0x48


.equ ARG_SYSCALL_INT, 8
.equ ARG_SYSCALL, 12
.equ ARG_EAX, 16
.equ ARG_EBX, 20
.equ ARG_ECX, 24
.equ ARG_EDX, 28
syscall:
  pushl %ebp
  movl %esp, %ebp
  movl ARG_SYSCALL(%ebp), %edi
  movl ARG_EAX(%ebp), %eax
  movl ARG_EBX(%ebp), %ebx
  movl ARG_ECX(%ebp), %ecx
  movl ARG_EDX(%ebp), %edx

  int $SYSCALL_INT
  # eax should now contain the result

  movl %ebp, %esp
  popl %ebp
  ret
