BITS 64

section .text
	global asm_strcasecmp

asm_strcasecmp:
	xor rax, rax

.loop:
	movzx eax, byte [rdi]
	movzx ebx, byte [rsi]
	cmp ebx, 0
	je .greater
	cmp eax, 0
	je .lesser

.lower_check_al:
	cmp eax, 64
	jb .lower_check_bl
	cmp eax, 91
	ja .lower_check_bl
	add eax, 32

.lower_check_bl:
	cmp ebx, 64
	jb .compare
	cmp ebx, 91
	ja .compare
	add ebx, 32
	jmp .compare

.compare:
	cmp eax, ebx
	jne .done
	inc rdi
	inc rsi
	jmp .loop

.done:
	cmp eax, ebx
	ja .greater
	jb .lesser

.equal:
	xor rax, rax
	ret

.greater:
	sub eax, ebx
	movsx rax, eax
	ret

.lesser:
	sub rax, rbx
	ret
