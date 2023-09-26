bits	64
section .data

redm:
    dq 0.299
greenm:
    dq 0.587
bluem:
    dq 0.114

section .text

global funcasm
funcasm:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 8
	
	mov	rax, rdi ; w
	mov	rbx, rsi ; h
	mov	r10, rdx ; channels
	mov	rdi, rcx ; *im
	; r8 - *res
	
	mul	rbx
	mul	r10
	mov	rcx, rax ; w * h *ch = size of data
    xor rax, rax
    mov r11, rdi
    add r11, rcx
.beg_loop:
    xorps xmm0, xmm0
    mov al, byte[rdi]
    cvtsi2sd xmm0, rax
    mulsd xmm0, [redm]
    add rdi, 1
    xorps xmm1, xmm1
    mov al, byte[rdi]
    cvtsi2sd xmm1, rax
    mulsd xmm1, [greenm]
    addsd xmm0, xmm1
    add rdi, 1
    xorps xmm1, xmm1
    mov al, byte[rdi]
    cvtsi2sd xmm1, rax
    mulsd xmm1, [bluem]
    addsd xmm0, xmm1
    add rdi, 1
    xor rax, rax
    cvtsd2si rax, xmm0
    mov [r8], rax
    add r8, 1
    mov [r8], rax
    add r8, 1
    mov [r8], rax
    add r8, 1
    sub rcx, 3
	cmp	rcx, 0
	jg	.beg_loop
.end_loop:
    xorps xmm0, xmm0
	xor	rax, rax
	leave
	pop rbx
	ret
