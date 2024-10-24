BITS 64

section .text
	global asm_strchr

asm_strchr:
.loop:
	cmp byte [rdi], sil
	je .done
	cmp byte [rdi], 0
	je .null_done
	inc rdi
	jmp .loop

.null_done:
	xor rax, rax
	ret

.done:
	mov rax, rdi
	ret

