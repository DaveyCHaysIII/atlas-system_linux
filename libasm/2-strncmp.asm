BITS 64

section .text
	global asm_strncmp

asm_strncmp:
	xor rax, rax
	test rdi, rdi
	je .equal
	test rsi, rsi
	je .greater

.loop:
	test rdx, rdx
	je .equal
	mov al, [rdi]
	mov bl, [rsi]
	cmp al, 0
	je .def_done
	cmp bl, 0
	je .greater
	cmp al, bl
	jl .lesser
	jg .greater
	inc rdi
	inc rsi
	dec rdx
	jmp .loop

.def_done:
	cmp al, bl
	je .equal
	ja .greater
	jb .lesser

.equal:
	xor eax, eax
	ret

.greater:
	mov rax, 1
	ret

.lesser:
	mov rax, -1
	ret
