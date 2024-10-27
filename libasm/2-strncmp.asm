BITS 64

section .text
	global asm_strncmp

asm_strncmp:
	xor rax, rax
	cmp byte [rdi], 0
	je .def_done
	cmp byte [rsi], 0
	je .greater
	test rdx, rdx
	jz .equal

.loop:
	test rdx, rdx
	je .def_done
	mov al, byte [rdi]
	mov bl, byte [rsi]
	cmp bl, 0
	je .greater
	cmp al, 0
	je .lesser
	inc rdi
	inc rsi
	dec rdx
	jmp .loop

.def_done:
	cmp al, bl
	je .equal
	jmp .lesser

.equal:
	xor rax, rax
	ret

.greater:
	sub al, bl
	movsx rax, al
	ret

.lesser:
	xor rax, rax
	sub al, bl
	movsx rax, al
	ret
