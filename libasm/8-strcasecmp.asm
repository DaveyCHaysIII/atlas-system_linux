BITS 64

section .text
	global asm_strcasecmp

asm_strcasecmp:
	xor rax, rax

.loop:
	mov al, [rdi]
	mov bl, [rsi]
	cmp al, 0
	je .done
	cmp bl, 0
	je .done

.lower_check_al:
	cmp al, 64
	jl .lower_check_bl
	cmp al, 91
	jg .lower_check_bl
	add al, 32

.lower_check_bl:
	cmp bl, 64
	jl .compare
	cmp bl, 91
	jg .compare
	add bl, 32
	jmp .compare

.compare:
	cmp al, bl
	jne .done
	inc rdi
	inc rsi
	jmp .loop

.done:
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

