BITS 64

section .text
	global asm_strncmp

asm_strncmp:
	xor rax, rax

.loop:
	test rdx, rdx
	je .def_done
	mov al, [rdi]
	mov bl, [rsi]
	cmp al, 0
	je .def_done
	cmp bl, 0
	je .def_done
	cmp al, bl
	je .equal
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
	xor rax, rax
	ret

.greater:
	mov rax, 1
	ret

.lesser:
	mov rax, -1
	ret

