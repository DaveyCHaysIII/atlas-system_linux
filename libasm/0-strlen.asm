BITS 64

section .text
	global asm_strlen

asm_strlen:
	xor rax, rax

.loop:
	cmp byte [rdi], 0
	je .done
	inc rdi
	inc rax
	jmp .loop

.done:
	ret

