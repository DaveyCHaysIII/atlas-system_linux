BITS 64

section .text
	global asm_strstr

asm_strstr:
	cmp byte [rsi], 0
	je .found
	cmp byte [rdi], 0
	je .null_done

.main_loop:
	mov al, byte [rdi]
	mov bl, byte [rsi]
	cmp al, 0
	je .null_done
	cmp bl, 0
	je .null_done
	cmp al, bl
	jne .next_char
	xor r10, r10

.inner_loop:
	mov al, byte [rdi + r10]
	mov bl, byte [rsi + r10]
	cmp bl, 0
	je .found
	cmp al, 0
	je .null_done

	cmp al, bl
	jne .next_char
	inc r10
	jmp .inner_loop

.next_char:
	inc rdi
	jmp .main_loop

.null_done:
	xor rax, rax
	ret

.found:
	mov rax, rdi
	ret

