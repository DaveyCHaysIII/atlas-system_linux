BITS 64

section .text
	global asm_puts
	extern asm_strlen
asm_puts:
	push rbp
	mov rbp, rsp

	push rdi
	call asm_strlen
	mov rdx, rax
	mov rsi, [rsp]
	mov rdi, 1
	mov rax, 1
	syscall

	pop rdi
	mov rsp, rbp
	pop rbp
	ret
