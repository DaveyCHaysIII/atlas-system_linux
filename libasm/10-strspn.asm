BITS 64

section .text
	global asm_strspn

asm_strspn:
	xor rcx, rcx

.loop:
	xor r10, r10
	mov al, [rdi + rcx]
	cmp al, 0
	je .done

.innerloop:
	mov bl, [rsi + r10]
	inc r10
	cmp bl, 0
	je .done
	cmp bl, al
	jne .innerloop
	inc rcx
	jmp .loop

.done:
	xor rax, rax
	mov rax, rcx
	ret

