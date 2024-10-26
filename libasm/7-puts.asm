BITS 64

section .text
	global asm_puts
	extern asm_strlen
asm_puts:
	push rbp
	mov rbp, rsp
	push rsi
	push rdx
	call asm_strlen
	mov rdx, rax

	mov rax, 1
	mov rsi, rdi
	mov rdi, 1
	syscall

	pop rdx
	pop rsi
	mov rsp, rbp
	pop rbp
	ret
