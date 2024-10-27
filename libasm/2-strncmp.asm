BITS 64

section .text
	global asm_strncmp

asm_strncmp:
	xor rax, rax
	cmp byte [rdi], 0
	je .equal
	cmp byte [rsi], 0
	je .greater
	test rdx, rdx
	jz .equal

.loop:
	test rdx, rdx
	je .def_done
	mov al, [rdi]
	mov bl, [rsi]
	cmp byte [rsi], 0
	je .greater
	cmp byte [rdi], 0
	je .lesser
	inc rdi
	inc rsi
	dec rdx
	jmp .loop

.def_done:
	cmp al, bl
	je .equal
	jg .greater
	jl .lesser

.equal:
	xor rax, rax
	ret

.greater:
	xor rax, rax
	sub al, bl
	movsx rax, al
	ret

.lesser:
	xor rax, rax
	sub al, bl
	movsx rax, al
	ret
