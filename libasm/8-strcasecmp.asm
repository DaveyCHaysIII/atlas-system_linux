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

.lower_check:
	cmp al, 64
	jg .lc_check
	cmp bl, 64
	jg .lc_check
	jmp .compare

.compare:
	cmp al, bl
	jne .done
	inc rdi
	inc rsi
	jmp .loop

.lc_check:
	cmp al, 91
	jl .lc_offset_al
	cmp bl, 91
	jl .lc_offset_bl
	jmp .compare

.lc_offset_al:
	add al, 32
	jmp .lower_check

.lc_offset_bl:
	add bl, 32
	jmp .compare

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

