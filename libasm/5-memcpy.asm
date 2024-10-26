BITS 64

section .text
	global asm_memcpy

asm_memcpy:
	cmp rdi, 0
	je .dest_ret
	cmp rsi, 0
	je .dest_ret
	xor rcx, rcx

.loop:
	cmp rdx, rcx
	je .dest_ret
	mov al, byte [rsi + rcx]
	mov byte [rdi + rcx], al
	inc rcx
	jmp .loop

.dest_ret:
	mov rax, rdi
	ret

