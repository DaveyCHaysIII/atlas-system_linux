BITS 64

section .text
	global asm_strncmp

asm_strncmp:
	xor rax, rax
	test rdi, rdi
	je .equal
	test rsi, rsi
	je .greater
	test rdx, rdx
	je .equal

.loop:
	test rdx, rdx
	je .def_done
	mov al, [rdi]
	mov bl, [rsi]
	cmp al, 0
	je .def_done
	cmp bl, 0
	je .greater
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
	mov rax, 1
	ret

.lesser:
	mov rax, -1
	ret
