
.section .data


.section .text
.globl strlen_sse42
.type strlen_sse42, @function

strlen_sse42: 
xorq %r9,%r9
xorq %r10,%r10
xorq %rax,%rax
xorq %rcx,%rcx

str_next:
xorps %xmm0, %xmm0
xorps %xmm1, %xmm1
movdqu (%rdi, %r10), %xmm0
pcmpistri $0x08 ,%xmm1, %xmm0
jc done
inc %r9
movq %r9,%r10
shl $4, %r10
jmp str_next

done:
lea (%r10, %rcx, 1), %rax
ret 
