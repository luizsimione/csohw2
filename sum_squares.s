.text
.globl    _sum_squares

_sum_squares:

pushq    %rbp
movq    %rsp, %rbp

movq    $0, %rax

movq    $1, %rcx

start_loop:

cmpq    %rdi, %rcx
jg      end_loop

movq    %rcx, %rdx
imulq   %rdx, %rdx
addq    %rdx, %rax

incq    %rcx
jmp     start_loop

end_loop:


popq    %rbp
retq                

