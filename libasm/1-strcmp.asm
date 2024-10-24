BITS 64

section .text
	global asm_strcmp

asm_strcmp:
	xor rax, rax

.loop:
	mov al, [rdi]
	mov bl, [rsi]
	cmp al, 0
	je .done
	cmp bl, 0
	je .done
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


