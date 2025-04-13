long decode_c_version(long x, long y, long z){

y-=z; //%rsi=%rsi-%rdx -- subq %rdx,%rsi
x*=y; // %rdi=%rdi*%rsi ---     imulq %rsi,%rdi
long result = y; // %rax=%rsi -- movq %rsi,%rax
result <<= 63; // %rax=%rax<<63 -- salq $63,%rax
result >>=63; // %rax=%rax>>63 -- sarq $63,%rax
result^=x; // %rax=%rax^%rdi -- xorq %rdi,%rax
return result; //%rax -- ret
}