BITS 64

section .text
	global asm_strpbrk

asm_strpbrk:
	xor rax, rax

.loop:
	xor rcx, rcx
	mov al, [rdi]
	cmp al, 0
	je .done

.innerloop:
	mov bl, [rsi + rcx]
	cmp bl, al
	je .found
	inc rcx
	cmp bl, 0
	jne .innerloop
	inc rdi
	jmp .loop

.found:
	xor rax, rax
	mov rax, rdi
	ret

.done:
	xor rax, rax
	ret

