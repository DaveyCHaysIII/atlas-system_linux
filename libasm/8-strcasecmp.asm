BITS 64

section .text
	global asm_strcasecmp

asm_strcasecmp:
	xor rax, rax

.loop:
	mov al, byte [rdi]
	mov bl, byte [rsi]
	cmp bl, 0
	je .greater
	cmp al, 0
	je .lesser

.lower_check_al:
	cmp al, 64
	jb .lower_check_bl
	cmp al, 91
	ja .lower_check_bl
	add al, 32

.lower_check_bl:
	cmp bl, 64
	jb .compare
	cmp bl, 91
	ja .compare
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
	ja .greater
	jb .lesser

.equal:
	xor rax, rax
	ret

.greater:
	sub al, bl
	movsx rax, al
	ret

.lesser:
	sub al, bl
	movsx rax, al
	ret
