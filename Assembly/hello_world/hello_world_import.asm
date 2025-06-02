global _start

; Instead of writing constants ourselves, we can just import from a different file
%include "./syscalls.inc"

;
; CONSTANTS
;
STDOUT      equ 1


SECTION .data

hello   db  "Hello World!", 10
hello_len   equ $-hello

SECTION .text

_start:
    ; syscall(SYS_WRITE, STDOUT, hello, hello_len)
    mov rax, SYS_WRITE ; Just standard for Linux syscalls
    mov rdi, STDOUT
    lea rsi, [hello]
    mov rdx, hello_len
    syscall

    push rax ; Save the result of SYS_WRITE before we overwrite RAX
             ; Note: it returns the number of bytes successfully written

    ; syscall(SYS_EXIT, <sys_write return value> - hello_len);
    mov rax, SYS_EXIT
    pop rdi
    sub rdi, hello_len
    syscall
    