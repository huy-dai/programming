global main

extern printf ; External function

SECTION .data
    hello   db  "Hello World!", 10, 0
    hello_len   equ $-hello

SECTION .text
main:
    ; No need to set up stack here because
    ; we are not defining any stack variable

    ; return printf(hello) - hello_len
    push rbp
    lea rdi, [hello]
    xor rax, rax ; mov rax, 0
    call printf
    pop rbp
    sub rax, hello_len
    ret